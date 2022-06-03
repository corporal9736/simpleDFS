#ifndef DEFINE_H
#define DEFINE_H
#include <vector>
#include <string>
#include <unordered_set>

    class address{
        public:
            address();
            address(int *ip, int port);
            address(const std::string& addr);
            address(const address& addr);
            const address& operator=(const address& addr);
            const std::string getIp();
            const int getPort();
            uint8_t ip[4];
            uint16_t port;
    };

    class address_hash{
        public:
            std::size_t operator()(const address& addr){
                return std::hash<uint8_t>()(addr.ip[0]) ^
                        std::hash<uint8_t>()(addr.ip[1]) ^
                        std::hash<uint8_t>()(addr.ip[2]) ^
                        std::hash<uint8_t>()(addr.ip[3]) ^
                        std::hash<uint16_t>()(addr.port);
            }
    };
    class config {
        public:
            config(const std::string& path);
            address master_ip;
            std::vector<address> chunk_node_ip;
    };

    class chunk_node_state {
        public:
            chunk_node_state();
            address chunk_node_ip;
            int storge_left; //percent of left space
    };

    class chunk_meta {
        public:
            chunk_meta();
            std::string chunk_hash;
            // std::unordered_set<address, address_hash> chunk_node_ip;
            std::vector<chunk_node_state> chunk_node_ip;
    };

    // typedef struct struct_file_meta{
    //     std::string file_name;
    //     std::vector<chunk_meta> chunks;
    // } file_meta;

    class file_meta{
        public:
            file_meta();
            std::string file_name;
            std::string comments;
            std::vector<chunk_meta> chunks;
    };

    class directory_node{
        public:
            directory_node();
            std::string name;
            // std::vector<directory_node> sub_dir;
            std::vector<file_meta> files;
            int addFile(const file_meta& file);
            int delFile(const file_meta& file);
    };


    

#endif //DEFINE_H
