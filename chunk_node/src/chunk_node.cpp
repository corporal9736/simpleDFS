#include "chunk_node.h"
#include <fstream>
#include <iostream>
#include <netinet/in.h>
#include <thread>
#include "json/json.h"


chunk_node::chunk_node(){}

void chunk_node::init(std::string configPath){
    //chunk.json的信息，包含port，master的地址
    std::ifstream ifs(configPath);
    if(!ifs){
        std::cout<<"open config file failed"<<std::endl;
        exit(1);
    }
    Json::Reader reader;
    Json::Value root;
    if(!reader.parse(ifs,root)){
        std::cout<<"parse config file failed"<<std::endl;
        exit(1);
    }
    this->port = root["node_port"].asInt();
    std::string master_ip = root["master_ip"].asString();
    int master_port = root["master_port"].asInt();
    //连接master
}

int chunk_node::getPort(){
    return this->port;
}
