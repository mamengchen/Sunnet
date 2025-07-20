#include "tc_epoller.h"
#include <unistd.h>

namespace tars
{
    TC_Epoller::TC_Epoller(bool bEt) 
    {
        _iEpollfd = -1;
        _pevs = nullptr;
        _bEt = bEt;
        _max_connections = 1024;
    }
    
    TC_Epoller::~TC_Epoller()
    {
        if(_pevs != nullptr) 
        {
            delete [] _pevs;
            _pevs = nullptr;
        }

        if (_iEpollfd > 0)
        {
            close(_iEpollfd);
        }
    }

    void TC_Epoller::ctrl(int fd, long long data, uint32_t events, int op)
    {
        struct epoll_event ev;
        ev.data.u64 = data;
        if (_bEt) {
            ev.events = events | EPOLLET; // Edge Triggered
        } else {
            ev.events = events; // Level Triggered
        }
        epoll_ctl(_iEpollfd, op, fd, &ev);
    }

    void TC_Epoller::create(int max_connections)
    {
        _max_connections = max_connections;
        _iEpollfd = epoll_create(_max_connections + 1);
        delete[] _pevs;
        _pevs = new struct epoll_event[_max_connections + 1];
    }


    void TC_Epoller::add(int fd, long long data, uint32_t events)
    {
        ctrl(fd, data, events, EPOLL_CTL_ADD);
    }

    void TC_Epoller::mod(int fd, long long data, uint32_t events)
    {
        ctrl(fd, data, events, EPOLL_CTL_MOD);
    }

    void TC_Epoller::del(int fd, long long data, uint32_t events)
    {
        ctrl(fd, data, events, EPOLL_CTL_DEL);
    }

    int TC_Epoller::wait(int millseconds)
    { 
        return ::epoll_wait(_iEpollfd, _pevs, _max_connections + 1, millseconds);
    }
}