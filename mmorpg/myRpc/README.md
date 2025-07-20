在 Linux 系统中，`epoll_event` 结构体是 epoll I/O 多路复用机制的核心数据结构，用于描述注册到 epoll 实例的文件描述符事件及其关联数据。

---

<strong>
源码定义（来自 Linux 头文件 sys/epoll.h）
</strong>

```c++
typedef union epoll_data {
    void *ptr;    // 用户自定义指针（常用）
    int   fd;     // 文件描述符
    uint32_t u32;   // 32 位无符号整数
    uint64_t u64;   // 64 位无符号整数
} epoll_data_t;

struct epoll_event {
    uint32_t events;   // 事件类型
    epoll_data_t data; // 用户数据（联合体，四选一）
};
```

<p>
1.event 字段：表示需要监听或实际发生的事件，由以下标志位通过 位或 | 组合：
</p>

```c
EPOLLIN     = 0x001,   // 监听可读事件
EPOLLOUT    = 0x004,   // 监听可写事件
EPOLLET     = (1 << 31), // 边缘触发模式（默认水平触发）

// 1.注册事件到 epoll
struct epoll_event event;
event.events = EPOLLIN | EPOLLET;    // 监听可读事件，边缘触发
event.data.fd = sockfd;              // 关联 socket 描述符
epoll_ctl(epollfd, EPOLL_CTL_ADD, sockfd, &event);

// 2.处理 epoll 返回事件
struct epoll_event events[MAX_EVENTS];
int n = epoll_wait(epollfd, events, MAX_EVENTS, -1);
for (int i = 0; i < n; i++) {
    if (events[i].events & EPOLLIN) {
        int fd = events[i].data.fd;
        handle_read(fd);
    }
}
```