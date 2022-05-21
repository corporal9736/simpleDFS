#ifndef MASTER_H
#define MASTER_H
#include "define.h"
#include <unordered_map>
class master{
    public:
        master(std::string config_path);
        int run();
        
    private:
        std::string config_path;
        config master_config;
        std::vector<chunk_node_state> states;
        std::unordered_map<std::string, std::vector<chunk_meta>>* files; //file name as key
        void parseConfig();
        void getChunkStates();
    };

#endif //MASTER_H