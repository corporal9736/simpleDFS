#include <iostream>
#include "client.h"

client::client(){}

void client::connect(const std::string& master_addr){
    // TODO: need to add failure catch and change this->is_connected
    address master(master_addr);
    this->rpc_client = new rpc::client(master.getIp(), master.getPort());
}

void client::run(){
    std::cout << "well come to simpleDFS, input \
        'help' to get more information" <<std::endl;
    while(1){
        std::cout << "(simpleDFS) ";
        std::string input;
        std::getline(std::cin, input);
        this->parseInput(input);
    }
}

void client::parseInput(const std::string& command){
    // TODO: write a parser to parse input as listed
    // first check this->is_connected, if not, print
    // "not connected, please connect first"
    //
    // connect:
    // args: a string format to ip:port, such as
    // 127.0.0.1:8080
    // call this->connect to establish a new connection
    // return "failed, please try again" if failed and
    // "success" if connected
    //
    // ls:
    // args: a string, may be a file or path
    // if is a path, return the file and sub path name
    // if is a file, return the string itself
    // if not exist, return "not exist"
    //
    // put:
    // args: two strings, the first one is the target path
    // and the second one is the file name
    // if path not exist, return "path not exist"
    // if on uploading, print current process by percent
    // and print "success" on complete
    //
    // get:
    // args: a string, the path of the file
    // if path not exist, return "path not exist"
    // if on getting, print current process by percent
    // and print "success" on cpmplete
    //
    // info:
    // args: a string, the path of the file
    // if path not exist, return "path not exist"
    // if found, print the basic info defined in file
    // sturct
    //
    // help:
    // no args
    // print some help information
    std::cout << command << std::endl;
}

void client::ls(const std::string& path){}
void client::put(const std::string& path, const std::string& name){}
void client::get(const std::string& path){}
void client::info(const std::string& path){}
void client::help(){}
