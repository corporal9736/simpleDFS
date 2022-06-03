#ifndef CHUNK_NODE_H
#define CHUNK_NODE_H
#include <string>
#include <unordered_map>
#include "define.h"
#include "singleton.h"

class chunk_node:public PublicSingleton<chunk_node>{
    friend class PublicSingleton<chunk_node>;
    public:
        chunk_node(const chunk_node&) = delete;
        chunk_node& operator=(const chunk_node&) = delete;
        void init(std::string configPath);//chunk的信息，由 | 分割，每个chunk的信息由 \n 分割
        void saveMap();//每十分钟将map信息保存到文件中，文件格式为chunk_hash|chunk_meta
        int getPort();
        void setPort(int port);
        //然后是put和get方法

    private:
        std::unordered_map<std::string, std::string> data;//chunk_hash,chunk_meta
        std::string config_path;
        int port;
};


#endif //CHUNK_NODE_H