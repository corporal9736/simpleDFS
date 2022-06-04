#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include "define.h"

std::vector<std::string> split(const std::string &str, const std::string &pattern);

std::vector<std::string> getDirInfo(const std::string &JsonInfo);

std::string generateDirInfo(const std::vector<std::string> &dirInfo);

std::vector<chunk_meta> getChunkMeta(const std::string &JsonInfo);

std::string generateChunkMeta(const std::vector<chunk_meta> &chunkMeta);

chunk_node_state getChunkNodeState(const std::string &JsonInfo);

std::string generateChunkNodeState(const chunk_node_state &chunkNodeState);

#endif //UTILS_H
