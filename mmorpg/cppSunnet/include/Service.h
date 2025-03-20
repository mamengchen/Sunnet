#pragma once
#include <queue>
#include <thread>
#include <memory>
#include <string>
#include "Msg.h"

using namespace std;

class Service{
public:
    uint32_t id;
    // 类型(服务类型)
    shared_ptr<string> type;
    // 是否正在退出
    bool isExiting = false;
    // 消息队列
    queue<shared_ptr<BaseMsg>> msgQueue;
    pthread_spinlock_t queueLock;
public:
    // 构造和析构函数
    Service();
    ~Service();

    // 回调函数
    void OnInit();
    void OnMsg(shared_ptr<BaseMsg> msg);
    void OnExit();

    // 插入消息
    void PushMsg(shared_ptr<BaseMsg> msg);

    // 执行消息
    bool ProcessMsg();
    void ProcessMsgs(int max);
private:
    // 取出一条消息
    shared_ptr<BaseMsg> PopMsg();
public:
    // 标记是否在全局队列，true:表示在队列中，或正在处理
    bool inGlobal = false;
    pthread_spinlock_t inGlobalLock;
    // 线程安全地设置 inGlobal
    void SetInGlobal(bool isIn);
};