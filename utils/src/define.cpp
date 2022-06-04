#include <vector>
#include "define.h"
#include "utils.h"
#include <iostream>
#include <fstream>
#include "json/json.h"
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
    // addr is in the form of "ip:port"
    // ip is in the form of "xxx.xxx.xxx.xxx"
    // port is in the form of "xxxx"
    std::string ip_str=addr.substr(0,addr.find(":"));
    std::string port_str=addr.substr(addr.find(":")+1);
    this->ip[0] = std::stoi(ip_str.substr(0,ip_str.find(".")));
    ip_str=ip_str.substr(ip_str.find(".")+1);
    this->ip[1] = std::stoi(ip_str.substr(0,ip_str.find(".")));
    ip_str=ip_str.substr(ip_str.find(".")+1);
    this->ip[2] = std::stoi(ip_str.substr(0,ip_str.find(".")));
    ip_str=ip_str.substr(ip_str.find(".")+1);
    this->ip[3] = std::stoi(ip_str);
    this->port = std::stoi(port_str);
}

address::address(const address& addr){
    // TODO: implement copy constructor
    for(int i=0;i<4;i++)
        this->ip[i] = addr.ip[i];
    this->port = addr.port;
}

const address& address::operator=(const address& addr){
    // TODO: implement operator =
    for(int i=0;i<4;i++)
        this->ip[i] = addr.ip[i];
    this->port = addr.port;
    return *this;
}

const std::string address::getIp(){
    // TODO: concat ip to string and return
    std::string ip_str=std::to_string(this->ip[0])+"."+std::to_string(this->ip[1])+"."+std::to_string(this->ip[2])+"."+std::to_string(this->ip[3]);
    return ip_str;
}

const int address::getPort(){
    return this->port;
}

config::config(const std::string& path){
    // TODO: parse config file and get config
    //读Path文件，解析成json格式，获取master_ip和chunk_node_ip
    Json::Value root;
    Json::Reader reader;
    std::ifstream ifs(path, std::ifstream::binary);
    if(!reader.parse(ifs, root, false)){
        std::cout<<"parse config file error!"<<std::endl;
        exit(1);
    }
    this->master_ip = address(root["master_ip"].asCString());
    for(int i=0;i<root["chunk_node_ip"].size();i++){
        this->chunk_node_ip.push_back(address(root["chunk_node_ip"][i].asCString()));
    }
}


chunk_node_state::chunk_node_state(){
    // TODO
}

chunk_meta::chunk_meta(){
    // TODO
}

file_meta::file_meta(){
    // TODO
}

int directory_node::addFile(const file_meta &file){
    //先判断文件不重名
    for(int i=0;i<this->files.size();i++){
        if(this->files[i].file_name == file.file_name){
            return -1;
        }
    }
    this->files.push_back(file);
    return 0;
}

int directory_node::delFile(const file_meta &file){
    for(int i=0;i<this->files.size();i++){
        if(this->files[i].file_name == file.file_name){
            this->files.erase(this->files.begin()+i);
            return 0;
        }
    }
    return -1;
}