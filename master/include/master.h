#ifndef MASTER_H
#define MASTER_H
#include <unordered_map>
#include "define.h"
#include "rpc/server.h"
#include "singleton.h"

class master: public PublicSingleton<master>
{
    friend class PublicSingleton<master>;
    public:
        master(const master&) = delete;
        master& operator=(const master&) = delete;
        const std::string test();
        void init(std::string config_path);
        int getPort();
        std::vector<chunk_meta> get(const std::string& file_path);
        std::vector<chunk_meta> put(const std::string& path,const std::string& name, int size);
        std::string getInfo(const std::string& file_path);
        
    private:
        master();
        bool isInited;
        std::string config_path;
        config* master_config;
        std::vector<chunk_node_state> states;
        std::unordered_map<std::string, std::vector<chunk_meta>>* files; //file name as key//这里如果这样做的话就没法做目录树了
        
        void parseConfig();
        void getChunkStates();
        
};

#endif //MASTER_H
