#ifndef DEFINE_H
#define DEFINE_H
#include <vector>
#include <string>
#include <unordered_set>
    typedef struct struct_config {
        std::string version;
        std::string master_ip;
        std::vector<std::string> chunk_node_ip;
    } config;

    typedef struct struct_chunk_node_state {
        std::string chunk_node_ip;
        int storge_left; //percent of left space
    } chunk_node_state;

    typedef struct struct_chunk_meta {
        std::string chunk_hash;
        std::unordered_set<std::string> chunk_node_ip;
    } chunk_meta;

    // typedef struct struct_file_meta{
    //     std::string file_name;
    //     std::vector<chunk_meta> chunks;
    // } file_meta;

    

#endif //DEFINE_H