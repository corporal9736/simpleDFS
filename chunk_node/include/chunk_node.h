#ifndef CHUNK_NODE_H
#define CHUNK_NODE_H
#include <string>
#include <unordered_map>
#include "define.h"
#include "singleton.h"

class chunk_node:public PublicSingleton<chunk_node>{
    friend class PublicSingleton<chunk_node>;
    public:
    private:
        std::unordered_map<std::string, chunk_meta> data;
};


#endif //CHUNK_NODE_H