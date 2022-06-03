#ifndef RPC_H
#define RPC_H

#include <string>
#include "chunk_node.h"
#include "rpc/server.h"

// used by client

// TODO: how to return a file
std::string get(const std::string& hash);

void put(const std::string& content, const std::string& hash);

void bindAll(rpc::server& server);


#endif //RPC_H