#include "SocketWorker.h"
#include "Sunnet.h"
#include <iostream>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <fcntl.h>
#include <sys/socket.h>


// 初始化
void SocketWorker::Init()
{
    cout << "SocketWorker Init" << endl;
    // 创建 epoll 对象
    epollFd = epoll_create(1024);
    assert(epollFd > 0);
}

void SocketWorker::operator()()
{
    while (true) {
        const int EVENT_SIZE = 64;
        struct epoll_event events[EVENT_SIZE];
        int eventCount = epoll_wait(epollFd, events, EVENT_SIZE, -1);
        // 取得事件
        for (int i = 0; i < eventCount; i++) {
            epoll_event ev = events[i];    // 当前要处理的事件
            OnEvent(ev);
        }
    }
}

// 注意跨线程调用
void SocketWorker::AddEvent(int fd) {
    cout << "AddEvent fd: " << fd << endl;
    // 添加到 epoll 对象
    struct epoll_event ev;
    ev.events = EPOLLIN | EPOLLET;
    ev.data.fd = fd;
    if (epoll_ctl(epollFd, EPOLL_CTL_ADD, fd, &ev) == -1 ) {
        cout << "AddEvent epoll_ctl Fail:" << strerror(errno) << endl;
    }
}


void SocketWorker::RemoveEvent(int fd) {
    cout << "RemoveEvent fd: " << fd << endl;
    epoll_ctl(epollFd, EPOLL_CTL_DEL, fd, nullptr);
}

void SocketWorker::ModifyEvent(int fd, bool epollOut) {
    cout << "ModifyEvent fd: " << fd << endl;
    struct epoll_event ev;

    ev.events = EPOLLIN | EPOLLET;
    if (epollOut) {
        ev.events |= EPOLLOUT;
    }
    ev.data.fd = fd;
    if (epoll_ctl(epollFd, EPOLL_CTL_MOD, fd, &ev) == -1 ) {
        cout << "ModifyEvent epoll_ctl Fail:" << strerror(errno) << endl;
    }
}

void SocketWorker::OnEvent(epoll_event ev) {
    cout << "OnEvent fd: " << ev.data.fd << endl;
    int fd = ev.data.fd;
    auto conn = Sunnet::_instance->GetConn(fd);
    if (conn == nullptr) {
        cout << "OnEvent error, conn == nullptr" << endl;
        return;
    }
    // 事件类型
    bool isRead = ev.events & EPOLLIN;
    bool isWrite = ev.events & EPOLLOUT;
    bool isError = ev.events & EPOLLERR;
    // 监听 socket
    if (conn->type == Conn::TYPE::LISTEN) {
        if (isRead) {
            OnAccept(conn);
        }
    }
    // 普通 socket
    else {
        if (isRead || isWrite) {
            OnRW(conn, isRead, isWrite);
        }
        if (isError) {
            cout << "OnEvent fd:" << conn->fd << endl;
        }
    }
}


void SocketWorker::OnAccept(shared_ptr<Conn> conn) {
    cout << "OnAccept fd: " << conn->fd << endl;
    // 步骤1：accept
    int clientFd = accept(conn->fd, nullptr, nullptr);
    if (clientFd < 0) {
        cout << "accept error: " << strerror(errno) << endl;
        return;
    }
    // 步骤2：设置非阻塞
    fcntl(clientFd, F_SETFL, O_NONBLOCK);
    // 步骤3：添加连接对象
    Sunnet::_instance->AddConn(clientFd, conn->serviceId, Conn::TYPE::CLIENT);
    // 步骤4：添加到 epoll 监听列表
    struct epoll_event ev;
    ev.events = EPOLLIN | EPOLLET;
    ev.data.fd = clientFd;
    if (epoll_ctl(epollFd, EPOLL_CTL_ADD, clientFd, &ev) == -1 ) {
        cout << "OnAccept epoll_ctl Fail:" << strerror(errno) << endl;
    }
    // 步骤5：通知服务
    auto msg = make_shared<SocketAcceptMsg>();
    msg->type = BaseMsg::TYPE::SOCKET_ACCEPT;
    msg->listenFd = conn->fd;
    msg->clientFd = clientFd;
    Sunnet::_instance->Send(conn->serviceId, msg);
}

void SocketWorker::OnRW(shared_ptr<Conn> conn, bool r, bool w) {
    cout << "OnRW fd: " << conn->fd << endl;
    auto msg = make_shared<SocketRWMsg>();
    msg->type = BaseMsg::TYPE::SOCKET_RW;
    msg->fd = conn->fd;
    msg->isRead = r;
    msg->isWrite = w;
    Sunnet::_instance->Send(conn->serviceId, msg);
}
