#include <cstdio>
#include <iostream>
#include <sys/stat.h>
#include <vector>
#include <fstream>
#include "define.h"
#include "master.h"
#include "json/json.h"
#include "rpc.h"
#include "rpc/server.h"
#include "utils.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include "utils.h"


master::master(){
    std::cout << "this is master" << std::endl;
    this->isInited = false;
}

void master::init(std::string config_path){//没写完
    this->config_path = config_path;
    this->parseConfig();
    // this->getChunkStates();
    this->dir_root = new dir_node();
    this->parseFileTree(this->master_config->root_path,this->dir_root);
    this->isInited = true;
}

// void master::getChunkStates(){//这个咋写？
//     // TODO
//     // get chunk node info and write to this->states
// }

int master::getPort(){
    return this->master_config->master_ip.port;
}

const std::string master::test(){
    return "test success";
}

std::vector<chunk_meta> master::get(const std::string& file_path){
    // TODO
    // get file_path from this->dir_root
    //依照file_path找到文件，然后返回chunk_meta
    //如果文件不存在，返回空vector
    //如果文件存在，返回chunk_meta
    std::vector<chunk_meta> chunk_metas; 
    dir_node* dir = this->dir_root;
    std::vector<std::string> path_list = split(file_path, "/");
    int i=0;
    for(i = 0; i < path_list.size()-1; i++){
        if(path_list[i] == "")
            continue;
        dir = dir->getSubDir(path_list[i]);
        if(dir == NULL)
            return chunk_metas;
    }
    file_meta* file = dir->getFile(path_list[i]);
    if(file == NULL)
        return chunk_metas;
    chunk_metas = file->chunks;
    return chunk_metas;
}

std::vector<chunk_meta> master::put(const std::string &path, const std::string &name,const std::string &comments, int size){
    // TODO
    // 文件分块、分配chunk节点、写入chunk节点信息
    // 如果文件不存在，创建文件，分配chunk节点，写入chunk节点信息
    // 如果文件存在，分配chunk节点，写入chunk节点信息
    // 返回chunk_meta
    std::vector<chunk_meta> chunk_metas;
    dir_node* dir = this->dir_root;
    std::vector<std::string> path_list = split(path, "/");
    for(int i = 0; i < path_list.size(); i++){
        if(path_list[i] == "")
            continue;
        dir = dir->getSubDir(path_list[i]);
        if(dir == NULL)
            return chunk_metas;
    }
    file_meta* file = dir->getFile(name);
    if(file == NULL){
        file_meta* new_file= new file_meta();
        new_file->file_name = name;
        new_file->comments = comments;
        new_file->size = size;
        splitChunk(new_file);
        if(dir->addFile(new_file))
            return chunk_metas;
        chunk_metas = new_file->chunks;
        //同时将文件信息Json后写入文件
        std::string file_path = this->master_config->root_path + path;
        std::string file_name = file_path + "/" + name;
        std::ofstream ofs(file_name);
        Json::Value root=new_file->to_json();
        ofs<<root;
        ofs.close();
    }
    else{
        return chunk_metas;
    }
    return chunk_metas;
}

std::string master::getInfo(const std::string &file_path){
    // TODO
    //按照file_path找到文件，返回文件信息
    //如果文件不存在，返回空string
    //如果文件存在，返回文件信息
    std::string info;
    dir_node* dir = this->dir_root;
    std::vector<std::string> path_list = split(file_path, "/");
    int i=0;
    for(i = 0; i < path_list.size()-1; i++){
        if(path_list[i] == "")
            continue;
        dir = dir->getSubDir(path_list[i]);
        if(dir == NULL)
            return info;
    }
    file_meta* file = dir->getFile(path_list[i]);
    if(file == NULL)
        return info;
    info = "filename:" + file->file_name + "\ncomments:" + file->comments + "\nsize:" + std::to_string(file->size);
    return info;
}

std::vector<std::string> master::ls(const std::string &path){
    // TODO
    //按照path找到文件，返回文件列表
    //如果文件不存在，返回空vector
    //如果文件存在，返回文件列表
    std::vector<std::string> file_list;
    dir_node* dir = this->dir_root;
    std::vector<std::string> path_list = split(path, "/");
    for(int i = 0; i < path_list.size(); i++){
        if(path_list[i] == "")
            continue;
        dir = dir->getSubDir(path_list[i]);
        if(dir == NULL)
            return file_list;
    }
    //遍历subDir
    for(auto it = dir->sub_dir.begin(); it != dir->sub_dir.end(); it++){
        file_list.push_back("dir:"+(*it)->name);
    }
    //遍历files
    for(auto it = dir->files.begin(); it != dir->files.end(); it++){
        file_list.push_back("file:"+(*it)->file_name);
    }
    return file_list;
}

int master::mkdir(const std::string &path){
    // TODO
    //按照path找到文件，创建文件夹
    //如果文件不存在，返回-1
    //如果文件存在，返回0
    dir_node* dir = this->dir_root;
    std::vector<std::string> path_list = split(path, "/");
    for(int i = 0; i < path_list.size()-1; i++){//最后一个是要创建的文件夹
        if(path_list[i] == "")
            continue;
        dir = dir->getSubDir(path_list[i]);
        if(dir == NULL)
            return -1;
    }
    dir_node* new_dir = new dir_node();
    new_dir->name = path_list[path_list.size()-1];
    //同时在硬盘上创建文件夹
    std::string dir_path = this->master_config->root_path + path;//这个地址不对啊//坏了，这个地址对，更要命了//这，居然一切正常
    ::mkdir(dir_path.c_str(), 0777);
    dir->sub_dir.push_back(new_dir);
    return 0;
}

int master::rm(const std::string &path){
    // TODO
    //按照path找到文件，删除文件
    //如果文件不存在，返回-1
    //如果文件存在，返回0
    dir_node* dir = this->dir_root;
    std::vector<std::string> path_list = split(path, "/");
    for(int i = 0; i < path_list.size()-1; i++){//最后一个是要删除的文件
        if(path_list[i] == "")
            continue;
        dir = dir->getSubDir(path_list[i]);
        if(dir == NULL)
            return -1;
    }
    //同时在硬盘上删除文件
    std::string dir_path = this->master_config->root_path + path;
    remove(dir_path.c_str());

    dir->delFile(path_list[path_list.size()-1]);
    return 0;
}

int master::rmdir(const std::string &path){
    // TODO
    //按照path找到文件，删除文件夹
    //如果文件不存在，返回-1
    //如果文件存在，返回0
    dir_node* dir = this->dir_root;
    std::vector<std::string> path_list = split(path, "/");
    for(int i = 0; i < path_list.size()-1; i++){//最后一个是要删除的文件夹
        if(path_list[i] == "")
            continue;
        dir = dir->getSubDir(path_list[i]);
        if(dir == NULL)
            return -1;
    }
    //同时删除硬盘上的此文件夹与文件夹下的所有文件
    std::string dir_path = this->master_config->root_path + path;
    DIR* dir_ptr = opendir(dir_path.c_str());
    struct dirent* ptr;
    while((ptr = readdir(dir_ptr)) != NULL){
        if(strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0)
            continue;
        std::string file_path = dir_path + "/" + ptr->d_name;
        remove(file_path.c_str());
    }
    closedir(dir_ptr);
    remove(dir_path.c_str());

    dir->delDir(path_list[path_list.size()-1]);
    return 0;
}

void master::updateState(const chunk_node_state &state){
    //查看states中是否有该chunk_node
    //如果有，更新chunk_node的状态
    //如果没有，添加chunk_node
    for(auto it = this->states.begin(); it != this->states.end(); it++){
        if((*it).chunk_node_ip.equal(state.chunk_node_ip)){
            (*it).storge_left = state.storge_left;
            //更新为当前时间戳
            (*it).last_update_time = time(NULL);
            return;
        }
    }
    this->states.push_back(state);
}

void master::parseConfig(){
    // TODO
    // use jsoncpp to parse config file
    // config path is stored in this->config_path
    // write result into this->master_config
    // this->master_config is a pointer to a config object
    this->master_config=new config(this->config_path);
    //遍历address存到state里面
    for(int i = 0; i < this->master_config->chunk_node_ip.size(); i++){
        chunk_node_state state;
        state.chunk_node_ip = this->master_config->chunk_node_ip[i];
        state.storge_left = 0;
        state.last_update_time = time(NULL);
        this->states.push_back(state);
    }
}

// std::vector<std:: string>getFiles(const std::string& path){
//     // TODO
//     // get all files in path
// }


void master::parseFileTree(const std::string& path,dir_node* dir){
    // file信息以文件夹树的形式直接存在master中
    //递归解析文件夹树
    //获取path最后一个文件夹名
    dir->name=path.substr(path.find_last_of("/")+1);
    //遍历文件夹
    DIR *dp;
    struct dirent *dirp;
    if((dp=opendir(path.c_str()))==NULL){
        std::cout<<"Error("<<errno<<"):open "<<path<<std::endl;
        return;
    }
    while((dirp=readdir(dp))!=NULL){
        //跳过.和..
        if(strcmp(dirp->d_name,".")==0||strcmp(dirp->d_name,"..")==0)
            continue;
        //获取文件路径
        std::string file_path=path+"/"+dirp->d_name;
        //判断是否是文件夹
        struct stat statbuf;
        stat(file_path.c_str(),&statbuf);
        if(S_ISDIR(statbuf.st_mode)){
            //是文件夹，递归解析
            dir_node* new_dir=new dir_node;
            dir->sub_dir.push_back(new_dir);
            parseFileTree(file_path,new_dir);
        }
        else{
            //是文件，内容是file_meta的json信息，在这里将其还原
            Json::Reader reader;
            Json::Value value;
            std::ifstream in(file_path);
            reader.parse(in,value);
            file_meta* file=new file_meta();
            file->file_name=value["name"].asString();
            file->size=value["size"].asInt();
            file->comments=value["comments"].asString();
            //遍历chunk_meta
            for(int i=0;i<value["chunks"].size();i++){
                chunk_meta chunk;
                chunk.chunk_hash=value["chunks"][i]["hash"].asString();
                //遍历address
                for(int j=0;j<value["chunks"][i]["chunk_node_ip"].size();j++){
                    //直接生成address
                    address addr(value["chunks"][i]["chunk_node_ip"][j].asString());
                    chunk.chunk_node_ip.push_back(addr);
                }
                file->chunks.push_back(chunk);
            }
            dir->files.push_back(file);
        }
    }
    closedir(dp);
}

std::string getUUID(){
    // TODO
    // generate a uuid
    // return uuid
    return "test";
}

void master::splitChunk(file_meta* file){
    int chunk_num=file->size/this->master_config->chunk_size+1;
    for(int i=0;i<chunk_num;i++){
        chunk_meta chunk;
        //获取一个uuid
        std::string uuid=getUUID();
        chunk.chunk_hash=uuid;
        //在state里随机取三个不同的chunk_node
        //这里的取法需要考虑到node的剩余空间、热度等
        //但是这里直接随机了
        std::vector<address> chunk_node_ip;
        //生成三个不同的随机数
        int index[3]={0,0,0};
        for(int j=0;j<3;j++){
            if(this->states.size()<4){
                std::cout<<"Error:no chunk_node"<<std::endl;
                break;
            }
            index[j]=rand()%this->states.size();
            for(int k=0;k<j;k++){
                if(index[j]==index[k]){
                    j--;
                    break;
                }
            }
        }
        //取出对应的addr
        for(int j=0;j<3;j++){
            chunk_node_ip.push_back(this->states[index[j]].chunk_node_ip);
        }
        chunk.chunk_node_ip=chunk_node_ip;
        file->chunks.push_back(chunk);
    }
}

void master_test(){
    auto& m=master::getInstance();
    m.mkdir("/test2/test3");
    m.put("/test2/test3","test.txt","test",80000000);
    std::vector<chunk_meta> e=m.get("/test2/test.txt");
    std::cout<<e[0].chunk_node_ip[0].to_string()<<std::endl;
    std::cout<<m.ls("/test2")[0]<<std::endl;
}