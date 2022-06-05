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
//获取一个port参数
int main(int argc, char *argv[]){
    // std::cout << "hello chunk_node" << std::endl;
    auto& cn=chunk_node::getInstance();
    int port=0;
    if(argc==1){
        cn.init("/home/thunder/CODE/c/simpleDFS/chunk_node/config.json");
        port=cn.getPort();
        std::cout<<"using default port "<<port<<std::endl;
    }else{
        cn.init("/home/thunder/CODE/c/simpleDFS/chunk_node/config.json",std::stoi(argv[2]));
        port=atoi(argv[1]);
        std::cout<<"using port "<<port<<std::endl;
    }
    rpc::server cn_server(port);//手动设置吧
    bindAll(cn_server);
    // std::thread t(update);
    // t.detach();
    cn.reportState();
    cn_server.run();
    return 0;
}