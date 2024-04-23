#include <stdlib.h>

#include <iostream>

#include "include/VariadicTable.h"
#include "include/color.hpp"
#include "include/json.hpp"

#include "user_input.h"
#include "request_manager.h"
#include "include/json.hpp"
#include "binance_data_model.h"
#include "display_manager.h"
#include "conputation_manager.h"
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[])
{
  UserInput user_input = UserInput::parse(argc, argv);

  RequestManager request_manager("https://api2.binance.com");

  ComputationManager computation_manager(user_input);

  while (true)
  {
    nlohmann::json data = request_manager.get("/api/v3/ticker/24hr");

    vector<BinanceDataModel> binance_data_models = BinanceDataModel::parse_array(data);

    computation_manager.add_binance_models(binance_data_models);

    vector<DisplayDataModel> display_models = computation_manager.get_display_models();

    DisplayManager::display(display_models);

    if (user_input.live > 0)
    {
      sleep(user_input.live);
    }
    else
    {
      break;
    }
  }
  return 0;
}
