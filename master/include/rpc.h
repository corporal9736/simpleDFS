#ifndef RPC_H
#define RPC_H
#include "master.h"


void bindAll(rpc::server& server);
// just for test
std::string test();

// used by client

// get file meta data from master
// the meta should be in order
std::vector<chunk_meta> get(const std::string& file_path);

// put file to master, return a vector of chunk node address
// which the chunks will be sent to
// TODO: check how to express size
std::vector<chunk_meta> put(const std::string& path,const std::string name, int size);//这里涉及到传文件的问题

// return the basic info of a file
// if not exist return "not exist"
// if menu return the child file info
std::string getInfo(const std::string& file_path);//string: "filename:namename \n comment:comment \n size:size"


//展示文件目录下的所有文件名以及子文件夹名
//string: "dir:test1","file:testFile1"
std::vector<std::string> ls(const std::string& dir_path);//dir_path:  "/root/dir1/dir2"

// used by chunk_node
int chunkNodeSignIn(const std::string& ip, int port);


// update master->states
// also can be used for new chunk_node online
void updateState(const chunk_node_state& state);

// call this every minute to show chunk_node still alive
// if not called for three times, delete this chunk_node
// from master->state
void heartBeat();

#endif //RPC_H
