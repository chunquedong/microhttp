
#ifndef httpclient_hpp
#define httpclient_hpp

#include <string>
#include <curl/curl.h>

namespace httpsuite {

class HttpClinet {
    CURL *curl;
public:
    std::string result;
public:
    HttpClinet();
    ~HttpClinet();

    int get(const char *url);
};

}
#endif /* httpclient_hpp */