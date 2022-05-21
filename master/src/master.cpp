#include <iostream>
#include <vector>
#include "master.h"
#include "jsoncpp/json/json.h"

master::master(std::string config_path){
    std::cout << "this is master" << std::endl;
    this->config_path = config_path;
    parseConfig();
}


int master::run(){
    return 0;
}

void master::parseConfig(){
    // TODO
    // use jsoncpp to parse config file
    // config path is stored in this->config_path
    // write result into this->master_config
    this->master_config = {
        .version = "1.0",
        .master_ip = "127.0.0.1:1234",
        .chunk_node_ip = std::vector<std::string>{"127.0.0.1:1235", "127.0.0.1:1236"}
    };
}

void master::getChunkStates(){
    return;
}