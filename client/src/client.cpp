#include  <iostream>
#include "client.h"
#include <string.h>
#include <stdio.h>
#include <fstream>
#include <unistd.h>
#include <sys/stat.h>

int parseline(const char *cmdline, char **argv)
{
    /* 祖传代码 */
    static char array[MAXLINE]; /* holds local copy of command line */
    char *buf = array;          /* ptr that traverses command line */
    char *delim;                /* points to first space delimiter */
    int argc;                   /* number of args */

    strcpy(buf, cmdline);
    buf[strlen(buf)] = ' ';
    while (*buf && (*buf == ' ')) /* ignore leading spaces */
        buf++;

    /* Build the argv list */
    argc = 0;
    if (*buf == '\'')
    {
        buf++;
        delim = strchr(buf, '\'');
    }
    else
    {
        delim = strchr(buf, ' ');
    }

    while (delim)
    {
        argv[argc++] = buf;
        *delim = '\0';
        buf = delim + 1;
        while (*buf && (*buf == ' ')) /* ignore spaces */
            buf++;

        if (*buf == '\'')
        {
            buf++;
            delim = strchr(buf, '\'');
        }
        else
        {
            delim = strchr(buf, ' ');
        }
    }
    argv[argc] = NULL;

    return argc;
}

client::client(){}

client::~client(){}

void client::connect(const std::string &master_addr)
{
    // TODO: need to add failure catch and change this->is_connected
    address master(master_addr);
    this->rpc_client = new rpc::client(master.getIp(), master.getPort());
    std::string testinfo;

    try
    {
        // const uint64_t short_timeout = 500;
        // this->rpc_client->set_timeout(short_timeout);
        testinfo = this->rpc_client->call("test").as<std::string>();
    }
    catch (rpc::system_error &e)
    {
        std::cerr<<e.what()<<std::endl;
        return;
    }
    catch (rpc::timeout &e)
    {
        std::cerr<<e.what()<<std::endl;
        return;
    }


    if(testinfo == "test success")
    {
        std::cout<<"Connect success."<<std::endl;
        this->is_connected = true;
    }
        
    return;
}

void client::run()
{
    std::cout << "well come to simpleDFS, input \
        'help' to get more information"
              << std::endl;
    while (1)
    {
        std::cout << "(simpleDFS)>> ";
        std::string input;
        std::getline(std::cin, input);
        this->parseInput(input);
    }
}

void client::parseInput(const std::string &command)
{

    char *argv[MAXARGS];
    int argc = parseline(command.c_str(), argv);

    if (argc == 0)
    {
        std::cout << "Please input correct arguments" << std::endl;
        return;
    }

    if (!strcmp(argv[0], "connect"))
    {
        if (argc < 2)
        {
            std::cout << "Please input ip of master" << std::endl;
            return;
        }
        const std::string address(argv[1]);
        this->connect(address);
    }
    else if (!strcmp(argv[0], "help"))
    {
        this->help();
    }
    else if (!strcmp(argv[0], "quit"))
    {
        exit(0);
    }
    else if(!this->is_connected){
        std::cout<<"please connect the server first!"<<std::endl;
        return;
    }
    else if (!strcmp(argv[0], "ls"))
    {
        if (argc<2)
        {
            std::cout<< "Please input directory!" <<std::endl;
            return;
        }
        const std::string dir(argv[1]);
        this->ls(dir);
    }
    else if (!strcmp(argv[0], "put"))
    {
        if (argc < 4)
        {
            std::cout << "Please input correct args --> put <dest> <source> <comment>" << std::endl;
            return;
        }
        const std::string local_file(argv[1]);
        const std::string server_file(argv[2]);
        const std::string comment(argv[3]);
        this->put(local_file, server_file, comment);
    }
    else if (!strcmp(argv[0], "get"))
    {
        if (argc < 3)
        {
            std::cout << "Please input correct args --> get <source> <dest>" << std::endl;
            return;
        }
        const std::string server_file(argv[1]);
        const std::string local_file(argv[2]);
        this->get(server_file, local_file);
    }
    else if (!strcmp(argv[0], "info"))
    {
        if (argc < 2)
        {
            std::cout<< "Please input file path!" <<std::endl;
            return;
        }
        const std::string server_file(argv[1]);
        this->info(server_file);
    }
    else if(!strcmp(argv[0], "mkdir"))
    {
        if (argc < 2)
        {
            std::cout<< "Please input directory path! "<<std::endl;
            return;
        }
        const std::string dir(argv[1]);
        this->mkdir(dir);
    }
    else if(!strcmp(argv[0], "rm"))
    {
        if (argc < 2)
        {
            std::cout<< "Please input file path! "<<std::endl;
            return;
        }
        const std::string file(argv[1]);
        this->removeFile(file);
    }
    else if(!strcmp(argv[0], "rmdir"))
    {
        if (argc < 2)
        {
            std::cout<< "Please input directory path! "<<std::endl;
            return;
        }
        const std::string dir(argv[1]);
        this->removeDir(dir);
    }
    else
    {
        std::cerr << "Undefined operation " << argv[0] << std::endl;
        std::cerr << "Using \"help\" to get usage" << std::endl;
        return;
    }

    std::cout << command << std::endl;
}

void client::ls(const std::string &server_file) {
    std::vector<std::string> dir_info = this->rpc_client->call("ls", server_file)
                                    .as<std::vector<std::string>>();
    std::vector<std::string>::iterator i;
    for(i=dir_info.begin();i!=dir_info.end();i++)
    {
        std::cout<<(*i)<<std::endl;
    }
    return;
}

void client::put(const std::string &local_file, const std::string &server_file, const std::string &comment)
{
    struct stat statbuf;
    int filesize;
    if (stat(local_file.c_str(), &statbuf) == 0)
    {
        filesize = statbuf.st_size;  /* long to size_f */
    }
    else
    {
        std::cerr << "File: " << local_file << " not exist!" << std::endl;
        return;
    }
    // std::cout<<"filesize: "<<filesize<<std::endl;
    std::string info = this->rpc_client->call("put", server_file, comment, filesize).as<std::string>();
    // std::cout<<info<<std::endl;
    std::vector<chunk_meta> target = getChunkMeta(info);
    // int block_size = this->rpc_client->call("getBlockSize").as<int>(); /* 获取块大小，还没有这个接口 */
    int block_size = 1024*1024*64;

    std::vector<chunk_meta>::iterator hash_iter;
    std::vector<address>::iterator node_iter;

    //读取文件的READBUFSIZE大小并转化为std::string
    std::ifstream file(local_file, std::ios::binary);
    std::string file_content((std::istreambuf_iterator<char>(file)),
                             std::istreambuf_iterator<char>());
    std::cout<<"file_content_size: "<<file_content.size()<<std::endl;
    file.close();
    int i=0;
    for (hash_iter = target.begin(); hash_iter != target.end(); hash_iter++)
    {
        std::string content=file_content.substr(i*block_size, block_size);

        // const std::string content(readbuf);
        // std::cout<<content.size()<<std::endl;
        std::cout<<"uploading chunk: "<<hash_iter->chunk_hash<<std::endl;
        for (node_iter = hash_iter->chunk_node_ip.begin(); node_iter != hash_iter->chunk_node_ip.end(); node_iter++)
        {
            std::string ip = node_iter->getIp();
            int port = node_iter->getPort();
            rpc::client node_client(ip, port);
            node_client.call("put", content, hash_iter->chunk_hash);
        }
        i++;
    }
    std::cout << std::endl;

    return;
}

void client::get(const std::string &server_file, const std::string &local_file)
{
    std::string info = this->rpc_client->call("get", server_file).as<std::string>();
    std::vector<chunk_meta> target = getChunkMeta(info);
    if (target.size() == 0)
    {
        std::cout << "No file " << server_file << "exist in the server" << std::endl;
        return;
    }

    std::ofstream dest;
    dest.open(local_file, std::ios::out);
    if(! dest)
    {
        std::cerr<< "Failed to open the file !"<<std::endl;
        return;
    }
    std::vector<chunk_meta>::iterator hash_iter;
    std::vector<address>::iterator node_iter;

    /* 同步调用，写起来简单，之后可以改异步调用 */
    for (hash_iter = target.begin(); hash_iter != target.end(); hash_iter++)
    {
        std::string content;
        int hash_read_success = 0;
        for (node_iter = hash_iter->chunk_node_ip.begin(); node_iter != hash_iter->chunk_node_ip.end(); node_iter++)
        {
            std::string ip = node_iter->getIp();
            int port = node_iter->getPort();
            rpc::client node_client(ip, port);

            try
            {
                const uint64_t short_timeout = 500;
                node_client.set_timeout(short_timeout);
                content = node_client.call("get", hash_iter->chunk_hash).as<std::string>();
            }
            catch (rpc::timeout &t)
            {
                continue;
            }

            hash_read_success = 1;
            break;
        }

        if (!hash_read_success)
        {
            std::cerr << "File part missing!\nmissing hash: " << hash_iter->chunk_hash << std::endl;
            dest.close();
            return;
        }
        dest << content;
    }

    dest.close();

    return;
}


void client::info(const std::string &server_file) {
    std::string file_info = this->rpc_client->call("getInfo", server_file).as<std::string>();
    std::cout<<file_info<<std::endl;
    return;
}

void client::mkdir(const std::string& dir_path)
{
    int state = this->rpc_client->call("mkdir", dir_path).as<int>();
    if(state<0)
        std::cout<<"mkdir: unknown error"<<std::endl;
    else
        std::cout<<"success"<<std::endl;

    return;
}

void client::removeFile(const std::string& file_path)
{
    int state = this->rpc_client->call("removeFile", file_path).as<int>();
    if(state<0)
        std::cout<<"remove file: unknown error"<<std::endl;
    else
        std::cout<<"success"<<std::endl;

    return;
}


void client::removeDir(const std::string& dir_path)
{
    int state = this->rpc_client->call("removeDir", dir_path).as<int>();
    if(state<0)
        std::cout<<"remove directory: unknown error"<<std::endl;
    else
        std::cout<<"success"<<std::endl;

    return;
}

void client::help()
{
    std::cout << "Usage:" << std::endl;
    std::cout << "    connect <ip>:<port>            | connect to the master" << std::endl;
    std::cout << "    ls <path>                      | list the files and sub-path names" << std::endl;
    std::cout << "    put <source> <dest> <comment>  | upload the source to destination with comment" << std::endl;
    std::cout << "    get <source> <dest>            | get the file content from source to dest" << std::endl;
    std::cout << "    info <path>                    | get the basic info of file" << std::endl;
    std::cout << "    mkdir <dir>                    | make directory"<<std::endl;
    std::cout << "    rm <file>                      | remove file"<<std::endl;
    std::cout << "    rmdir <dir>                    | remove directory"<<std::endl;      
    std::cout << "    quit                           | quit client" << std::endl;
    return;
}
