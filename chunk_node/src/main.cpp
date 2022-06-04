#include <iostream>
#include "rpc.h"

int main(){
    // std::cout << "hello chunk_node" << std::endl;
    auto& cn=chunk_node::getInstance();
    cn.init("/home/thunder/CODE/c/simpleDFS/chunk_node/config.json");
    rpc::server cn_server(cn.getPort());//手动设置吧
    bindAll(cn_server);
    cn_server.run();
    return 0;
}