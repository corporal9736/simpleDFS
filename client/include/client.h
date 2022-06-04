#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include "rpc/client.h"
#include "define.h"
#include "singleton.h"
#include "utils.h"

#define MAXLINE 1024   /* max line size */
#define MAXARGS 128    /* max args on a command line */
#define READBUFSIZE 4096


class client:public PublicSingleton<client>{
    friend class PublicSingleton<client>;
    public:
        client(const client&) = delete;
        client& operator=(const client&) = delete;
        void run();
        void connect(const std::string& master_addr);
        void ls(const std::string& server_path);
        void put(const std::string& local_file, const std::string& server_file, const std::string& comment);
        void get(const std::string& server_file, const std::string& local_file);
        void info(const std::string& server_file);
        void mkdir(const std::string & dir_path);
        void removeDir(const std::string& dir_path);
        void removeFile(const std::string& file_path);
        void help();
        void parseInput(const std::string& command);
    private:
        client();
        ~client();
        bool is_connected;
        address* master_addr;
        rpc::client* rpc_client;
};

#endif //CLIENT_H
