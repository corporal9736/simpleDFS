#include <iostream>
#include <vector>
#include <fstream>
#include "master.h"
#include "json/json.h"
#include "rpc.h"
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
    this->parseFileTree();
    this->isInited = true;
}

void master::parseConfig(){
    // TODO
    // use jsoncpp to parse config file
    // config path is stored in this->config_path
    // write result into this->master_config
    // this->master_config is a pointer to a config object
    this->master_config=new config(this->config_path);
}

void master::getChunkStates(){//这个咋写？
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

std::vector<chunk_meta> master::get(const std::string& file_path){
    // TODO
    // get file_path's chunk_meta from this->files
    // return the result
    // std::string key=file_path;
    // std::vector<chunk_meta> result;
    // if(this->files->find(key)!=this->files->end()){
    //     result=this->files->at(key);
    // }
    // return result;
}

std::vector<chunk_meta> master::put(const std::string &path, const std::string &name, int size){
    // TODO
    // 文件分块、分配chunk节点、写入chunk节点信息
}

std::string master::getInfo(const std::string &file_path){
    // TODO
    //
}

void master::parseFileTree(){
    Json::Reader reader;
    std::ifstream ifs(this->master_config->file_tree_path, std::ifstream::binary);
    if(!reader.parse(ifs, this->file_tree_root, false)){
        std::cout<<"parse file tree error!"<<std::endl;
        exit(1);
    }
}

const bool is_directory(Json::Value node){
    return !node.isArray();
}

const bool is_file(Json::Value node){
    return node.isArray();
}