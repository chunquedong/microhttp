

#include "Server.hpp"
#include "platform.h"

using namespace httpsuite;

Server::Server() {

}
Server::~Server() {

}

void Server::onReceive(Request &req, Response &res) {
    std::string url = req.url();
    for (std::unordered_map<std::string, Hander>::iterator itr=handlers.begin();
         itr != handlers.end(); ++itr) {
        if (url.find(itr->first) == 0) {
            Hander handler = itr->second;
            handler(req, res);
            break;
        }
    }
}

enum MHD_Result Server::request_receive(void *cls,
                     struct MHD_Connection *connection,
                     const char *url,
                     const char *method,
                     const char *version,
                     const char *upload_data, size_t *upload_data_size, void **ptr) {

    if (NULL == *ptr) {
        Request *req = new Request(cls, connection, url, method, version, upload_data, upload_data_size, ptr);
        *ptr = req;
        return MHD_YES;
    }
    Request *req = (Request *)*ptr;

    if (upload_data && *upload_data_size > 0) {
        std::string data(upload_data, *upload_data_size);
        req->body() += data;
        *upload_data_size = 0;
        return MHD_YES;
    }

    Server *s = (Server*)cls;
    Response res;
    s->onReceive(*req, res);

    if (res.response == NULL) return MHD_NO;
    enum MHD_Result ret = MHD_queue_response (connection, res.status_code, res.response);
    return ret;
}

void Server::request_completed (void *cls, struct MHD_Connection *connection,
                   void **con_cls, enum MHD_RequestTerminationCode toe) {
    Request *req = (Request *)*con_cls;
    if (req) {
        delete req;
    }
    *con_cls = NULL;
}

bool Server::start() {
#if defined(__linux__)
    d = MHD_start_daemon (MHD_USE_EPOLL_INTERNALLY
                          | MHD_USE_EPOLL | MHD_USE_EPOLL_TURBO,
                          port,
                          NULL, NULL, &request_receive, (void*)this
                          , MHD_OPTION_NOTIFY_COMPLETED, request_completed, NULL,
                          MHD_OPTION_CONNECTION_TIMEOUT, (unsigned int) 15,
                          MHD_OPTION_THREAD_POOL_SIZE, thread,
                          MHD_OPTION_CONNECTION_LIMIT, (unsigned int) 1000,
                          MHD_OPTION_END);
#elif 0
    d = MHD_start_daemon (MHD_USE_THREAD_PER_CONNECTION | MHD_USE_DEBUG,
                          port,
                          NULL, NULL, &request_receive, (void*)this
                          , MHD_OPTION_NOTIFY_COMPLETED, request_completed, NULL,
                          MHD_OPTION_END);
#else
    d = MHD_start_daemon (MHD_USE_AUTO | MHD_USE_INTERNAL_POLLING_THREAD | MHD_USE_DEBUG,
                          port,
                          NULL, NULL, &request_receive, (void*)this
                          , MHD_OPTION_NOTIFY_COMPLETED, request_completed, NULL,
                          MHD_OPTION_CONNECTION_TIMEOUT, (unsigned int) 15,
                          MHD_OPTION_THREAD_POOL_SIZE, thread,
                          MHD_OPTION_CONNECTION_LIMIT, (unsigned int) 1000,
                          MHD_OPTION_END);
#endif
    if (d == NULL)
        return false;

    printf("server start at %d\n", port);

    stoped = false;
    while (!stoped) {
        sleep(10);
    }
    MHD_stop_daemon (d);
    return true;
}
