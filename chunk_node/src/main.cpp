#include <iostream>
#include "rpc.h"
#include "rpc/client.h"
#include <thread>
#include <chrono>

void update(){
    while(1){
        auto& cn=chunk_node::getInstance();
        cn.reportState();
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

int main(){
    // std::cout << "hello chunk_node" << std::endl;
    auto& cn=chunk_node::getInstance();
    cn.init("/home/thunder/CODE/c/simpleDFS/chunk_node/config.json");
    rpc::server cn_server(cn.getPort());//手动设置吧
    bindAll(cn_server);
    // std::thread t(update);
    // t.detach();
    cn.reportState();
    cn_server.run();
    return 0;
}