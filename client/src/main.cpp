#include <iostream>
#include "client.h"

int main(int argc, char* argv[]){
    // TODO: read args from main and decide:
    // if get no args, use client->run and print
    // tips to ask for connect
    // if get one args, it should be address formatted as 
    // "127.0.0.1:8080". check and try to connect and print
    // result
    auto& cl = client::getInstance();
    cl.run();
    return 0;
}
