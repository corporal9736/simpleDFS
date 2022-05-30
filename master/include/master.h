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
        
    private:
        master();
        bool isInited;
        std::string config_path;
        config* master_config;
        std::vector<chunk_node_state> states;
        std::unordered_map<std::string, std::vector<chunk_meta>>* files; //file name as key
        
        void parseConfig();
        void getChunkStates();
    };

#endif //MASTER_H
