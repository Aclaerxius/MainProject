#pragma once

#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
#include "include/json.hpp"

using namespace std;

class DisplayDataModel
{
public:
  string symbol;
  double price;
  double price_change;
  double volume;
  long number_of_trades;
  double trend;
};
