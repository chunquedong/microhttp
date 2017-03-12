
//#include <stdlib.h>
#include "httpsuiteClient/HttpClient.hpp"
using namespace httpsuite;

int main(int argc, const char * argv[]) {
    HttpClinet cli;
    int rc = cli.get("http://localhost:8000/index");
    printf("res %d, %s\n", rc, cli.result.c_str());
    return 0;
}

