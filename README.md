# httpsuite
Cross-platform C++ library for creating an embedded HTTP server/client.

Base on libmicrohttpd and curl.

# Server Example
```
int main(int argc, const char * argv[]) {
    Server server;
    server.port = 8000;
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
```
# Client Example
```
int main(int argc, const char * argv[]) {
    HttpClient cli;
    int rc = cli.get("http://localhost:8000/index");
    printf("res %d, %s\n", rc, cli.result.c_str());
    return 0;
}
```
