

#include "Request.hpp"
#include "platform.h"

using namespace httpsuite;

Request::Request(void *cls,
        struct MHD_Connection *connection,
        const char *url,
        const char *method,
        const char *version,
        const char *upload_data, size_t *upload_data_size, void **ptr)
    :
    _cls(cls),
    _connection(connection),
    _url(url),
    _method(method),
    _version(version),
    _body(upload_data, *upload_data_size),
    _ptr(ptr)
{
}

const char *Request::param(const char *name, const char *defVal) {
    const char *val = MHD_lookup_connection_value (_connection, MHD_GET_ARGUMENT_KIND, name);
    if (val != NULL)  return val;

    val = MHD_lookup_connection_value (_connection, MHD_POSTDATA_KIND, name);
    if (val != NULL)  return val;

    return defVal;
}

const char *Request::header(const char *name) {
    return MHD_lookup_connection_value (_connection, MHD_HEADER_KIND, name);
}

const char *Request::cookie(const char *name) {
    return MHD_lookup_connection_value (_connection, MHD_COOKIE_KIND, name);
}

Response::Response() : response(NULL) {
    status_code = MHD_HTTP_OK;
}
Response::~Response() {
    MHD_destroy_response (response);
}

void Response::sendMem(char *data, size_t size, bool copy) {
    if (data == 0) return;

    enum MHD_ResponseMemoryMode respmem = copy ? MHD_RESPMEM_MUST_COPY : MHD_RESPMEM_MUST_FREE;

    if (response == NULL) {
        response = MHD_create_response_from_buffer (size, data, respmem);
    }
    if (response == NULL) {
        if (MHD_RESPMEM_MUST_FREE) {
            free (data);
            data = NULL;
        }
        return;
    }

    for (std::map<std::string, std::string>::iterator itr=headers.begin();
         itr != headers.end(); ++itr) {
        MHD_add_response_header (response, itr->first.c_str(), itr->second.c_str());
    }
}

void Response::sendString(std::string &str) {
    sendMem((char*)str.c_str(), str.size(), true);
}