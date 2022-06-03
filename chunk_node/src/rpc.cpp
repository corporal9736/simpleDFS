#include "rpc.h"

std::string get(const std::string& hash){}

void put(const std::string& content, const std::string& hash){}

void bindAll(rpc::server& server){
    server.bind("get", &get);
    server.bind("put", &put);
}