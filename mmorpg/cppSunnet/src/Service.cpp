#include "Service.h"
#include "Sunnet.h"
#include <iostream>
#include <unistd.h>
#include <string.h>


// 构造函数
Service::Service(){
    // 初始化自旋锁
    pthread_spin_init(&queueLock, PTHREAD_PROCESS_PRIVATE);

    // 初始化全局队列
    pthread_spin_init(&inGlobalLock, PTHREAD_PROCESS_PRIVATE);
}

// 析构函数
Service::~Service(){
    pthread_spin_destroy(&queueLock);

    pthread_spin_destroy(&inGlobalLock);
}

// 插入消息
void Service::PushMsg(shared_ptr<BaseMsg> msg) {
    pthread_spin_lock(&queueLock);
    {
        msgQueue.push(msg);
    }
    pthread_spin_unlock(&queueLock);
}


// 取出消息
shared_ptr<BaseMsg> Service::PopMsg() {
    shared_ptr<BaseMsg> msg = NULL;
    pthread_spin_lock(&queueLock);
    {
        if (!msgQueue.empty()) {
            msg = msgQueue.front();
            msgQueue.pop();
        }
    }
    pthread_spin_unlock(&queueLock);
    return msg;
}


// 创建服务后触发
void Service::OnInit(){
    cout << "【id:" << id << "】OnInit" << endl;
    // 开启监听
    Sunnet::_instance->Listen(8002, id);
}


// 退出服务时触发
void Service::OnExit(){
    cout << "【id:" << id << "】OnExit" << endl;
}

// 处理一条消息，返回值代表是否处理
bool Service::ProcessMsg(){
    shared_ptr<BaseMsg> msg = PopMsg();
    if (msg != NULL) {
        OnMsg(msg);
        return true;
    }
    else {
        return false;
    }
}

// 处理 N 条消息，返回值代表是否处理
void Service::ProcessMsgs(int max){
    for (int i = 0; i < max; i++) {
        bool succ = ProcessMsg();
        if (!succ) {
            break;
        }
    }
}

void Service::SetInGlobal(bool isIn){
    pthread_spin_lock(&inGlobalLock);
    {
        inGlobal = isIn;
    }
    pthread_spin_unlock(&inGlobalLock);
}


// 收到信息时33触发
void Service::OnMsg(shared_ptr<BaseMsg> msg){
    // 测试用
    if (msg->type == BaseMsg::TYPE::SERVICE) {
        auto m = dynamic_pointer_cast<ServiceMsg>(msg);
        cout << "【id:" << id << "】OnMsg source:" << m->source << " size:" << m->size << " |buffmsg:" << m->buff << endl;

        auto msgRet = Sunnet::_instance->MakeMsg(id, new char[999999]{'p','i','c','k','\0'}, 999999);
        Sunnet::_instance->Send(m->source, msgRet);
    }
    // SOCKET_ACCEPT
    if (msg->type == BaseMsg::TYPE::SOCKET_ACCEPT) {
        auto m = dynamic_pointer_cast<SocketAcceptMsg>(msg);
        cout << "new conn " << m->clientFd << endl;
    }
    // SOCKET_RW
    if (msg->type == BaseMsg::TYPE::SOCKET_RW) {
        auto m = dynamic_pointer_cast<SocketRWMsg>(msg);
        if (m->isRead) {
            char buff[512];
            int len = read(m->fd, &buff, 512);
            if (len > 0) {
                char writeBuff[3] = {'l', 'p', 'y'};
                write(m->fd, &writeBuff, 3);
            }
            else {
                cout << "close " << m->fd << endl;
                Sunnet::_instance->CloseConn(m->fd);
            }
        }
    }
}