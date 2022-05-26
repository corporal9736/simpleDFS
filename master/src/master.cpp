#include <iostream>
#include <vector>
#include "master.h"
#include "json/json.h"
#include "rpc/server.h"
#include "utils.h"


master::master(){
    std::cout << "this is master" << std::endl;
    this->isInited = false;
}

void master::init(std::string config_path){
    this->config_path = config_path;
    this->parseConfig();
    this->getChunkStates();
    this->isInited = true;
}

void master::parseConfig(){
    // TODO
    // use jsoncpp to parse config file
    // config path is stored in this->config_path
    // write result into this->master_config
    this->master_config = {
        .version = "1.0",
        .master_ip = "127.0.0.1:8005",
        .chunk_node_ip = std::vector<std::string>{"127.0.0.1:1235", "127.0.0.1:1236"}
    };
}

void master::getChunkStates(){
    // TODO
    // get chunk node info and write to this->states
    this->states = {
        chunk_node_state{
            .chunk_node_ip = "127.0.0.1:1235",
            .storge_left = 50
        },
        chunk_node_state{
            .chunk_node_ip = "127.0.0.1:1236",
            .storge_left = 72
        }
    };
}

int master::getPort(){
    int port = 0;
    tie(std::ignore, port) = parseAddress(master_config.master_ip);
    return port;
}

const std::string master::test(){
    return "test success";
}
