#ifndef RPC_H
#define RPC_H
#include "define.h"
#include "master.h"
#include "utils.h"


void bindAll(rpc::server& server);
// just for test
std::string test();

// used by client

// get file meta data from master
// the meta should be in order
std::string get(const std::string& file_path);

// put file to master, return a vector of chunk node address
// which the chunks will be sent to
// TODO: check how to express size
//path是在目录树的path不是client的path
std::string put(const std::string& path,const std::string name,const std::string comment, int size);//这里涉及到传文件的问题

// return the basic info of a file
// if not exist return "not exist"
// if menu return the child file info
std::string getInfo(const std::string& file_path);//string: "filename:namename \n comment:comment \n size:size"


//展示文件目录下的所有文件名以及子文件夹名
//string: "dir:test1","file:testFile1"
std::vector<std::string> ls(const std::string& dir_path);//dir_path:  "/root/dir1/dir2"

//success:0 fail:-1
int mkdir(const std::string& dir_path);

int removeFile(const std::string& file_path);

int removeDir(const std::string& dir_path);

// used by chunk_node
// int chunkNodeSignIn(const chunk_node_state& state);


// update master->states
// also can be used for new chunk_node online
void updateState(const chunk_node_state& state);

// call this every minute to show chunk_node still alive
// if not called for three times, delete this chunk_node
// from master->state
void heartBeat();//emm

#endif //RPC_H
