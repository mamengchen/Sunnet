#include <iostream>
#include <unistd.h>
#include "Worker.h"
#include "Service.h"
#include "Sunnet.h"
using namespace std;

// 线程函数
void Worker::operator()() {
    while (true) {
        shared_ptr<Service> srv = Sunnet::_instance->PopGlobalQueue();
        if (!srv) {
            Sunnet::_instance->WorkerWait();
        }
        else {
            srv->ProcessMsgs(eachNum);
            CheckAndPutGlobal(srv);
        }
    }
}


void Worker::CheckAndPutGlobal(shared_ptr<Service> srv) {
    // 退出中（服务的退出方式只能它自己调用，这样 isExiting 才不会产生线程冲突）
    if (srv->isExiting) {
        return;
    }
    
    pthread_spin_lock(&srv->queueLock);
    {
        // 重新放回到全局队列
        if (!srv->msgQueue.empty()) {
            // 此时 srv->inGlobal 为 true
            Sunnet::_instance->PushGlobalQueue(srv);
        }
        // 不在队列中，重设 inGlobal
        else {
            srv->SetInGlobal(false);
        }
    }
    pthread_spin_unlock(&srv->queueLock);
}
