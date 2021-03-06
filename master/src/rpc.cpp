#include "rpc.h"
#include "utils.h"
#include <iostream>

void bindAll(rpc::server &server){
    server.bind("test", &test);
    server.bind("get", &get);
    server.bind("put", &put);
    server.bind("getInfo", &getInfo);
    server.bind("ls", &ls);
    server.bind("mkdir", &mkdir);
    server.bind("removeFile", &removeFile);
    server.bind("removeDir", &removeDir);
    server.bind("updateState", &updateState);
    server.bind("heartBeat", &heartBeat);
}

std::string test(){
    auto& m = master::getInstance();
    return m.test();
}

std::string get(const std::string& file_path){
    auto& m = master::getInstance();
    return generateChunkMeta(m.get(file_path));
}

std::string put(const std::string& path,const std::string comment, int size){
    auto& m = master::getInstance();
    std::cout<<"put "<<path<<" "<<comment<<" "<<size<<std::endl;
    return generateChunkMeta(m.put(path,comment,size));
}

std::string getInfo(const std::string& file_path){
    auto& m = master::getInstance();
    return m.getInfo(file_path);
}

std::vector<std::string> ls(const std::string &dir_path){
    auto& m = master::getInstance();
    return m.ls(dir_path);
}

int mkdir(const std::string &dir_path){
    auto& m = master::getInstance();
    return m.mkdir(dir_path);
}

int removeFile(const std::string &file_path){
    auto& m = master::getInstance();
    return m.rm(file_path);
}

int removeDir(const std::string &dir_path){
    auto& m = master::getInstance();
    return m.rmdir(dir_path);
}

void updateState(const std::string &state){
    auto& m = master::getInstance();
    m.updateState(getChunkNodeState(state));
}

void heartBeat(){}
