#include "rpc.h"

std::string get(const std::string& hash){
    auto& cn = chunk_node::getInstance();
    return cn.get(hash);
}

void put(const std::string& content, const std::string& hash){
    auto& cn = chunk_node::getInstance();
    cn.put(content, hash);
}

void bindAll(rpc::server& server){
    server.bind("get", &get);
    server.bind("put", &put);
}