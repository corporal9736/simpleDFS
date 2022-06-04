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
        void init(const std::string& configPath);//chunk的信息，包含port，master的地址
        int getPort();
        //然后是put和get方法
        std::string get(const std::string& hash);
        void put(const std::string& content, const std::string& hash);
        void reportState() const;
    private:
        chunk_node();
        address addr;
        address master_addr;
        std::string root;
        std::uint64_t total_size; // size in byte, 21474836480 byte = 20GB
};



#endif //CHUNK_NODE_H