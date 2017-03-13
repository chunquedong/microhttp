
#ifndef httpclient_hpp
#define httpclient_hpp

#include <string>
#include <curl/curl.h>

namespace httpsuite {

class HttpClient {
    CURL *curl;
public:
    std::string result;
public:
    HttpClient();
    ~HttpClient();

    int get(const char *url);
};

}
#endif /* httpclient_hpp */