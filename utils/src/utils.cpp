#include <vector>
#include "utils.h"


std::vector<std::string> split(const std::string &str, const std::string &pattern)
{
    std::vector<std::string> res;
    if(str == "")
        return res;
    //在字符串末尾也加入分隔符，方便截取最后一段
    std::string strs = str + pattern;
    size_t pos = strs.find(pattern);

    while(pos != strs.npos)
    {
        std::string temp = strs.substr(0, pos);
        res.push_back(temp);
        //去掉已分割的字符串,在剩下的字符串中进行分割
        strs = strs.substr(pos+1, strs.size());
        pos = strs.find(pattern);
    }

    return res;
}

std::tuple<std::string, int> parseAddress(std::string address){
    auto vec = split(address,":");
    std::string ip = vec[0];
    int port = std::stoi(vec[1]);
    return {ip, port};
}