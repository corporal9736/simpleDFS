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
        void init(std::string configPath);//chunk的信息，包含port，master的地址
        int getPort();
        //然后是put和get方法
        std::string get(std::string chunk_hash);
    private:
        chunk_node();
        int port;
};



#endif //CHUNK_NODE_H