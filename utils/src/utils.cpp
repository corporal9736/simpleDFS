#include "utils.h"
#include "define.h"
#include <iostream>


std::vector<std::string> split(const std::string &str, const std::string &pattern)
{
    std::vector<std::string> res;
    if(str == "")
        return res;
    //在字符串末尾也加入分隔符，方便截取最后一段
    std::string strs = str + pattern;
    size_t pos = strs.find(pattern);

    while(pos != strs.npos)
    {
        std::string temp = strs.substr(0, pos);
        res.push_back(temp);
        //去掉已分割的字符串,在剩下的字符串中进行分割
        strs = strs.substr(pos+1, strs.size());
        pos = strs.find(pattern);
    }

    return res;
}

std::vector<std::string> getDirInfo(const std::string &JsonInfo)
{
    std::vector<std::string> res;
    Json::Value root;
    Json::Reader reader;
    if(!reader.parse(JsonInfo, root))
    {
        std::cout << "parse json error" << std::endl;
        return res;
    }
    for(int i=0;i<root["dir_info"].size();i++)
    {
        res.push_back(root["dir_info"][i].asString());
    }
    return res;
}

std::string generateDirInfo(const std::vector<std::string> &dirInfo)
{
    Json::Value root;
    for(const auto i: dirInfo)
    {
        root["dir_info"].append(i);
    }
    Json::FastWriter writer;
    return writer.write(root);
}

std::vector<chunk_meta> getChunkMeta(const std::string &JsonInfo){
    std::vector<chunk_meta> res;
    Json::Value root;
    Json::Reader reader;
    if(!reader.parse(JsonInfo, root))
    {
        std::cout << "parse json error" << std::endl;
        return res;
    }
    for(int i=0;i<root["chunk_meta"].size();i++)
    {
        chunk_meta temp;
        temp.chunk_hash = root["chunk_meta"][i]["hash"].asString();
        for(int j=0;j<root["chunk_meta"][i]["chunk_node_ip"].size();j++)
        {
            temp.chunk_node_ip.push_back(address(root["chunk_meta"][i]["chunk_node_ip"][j].asString()));
        }
        res.push_back(temp);
    }
    return res;
}

std::string generateChunkMeta(const std::vector<chunk_meta> &chunkMeta){
    Json::Value root;
    for(const auto i: chunkMeta)
    {
        Json::Value chunk;
        chunk["hash"] = i.chunk_hash;
        for(const auto j: i.chunk_node_ip)
        {
            chunk["chunk_node_ip"].append(j.to_string());
        }
        root["chunk_meta"].append(chunk);
    }
    Json::FastWriter writer;
    return writer.write(root);
}

chunk_node_state getChunkNodeState(const std::string &JsonInfo){
    chunk_node_state res;
    Json::Value root;
    Json::Reader reader;
    if(!reader.parse(JsonInfo, root))
    {
        std::cout << "parse json error" << std::endl;
        return res;
    }
    res.storge_left = root["storage_left"].asInt();
    res.last_update_time = root["last_update_time"].asInt();
    res.chunk_node_ip = address(root["chunk_node_ip"].asString());
    return res;
}

std::string generateChunkNodeState(const chunk_node_state &chunkNodeState){
    Json::Value root;
    root["storage_left"] = chunkNodeState.storge_left;
    root["last_update_time"] = chunkNodeState.last_update_time;
    root["chunk_node_ip"] = chunkNodeState.chunk_node_ip.to_string();
    Json::FastWriter writer;
    return writer.write(root);
}