
#include "HttpClient.hpp"
using namespace httpsuite;

HttpClinet::HttpClinet() {
    curl = curl_easy_init();
}

HttpClinet::~HttpClinet() {
    if (curl) {
        curl_easy_cleanup(curl);
    }
}

size_t OnWriteData(char *ptr, size_t size, size_t nmemb, void *userdata) {
    HttpClinet *me = (HttpClinet*) userdata;
    int asize = size*nmemb;
    me->result.append(ptr, asize);
    return asize;
}

int HttpClinet::get(const char *url) {
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, OnWriteData);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, this);
    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");

    CURLcode res = curl_easy_perform(curl);
    int responseCode = 0;
    if(res == CURLE_OK) {
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &responseCode);
        //resultStream.rewind();
        return responseCode;
    }
    return -1;
}