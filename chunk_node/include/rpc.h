#ifndef RPC_H
#define RPC_H

#include <string>

// used by client

// TODO: how to return a file
std::string get(const std::string& hash);

void put(const std::string& content, const std::string& hash);


#endif //RPC_H