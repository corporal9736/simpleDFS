#include <vector>
#include "define.h"
#include "utils.h"
address::address(){
    for(int i=0;i<4;i++)
        this->ip[i]  = 0;
    this->port = 0;
}
address::address(int*ip, int port){
    this->ip[0] = *ip;
    this->ip[1] = *(ip+1);
    this->ip[2] = *(ip+2);
    this->ip[3] = *(ip+3);
    this->port = port;
}
address::address(const std::string& addr){
    // TODO: convert a string to address
    this->ip[0] = 127;
    this->ip[1] = 0;
    this->ip[2] = 0;
    this->ip[3] = 1;
    this->port = 1234;
}

address::address(const address& addr){
    // TODO: implement copy constructor
}

const address& address::operator=(const address& addr){
    // TODO: implement operator =
}

config::config(const std::string& path){
    // TODO: parse config file and get config
    int m_ip[4] = {127,0,0,1};
    int port = 1234;
    this->master_ip = address(m_ip, port);
    int node_ip[4] = {127,0,0,1};
    int node_1_port = 1235;
    int node_2_port = 1236;
    this->chunk_node_ip = {
        address(node_ip,node_1_port),
        address(node_ip,node_2_port)
    };
}


chunk_node_state::chunk_node_state(){
    // TODO
}

chunk_meta::chunk_meta(){
    // TODO
}
