#include "chunk_node.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <netinet/in.h>
#include <thread>
#include <filesystem>
#include <chrono>
#include "rpc/client.h"
#include "json/json.h"
#include "utils.h"
namespace fs = std::filesystem;
chunk_node::chunk_node(){}

void chunk_node::init(const std::string& configPath){
    //chunk.json的信息，包含port，master的地址
    std::ifstream ifs(configPath);
    if(!ifs){
        std::cout<<"open config file failed"<<std::endl;
        exit(1);
    }
    Json::Reader reader;
    Json::Value root;
    if(!reader.parse(ifs,root)){
        std::cout<<"parse config file failed"<<std::endl;
        exit(1);
    }
    this->addr = address(root["node_addr"].asString());
    this->master_addr = address(root["master_addr"].asString());
    this->root = root["node_root"].asString();
    this->total_size = root["max_size"].asInt64();
    //连接master
}

int chunk_node::getPort(){
    return this->addr.getPort();
}

std::string chunk_node::get(const std::string &hash){
    std::string path = this->root + "/" + hash;
    std::ifstream input_file(path, std::ifstream::binary);
    if (!input_file.is_open()) {
        std::cout << "Could not open the file - '"
             << path << "'" << std::endl;
        exit(1);
    }
    return std::string((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
}

void chunk_node::put(const std::string &content, const std::string &hash){
    std::string path = this->root + "/" + "hash";
    std::ofstream O(path,std::ofstream::binary);
	O << content;
    O.flush();
	O.close();
}

void chunk_node::reportState() const{
    std::cout << "report" <<std::endl;
    uintmax_t crnt_size = 0;
    for(const auto i: fs::directory_iterator(this->root)){
        crnt_size += i.file_size();
    }
    chunk_node_state st;
    st.chunk_node_ip = this->addr;
    st.last_update_time = time(NULL);
    st.storge_left = crnt_size / this->total_size;
    rpc::client ct(this->addr.getIp(),this->addr.getPort());
    // ct->async_call("updateState", generateChunkNodeState(st));
    ct.call("updateState", generateChunkNodeState(st));
}
