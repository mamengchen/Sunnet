#pragma once
#include <thread>
#include <string>
#include <memory>
class Sunnet;
class Service;
using namespace std;

class Worker{
public:
    int id;                 // 编号
    int eachNum;            // 每次处理多少条信息
    void operator()();      // 线程函数

    void CheckAndPutGlobal(shared_ptr<Service> srv);
};