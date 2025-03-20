#include "Sunnet.h"
using namespace std;


void test() {
    auto pingType = make_shared<string>("ping");
    uint32_t ping1 = Sunnet::_instance->NewService(pingType);
    uint32_t ping2 = Sunnet::_instance->NewService(pingType);
    uint32_t pong = Sunnet::_instance->NewService(pingType);

    auto msg1 = Sunnet::_instance->MakeMsg(ping1, new char[3]{'h','i','\0'}, 3);
    auto msg2 = Sunnet::_instance->MakeMsg(ping2, new char[6]{'h','e','l','l','o','\0'}, 6);

    Sunnet::_instance->Send(pong, msg1);
    Sunnet::_instance->Send(pong, msg2);
}

void TestEcho() {
    auto t = make_shared<string>("echo");
    uint32_t echo = Sunnet::_instance->NewService(t);
}

int main(){
    new Sunnet();
    Sunnet::_instance->Start();
    test();
    // 开启系统后的一些逻辑
    Sunnet::_instance->Wait();
    return 0;
}