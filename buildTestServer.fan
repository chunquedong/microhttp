#! /usr/bin/env fan

using fmake

class Build : BuildCpp
{
    new make()
    {
        name = "testServer"
        summary = "http server test"
        outType = TargetType.exe
        version = Version("1.0.0")
        srcDirs = [`testServer/`]
        depends = ["httpsuiteClient 1.0.0", "httpsuiteServer 1.0.0"]

        extConfigs["cppflags"] = "-std=c++14"
    }
}