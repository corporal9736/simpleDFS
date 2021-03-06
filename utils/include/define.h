#ifndef DEFINE_H
#define DEFINE_H
#include <vector>
#include <string>
#include <unordered_set>
#include "json/json.h"

    class address{
        public:
            address();
            address(int *ip, int port);
            address(const std::string& addr);
            address(const address& addr);
            const address& operator=(const address& addr);
            const std::string getIp() const;
            const int getPort() const;
            const std::string to_string() const;
            bool equal(const address& addr) const;
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
            std::string root_path;
            std::vector<address> chunk_node_ip;
            int chunk_size;
    };

    class chunk_node_state {
        public:
            chunk_node_state();
            address chunk_node_ip;
            int storge_left; //percent of left space
            int last_update_time;
    };

    class chunk_meta {
        public:
            chunk_meta();
            std::string chunk_hash;
            std::vector<address> chunk_node_ip;
            const Json::Value to_json() const;
            // friend void from_json(chunk_meta& chunk);
    };

    class file_meta{
        public:
            file_meta();
            const Json::Value to_json() const;
            std::string file_name;
            std::string comments;
            int size;
            std::vector<chunk_meta> chunks;
    };

    class dir_node{
        public:
            dir_node();
            ~dir_node();
            std::string name;
            // const Json::Value to_json() const;
            std::vector<file_meta*> files;
            std::vector<dir_node*> sub_dir;
            //????????????????????????
            int addFile(file_meta* file);//?????????????????????master????????????
            int delFile(const std::string& file_name);
            int delDir(const std::string& dir_name);
            dir_node* getSubDir(const std::string& dir_name);
            file_meta* getFile(const std::string& file_name);
    };
    

#endif //DEFINE_H
