#include "chunk_node.h"
#include <fstream>
#include <iostream>
#include <netinet/in.h>
#include <thread>

void chunk_node::init(std::string configPath){
    //chunk的信息，由 | 分割，每个chunk的信息由 \n 分割
    this->config_path=configPath;
    std::ifstream ifs(configPath);
    std::string line;
    while(std::getline(ifs, line)){
        std::string chunk_hash=line.substr(0, line.find('|'));
        std::string chunk_meta=line.substr(line.find('|')+1);
        this->data[chunk_hash]=chunk_meta;
    }
    ifs.close();
    //开一个线程，每十分钟将map信息保存到文件中，文件格式为chunk_hash|chunk_meta
    std::thread t(&chunk_node::saveMap, this);
    t.detach();
}

void chunk_node::saveMap(){
    //每五分钟将map信息覆盖保存到文件中，文件格式为chunk_hash|chunk_meta
    while(true){
        std::ofstream ofs(this->config_path);
        for(auto it=this->data.begin(); it!=this->data.end(); it++){
            ofs<<it->first<<"|"<<it->second<<std::endl;
        }
        ofs.close();
        std::this_thread::sleep_for(std::chrono::seconds(300));
    }
}

int chunk_node::getPort(){
    return this->port;
}

void chunk_node::setPort(int port){
    this->port=port;
}