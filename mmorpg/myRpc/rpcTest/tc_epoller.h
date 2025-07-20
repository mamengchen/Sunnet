#ifndef __TC_EPOLLER_H__
#define __TC_EPOLLER_H__ 

#include <sys/epoll.h>
#include <cassert>

namespace tars
{

class TC_Epoller {
public:
    TC_Epoller(bool bEt = true); 
    ~TC_Epoller();

    void create(int max_connections);

    void add(int fd, long long data, uint32_t events);

    void mod(int fd, long long data, uint32_t events);

    void del(int fd, long long data, uint32_t events);

    int wait(int millseconds);

    struct epoll_event* get(int i) { assert(i); }
protected:
    void ctrl(int fd, long long data, uint32_t events, int op);

protected:

    int _iEpollfd;
    int _max_connections;
    struct epoll_event* _pevs;
    bool _bEt; // Edge Triggered
};

}


#endif