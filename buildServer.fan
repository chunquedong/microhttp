#! /usr/bin/env fan

using fmake

class Build : BuildCpp
{
    new make()
    {
        name = "httpsuiteServer"
        summary = "http server"
        outType = TargetType.lib
        version = Version("1.0.0")
        srcDirs = [`microhttpd/`, `server/`]
        excludeSrc = Regex("connection_https.c")
        extConfigs["cppflags"] = "-std=c++14"
    }
}