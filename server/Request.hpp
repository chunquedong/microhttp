

#ifndef Request_hpp
#define Request_hpp

#include <stdio.h>
#include <map>
#include <string>

#include "microhttpd.h"

namespace httpsuite {

class Request {
    friend class Server;
private:
    void *_cls;//callback param
    struct MHD_Connection *_connection;
    const char *_url;
    const char *_method;
    const char *_version;

    std::string _body;

    void **_ptr;//context state

public:
    Request(void *cls,
            struct MHD_Connection *connection,
            const char *url,
            const char *method,
            const char *version,
            const char *upload_data, size_t *upload_data_size, void **ptr);

    const char *method() { return _method; }
    const char *url() { return _url; }

    const char *param(const char *name, const char *defVal);

    const char *header(const char *name);

    const char *cookie(const char *name);

    std::string &body() { return _body; }
};


class Response {
    friend class Server;
private:
    struct MHD_Response *response;
public:
    unsigned int status_code;
    std::map<std::string, std::string> headers;

    void sendString(std::string &str);
    void sendMem(char *data, size_t size, bool copy);

    Response();
    ~Response();

private:
    int send_response();
};

}

#endif /* Request_hpp */