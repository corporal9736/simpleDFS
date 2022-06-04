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
    for(int i = 0; i < path_list.size(); i++){
        if(path_list[i] == "")
            continue;
        dir = dir->getSubDir(path_list[i]);
        if(dir == NULL)
            return chunk_metas;
    }
    file_meta* file = dir->getFile(file_path);
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
    file_meta* file = dir->getFile(path);
    if(file == NULL){
        file_meta* new_file= new file_meta();
        new_file->file_name = name;
        new_file->comments = comments;
        new_file->size = size;
        splitChunk(new_file);
        if(dir->addFile(new_file))
            return chunk_metas;
        chunk_metas = new_file->chunks;
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

void master::splitChunk(file_meta* file){
    // int chunk_num=file->size/this->master_config->chunk_size+1;
    // for(int i=0;i<chunk_num;i++){
    //     chunk_meta chunk;
    //     chunk.chunk_hash=hash(file->file_name+std::to_string(i));
    //     for(int j=0;j<this->master_config->chunk_node_num;j++){
    //         address addr=this->master_config->chunk_node_ip[j];
    //         chunk.chunk_node_ip.push_back(addr);
    //     }
    //     file->chunks.push_back(chunk);
    // }
}