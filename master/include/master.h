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
        void getChunknodeInfo(); // get all hash from all chunk_nodes

        //client
        std::vector<chunk_meta> get(const std::string& file_path);
        std::vector<chunk_meta> put(const std::string& path,const std::string& comment, int size);
        std::string getInfo(const std::string& file_path);
        std::vector<std::string> ls(const std::string& path);
        int mkdir(const std::string& path);
        int rm(const std::string& path);
        int rmdir(const std::string& path);

        //chunk_node
        // int chunkNodeSignIn(const chunk_node_state& state);//不要这个了，只需要下面那个就行了
        void updateState(const chunk_node_state& state);
        
    private:
        master();
        bool isInited;
        std::string config_path;
        config* master_config;//在这里面有chunk_node的信息
        std::vector<chunk_node_state> states;
        dir_node* dir_root;
        
        void parseConfig();
        // void getChunkStates();
        void parseFileTree(const std::string& path,dir_node* dir); // get file tree information from a file tree
        // void saveFileTree();
        void splitChunk(file_meta* file);   
};

void master_test();

#endif //MASTER_H
