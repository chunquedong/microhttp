
#include <stdlib.h>
#include "Server.hpp"
using namespace httpsuite;

int main(int argc, const char * argv[]) {
    printf("%s\n", argv[0]);
    int port = 8000;
    if (argc > 1) {
        port = atoi(argv[1]);
    }

    Server server;
    server.port = port;
    server.addHandler("/index", [](Request &req, Response &res){
        std::string s = "Hello World";
        res.sendString(s);
        return;
    });

    if (!server.start()) {
        return 1;
    }
    return 0;
}

