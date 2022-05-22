#include "rpc.h"

void bindAll(rpc::server &server){
    server.bind("test", &test);
}

std::string test(){
    auto& m = master::getInstance();
    return m.test();
}