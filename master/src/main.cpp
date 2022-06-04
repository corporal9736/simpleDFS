#include <iostream>
#include <cstdlib>
#include "rpc.h"

int main(){
    auto& m = master::getInstance();
    m.init("/home/thunder/CODE/c/simpleDFS/master/config.json");
    rpc::server m_server(m.getPort());
    bindAll(m_server);
    // master_test();
    m_server.run();
    return 0;
}