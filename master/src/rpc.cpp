#include "rpc.h"

void bindAll(rpc::server &server){
    server.bind("test", &test);
}

std::string test(){
    auto& m = master::getInstance();
    return m.test();
}

std::vector<chunk_meta> get(const std::string& file_path){}

std::vector<address> put(const std::string& path, int size){}

std::string getInfo(const std::string& file_path){}

void updateState(const chunk_node_state &state){}

void heartBeat(){}