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
}

void master::getChunkStates(){
    // TODO
    // get chunk node info and write to this->states
}

int master::getPort(){
    int port = 0;
    /* tie(std::ignore, port) = parseAddress(master_config.master_ip); */
    return port;
}

const std::string master::test(){
    return "test success";
}
