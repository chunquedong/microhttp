#! /usr/bin/env fan

using fmake

class Build : BuildCpp
{
    new make()
    {
        name = "httpsuiteClient"
        summary = "http client"
        outType = TargetType.lib
        version = Version("1.0.0")
        srcDirs = [`curl/`, `client/`]

        extConfigs["cppflags"] = "-std=c++14"
        if (Env.cur.os == "win32") {
          defines = ["CURL_DISABLE_LDAP CURL_STATICLIB"]
        } else {
          defines = ["__LINUX__"]
          extLibs = ["pthread", "z"]
          if (Env.cur.os == "linux") {
            extLibs = ["pthread","rt","z"]
          }
        }
    }
}