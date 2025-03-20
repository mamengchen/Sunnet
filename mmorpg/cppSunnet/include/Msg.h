#pragma once
#include <cstdint>
#include <string>
using namespace std;


// 消息基类
class BaseMsg {
public:
    enum TYPE {         // 消息类型
        SERVICE = 1,
        SOCKET_ACCEPT = 2,      // 套接字接受
        SOCKET_RW = 3,          // 套接字读写
    };
    uint8_t type;       // 消息类型
    char load[999999]{};    // 用于检测内存泄漏，
    virtual ~BaseMsg() {};
};

class ServiceMsg : public BaseMsg {
public:
    char* buff;
    uint32_t source;
    uint32_t size;
};

// 有新连接
class SocketAcceptMsg : public BaseMsg {
public:
    int listenFd;
    int clientFd;
};

// 读写套接字
class SocketRWMsg : public BaseMsg {
public:
    int fd;
    bool isRead = false;
    bool isWrite = false;
};