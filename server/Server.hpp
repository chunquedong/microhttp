

#ifndef Server_hpp
#define Server_hpp

#include "Request.hpp"
#include "microhttpd.h"
#include <unordered_map>
#include <functional>

namespace httpsuite {

class Server {
    struct MHD_Daemon *d = NULL;
    bool stoped = false;

    typedef std::function<void(Request &req, Response &res)> Hander;

    std::unordered_map<std::string, Hander> handlers;

public:
    int port = 8000;
    int thread = 20;
public:
    Server();
    ~Server();

    void stop() { stoped = true; }

    bool start();

    void addHandler(const std::string &partten, Hander handler) {
        handlers[partten] = handler;
    }

    virtual void onReceive(Request &req, Response &res);

/////////////////////////////

    static enum MHD_Result request_receive(void *cls,
                       struct MHD_Connection *connection,
                       const char *url,
                       const char *method,
                       const char *version,
                       const char *upload_data, size_t *upload_data_size, void **ptr);

    static void request_completed (void *cls, struct MHD_Connection *connection,
                       void **con_cls, enum MHD_RequestTerminationCode toe);
};

}

#endif /* Server_hpp */
