#pragma once

#include <string>
#include <vector>

#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "include/httplib.h"
#include "include/json.hpp"

using namespace std;
using json = nlohmann::json;

class RequestManager
{
  string host;

public:
  RequestManager(string host)
  {
    this->host = host;
  }

  json get(string path)
  {
    json json_response;

    try
    {
      httplib::Client cli{host};
      const auto response = cli.Get(path);
      json_response = json::parse(response->body);
    }
    catch (const exception &e)
    {
      throw e;
    }

    return json_response;
  }
};
