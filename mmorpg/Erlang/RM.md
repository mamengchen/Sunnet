# Erlang 用法

> Erlang 是在代码层面实现Actor模型的案例。

---
## Erlang 语法：
**行为模块规范：**

<p>
可以指定该模块是行为的回调模块：</p>

``` erlang
- behaviour(Behaviour).
%% 原子给出行为的名称，可以是 用户定义的行为或以下 OTP 标准行为之一：Behaviour
```
- gen_server
- gen_statem
- gen_event
- supervisor

模块的回调函数可以直接由 exported 函数：behaviour_info/1

---
<font>以下是一个基于 Erlang/OTP 的简单服务端实现，包含GenServer服务，监督树和 HTTP 接口。</font>