#include <iostream>
#include "Sunnet.h"
#include <assert.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
using namespace std;

// 单例
Sunnet* Sunnet::_instance;

Sunnet::Sunnet(){
    _instance = this;
}


void Sunnet::Start(){
    cout<<"Sunnet Start"<<endl;
    // 初始化锁
    pthread_rwlock_init(&serviceLock, NULL);
    pthread_spin_init(&globalLock, PTHREAD_PROCESS_PRIVATE);
    // 开启工作线程
    StartWorkers();
    // 开启socket 线程
    StartSocket();

    assert(pthread_rwlock_init(&connsLock, NULL) == 0);
}

void Sunnet::StartWorkers(){
    for (int i = 0; i < WORKER_NUM; i++) {
        cout << "start worker thread:" << i << endl;
        // 创建线程对象
        Worker* worker = new Worker();
        worker->id = i;
        worker->eachNum = 2 << i;
        // 创建线程
        thread* wt = new thread(*worker);
        // 添加到数组
        workers.push_back(worker);
        workerThreads.push_back(wt);
    }
}

// 等待
void Sunnet::Wait(){
    if (workerThreads[0]) {
        workerThreads[0]->join();
    }
}


//新建服务
uint32_t Sunnet::NewService(shared_ptr<string> type){
    auto srv = make_shared<Service>();
    srv->type = type;
    pthread_rwlock_wrlock(&serviceLock);
    {
        srv->id = maxId;
        maxId++;
        services.emplace(srv->id, srv);
    }
    pthread_rwlock_unlock(&serviceLock);
    srv->OnInit();          // 初始化
    return srv->id;
}


// 由id查询服务
shared_ptr<Service> Sunnet::GetService(uint32_t id){
    shared_ptr<Service> srv = NULL;
    pthread_rwlock_rdlock(&serviceLock);
    {
        unordered_map<uint32_t, shared_ptr<Service>>::iterator it = services.find(id);
        if (it != services.end()) {
            srv = it->second;
        }
    }
    pthread_rwlock_unlock(&serviceLock);
    return srv;
}

// 删除服务
// 只能 service 自己调用自己，因为会调用不加锁的 srv->OnExit 和 srv->isExiting
void Sunnet::KillService(uint32_t id){
    shared_ptr<Service> srv = GetService(id);
    if (!srv) {
        return;
    }
    // 退出前
    srv->OnExit();
    srv->isExiting = true;
    // 删除列表
    pthread_rwlock_wrlock(&serviceLock);
    {
        services.erase(id);
    }
    pthread_rwlock_unlock(&serviceLock);
}

// 弹出全局队列
shared_ptr<Service> Sunnet::PopGlobalQueue(){
    shared_ptr<Service> srv = NULL;
    pthread_spin_lock(&globalLock);
    {
        if (!globalQueue.empty()) {
            srv = globalQueue.front();
            globalQueue.pop();
            globalLen--;
        }
    }
    pthread_spin_unlock(&globalLock);
    return srv;
}


// 插入全局队列
void Sunnet::PushGlobalQueue(shared_ptr<Service> srv){
    pthread_spin_lock(&globalLock);
    {
        globalQueue.push(srv);
        globalLen++;
    }
    pthread_spin_unlock(&globalLock);
}


// 发送消息
void Sunnet::Send(uint32_t toId, shared_ptr<BaseMsg> msg){
    shared_ptr<Service> toSrv = GetService(toId);
    if (!toSrv) {
        cout << "Send fail, toSrv not exist toId:" << toId << endl;
        return;
    }
    // 插入目标服务的消息队列
    toSrv->PushMsg(msg);
    // 检查并放入全局队列
    bool hasPush = false;
    pthread_spin_lock(&toSrv->inGlobalLock);
    {
        if (!toSrv->inGlobal) {
            PushGlobalQueue(toSrv);
            toSrv->inGlobal = true;
            hasPush = true;
        }
    }
    pthread_spin_unlock(&toSrv->inGlobalLock);

    // 唤起进程，不放在临界区里面
    if (hasPush) {
        CheckAndWeakUp();
    }
}

// buff 须有 new 产生
shared_ptr<BaseMsg> Sunnet::MakeMsg(uint32_t source, char* buff, int len){
    auto msg = make_shared<ServiceMsg>();
    msg->type = BaseMsg::TYPE::SERVICE;
    msg->source = source;
    msg->buff = buff;
    msg->size = len;
    return msg;
}

// worker 线程调用，进入休眠
void Sunnet::WorkerWait(){
    pthread_mutex_lock(&sleepMtx);
    sleepCount++;
    pthread_cond_wait(&sleepCond, &sleepMtx);
    sleepCount--;
    pthread_mutex_unlock(&sleepMtx);
}

// 检查并唤醒线程
void Sunnet::CheckAndWeakUp(){
    if (sleepCount == 0) {
        return;
    }
    if (WORKER_NUM - sleepCount <= globalLen) {
        cout << "weakup" << endl;
        pthread_cond_signal(&sleepCond);
    }
}

// 开启 socket 线程
void Sunnet::StartSocket(){
    // 创建线程对象
    socketWorker = new SocketWorker();
    // 初始化
    socketWorker->Init();
    // 创建线程
    socketThread = new thread(*socketWorker);
}

// 添加连接
int Sunnet::AddConn(int fd, uint32_t id, Conn::TYPE type) {
    auto conn = make_shared<Conn>();
    conn->fd = fd;
    conn->serviceId = id;
    conn->type = type;
    pthread_rwlock_wrlock(&connsLock);
    {
        conns.emplace(fd, conn);
    }
    pthread_rwlock_unlock(&connsLock);
    return fd;
}

// 通过 id 查找连接
shared_ptr<Conn> Sunnet::GetConn(int fd) {
    shared_ptr<Conn> conn = NULL;
    pthread_rwlock_rdlock(&connsLock);
    {
        unordered_map<uint32_t, shared_ptr<Conn>>::iterator iter = conns.find(fd);
        if (iter != conns.end()) {
            conn = iter->second;
        }
    }
    pthread_rwlock_unlock(&connsLock);
    return conn;
}


// 删除连接
bool Sunnet::RemoveConn(int fd) {
    int result;
    pthread_rwlock_wrlock(&connsLock);
    {
        result = conns.erase(fd);
    }
    pthread_rwlock_unlock(&connsLock);
    return result;
}


// 监听连接
int Sunnet::Listen(uint32_t port, uint32_t serviceId) {
    // 步骤1：创建 socket
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd <= 0) {
        cout << "listen error, listenfd <= 0" << endl;
        return -1;
    }
    // 步骤2：设置为非阻塞
    fcntl(listenfd, F_SETFL, O_NONBLOCK);
    // 步骤3：bind
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    int ret = bind(listenfd, (struct sockaddr*)&addr, sizeof(addr));
    if (ret == -1) {
        cout << "listen error, bind fail" << endl;
        return -1;
    }
    // 步骤4：listen
    ret = listen(listenfd, 64);
    if (ret < 0) {
        return -1;
    }
    // 步骤5：添加到管理结构
    AddConn(listenfd, serviceId, Conn::TYPE::LISTEN);
    // 步骤6：epoll 事件，跨线程
    socketWorker->AddEvent(listenfd);
    return listenfd;
}

void Sunnet::CloseConn(uint32_t fd) {
    // 删除 conn 对象
    bool succ = RemoveConn(fd);
    // 关闭 socket
    close(fd);
    // 删除 epoll 对象对套接字的监听
    if (succ) {
        socketWorker->RemoveEvent(fd);
    }
}
