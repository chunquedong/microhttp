#! /usr/bin/env fan

using build
class Build : BuildGroup
{
  new make()
  {
    childrenScripts =
    [
      `buildClient.fan`,
      `buildServer.fan`,
      `buildTestServer.fan`,
      `buildTestClient.fan`
    ]
  }
}