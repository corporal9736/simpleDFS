#include "rpc.h"

void bindAll(rpc::server &server){
    server.bind("test", &test);
}

std::string test(){
    auto& m = master::getInstance();
    return m.test();
}

std::vector<chunk_meta> get(const std::string& file_path){
    auto& m = master::getInstance();
    return m.get(file_path);
}

std::vector<chunk_meta> put(const std::string& path,const std::string& name, int size){//不着急写
    // auto& m = master::getInstance();
    // return m.put(path, name, size);
}

std::string getInfo(const std::string& file_path){
    auto& m = master::getInstance();
    return m.getInfo(file_path);
}

void updateState(const chunk_node_state &state){}

void heartBeat(){}
