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
            std::unordered_set<address, address_hash> chunk_node_ip;
    };

    // typedef struct struct_file_meta{
    //     std::string file_name;
    //     std::vector<chunk_meta> chunks;
    // } file_meta;

    

#endif //DEFINE_H
