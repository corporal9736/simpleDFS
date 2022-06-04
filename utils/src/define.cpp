#include "json/value.h"
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

const std::string address::getIp() const{
    // TODO: concat ip to string and return
    std::string ip_str=std::to_string(this->ip[0])+"."+std::to_string(this->ip[1])+"."+std::to_string(this->ip[2])+"."+std::to_string(this->ip[3]);
    return ip_str;
}

const int address::getPort() const{
    return this->port;
}

bool address::equal(const address &addr) const{
    if(this->port != addr.port)
        return false;
    for(int i=0;i<4;i++)
        if(this->ip[i] != addr.ip[i])
            return false;
    return true;
}

const std::string address::to_string() const{
    return this->getIp() + ":" + std::to_string(this->port);
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
    this->master_ip = address(root["master_ip"].asString());
    for(int i=0;i<root["chunk_node_ip"].size();i++){
        this->chunk_node_ip.push_back(address(root["chunk_node_ip"][i].asString()));
    }
    this->root_path = root["root_path"].asString();
    this->chunk_size = root["chunk_size"].asInt();
}


chunk_node_state::chunk_node_state(){
    // TODO
}

chunk_meta::chunk_meta(){
    // TODO
}

const Json::Value chunk_meta::to_json() const{
    Json::Value chunk;
    chunk["type"] = "chunk";
    chunk["hash"] = this->chunk_hash;
    for(const auto i: this->chunk_node_ip){
        chunk["chunk_node_ip"].append(i.to_string());
    }
    return chunk;
}

file_meta::file_meta(){
    // TODO
}

dir_node::dir_node(){

}

dir_node::~dir_node(){//释放内存
    // TODO
    //delete所有的file和dir_node
    //这里其实还可以给node发送任务删除对应的chunk
    for(int i=0;i<this->files.size();i++){
        delete this->files[i];
    }
    for(int i=0;i<this->sub_dir.size();i++){
        delete this->sub_dir[i];
    }
}

int dir_node::addFile(file_meta* file){
    //先判断文件不重名
    for(int i=0;i<this->files.size();i++){
        if(this->files[i]->file_name == file->file_name){
            return -1;
        }
    }
    this->files.push_back(file);
    return 0;
}

int dir_node::delFile(const std::string& file_name){
    for(int i=0;i<this->files.size();i++){
        if(this->files[i]->file_name == file_name){
            delete this->files[i];
            this->files.erase(this->files.begin()+i);
            return 0;
        }
    }
    return -1;
}

int dir_node::delDir(const std::string &dir_name){
    for(int i=0;i<this->sub_dir.size();i++){
        if(this->sub_dir[i]->name == dir_name){
            delete this->sub_dir[i];
            this->sub_dir.erase(this->sub_dir.begin()+i);
            return 0;
        }
    }
    return -1;
}

dir_node* dir_node::getSubDir(const std::string& dir_name){
    for(int i=0;i<this->sub_dir.size();i++){
        if(this->sub_dir[i]->name == dir_name){
            return this->sub_dir[i];
        }
    }
    return nullptr;
}

file_meta* dir_node::getFile(const std::string &file_name){
    for(int i=0;i<this->files.size();i++){
        if(this->files[i]->file_name == file_name){
            return this->files[i];
        }
    }
    return nullptr;
}

const Json::Value file_meta::to_json() const{
    Json::Value file;
    file["type"] = "file";
    file["name"] = this->file_name;
    file["comments"] = this->comments;
    for(const auto i: this->chunks){
        file["chunks"].append(i.to_json());
    }
    file["size"] = this->size;
    return file;
}