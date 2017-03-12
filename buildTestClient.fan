#! /usr/bin/env fan

using fmake

class Build : BuildCpp
{
    new make()
    {
        name = "testClient"
        summary = "http client test"
        outType = TargetType.exe
        version = Version("1.0.0")
        srcDirs = [`testClient/`]
        depends = ["httpsuiteClient 1.0.0", "httpsuiteServer 1.0.0"]

        extConfigs["cppflags"] = "-std=c++14"
        if (Env.cur.os != "win32") {
          extLibs = ["pthread", "z"]
          if (Env.cur.os == "linux") {
            extLibs = ["pthread","rt","z"]
          }
        }
    }
}