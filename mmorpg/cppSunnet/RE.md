### 自己实现的服务端架构（主要参考skynet）
---

<p>skynet是一个轻量级服务器框架，核心思想 <strong>Actor模型</strong> 和 <strong>高并发服务调度</strong></p>

<font>一个纯粹的Actor只是接收信息，受事件驱动，然后根据消息执行相应的计算。其中最大的特点：大量actor之间是相互隔离的，它们不共享内存。actor之间有且就有一种是消息通信。</font>

<font>在skynet源码中有两个队列：一个是私有队列，一个是全局队列</font>