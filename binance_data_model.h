#pragma once

#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
#include "include/json.hpp"

using namespace std;

class BinanceDataModel
{

public:
  static BinanceDataModel parse(nlohmann::json &json)
  {

    //
  }

  static vector<BinanceDataModel> parse_array(nlohmann::json &json)
  {
    //
  }
};
