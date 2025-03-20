
#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include "Worker.h"
#include "Service.h"
#include "SocketWorker.h"
#include "Conn.h"

class Sunnet
{
public:
    static Sunnet* _instance;
public:
    Sunnet();
    void Start();

    // 等待运行
    void Wait();
private:
    // 工作线程
    int WORKER_NUM = 3;
    vector<Worker*> workers;
    vector<thread*> workerThreads;

    // 开启工作线程
    void StartWorkers();
public:
    // 服务列表
    unordered_map<uint32_t, shared_ptr<Service>> services;
    uint32_t maxId = 0;                     // 最大ID
    pthread_rwlock_t serviceLock;           // 读写锁

public:
    // 增删服务
    uint32_t NewService(shared_ptr<string> type);
private:
    void KillService(uint32_t id);              // 仅限服务自己调用
    // 获取服务
    shared_ptr<Service> GetService(uint32_t id);

private:
    // 全局队列
    queue<shared_ptr<Service>> globalQueue;
    int globalLen = 0;                              // 队列长度
    pthread_spinlock_t globalLock;                  // 锁
public:
    // 发送消息
    void Send(uint32_t toId, shared_ptr<BaseMsg> msg);

    // 全局队列操作
    shared_ptr<Service> PopGlobalQueue();
    void PushGlobalQueue(shared_ptr<Service> srv);

    // 仅测试用
    shared_ptr<BaseMsg> MakeMsg(uint32_t source, char* buff, int len);
private:
    // 休眠和唤醒
    pthread_mutex_t sleepMtx;
    pthread_cond_t sleepCond;
    int sleepCount = 0;
public:
    // 唤醒工作线程
    void CheckAndWeakUp();
    // 让工作线程等待
    void WorkerWait();

private:
    // socket 线程
    SocketWorker* socketWorker;
    thread* socketThread;
    // 开启 Socket 线程
    void StartSocket();

// conn 相关内容
public:
    // 增删查 Conn
    int AddConn(int fd, uint32_t id, Conn::TYPE type);
    shared_ptr<Conn> GetConn(int fd);
    bool RemoveConn(int fd);
private:
    // conn 列表
    unordered_map<uint32_t, shared_ptr<Conn>> conns;
    pthread_rwlock_t connsLock; // 读写锁
public:
    // 网络连接操作接口
    int Listen(uint32_t port, uint32_t serviceId);
    void CloseConn(uint32_t fd);
};

