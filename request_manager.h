#pragma once

#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
#include "include/json.hpp"

using namespace std;

class RequestManager
{
  string host;

public:
  RequestManager(string host)
  {
    this->host = host;
  }

  nlohmann::json get(string path)
  {
    string url = this->host + path;

    // TODO: make request

    nlohmann::json response;

    return response;
  }
};
