#pragma once

#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
#include "include/json.hpp"
#include "binance_data_model.h"
#include "display_data_model.h"
#include "user_input.h"

using namespace std;

class ComputationManager
{
  UserInput user_input;
  vector<DisplayDataModel> display_models;

public:
  ComputationManager(UserInput user_input)
  {
    this->user_input = user_input;
  }

  void add_binance_models(vector<BinanceDataModel> binance_data_models)
  {
    //
    //
  }

  vector<DisplayDataModel> get_display_models()
  {
    return display_models;
  }
};
