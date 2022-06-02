#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include "rpc/client.h"
#include "define.h"
#include "singleton.h"
class client:public PublicSingleton<client>{
    friend class PublicSingleton<client>;
    public:
        client(const client&) = delete;
        client& operator=(const client&) = delete;
        void run();
        void connect(const std::string& master_addr);
        void ls(const std::string& path);
        void put(const std::string& path, const std::string& name);
        void get(const std::string& path);
        void info(const std::string& path);
        void help();
        void parseInput(const std::string& command);
    private:
        client();
        bool is_connected;
        address* master_addr;
        rpc::client* rpc_client;
};

#endif //CLIENT_H
