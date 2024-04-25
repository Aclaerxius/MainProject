#include <stdlib.h>

#include <iostream>

#include "include/VariadicTable.h"
#include "include/termcolor.hpp"
#include "include/json.hpp"
#include "user_input.h"
#include "request_manager.h"
#include "binance_data_model.h"
#include "display_manager.h"
#include "conputation_manager.h"
#include <unistd.h>
#include <chrono>

using namespace std::chrono;
using namespace std;

int main(int argc, char *argv[])
{
  UserInput user_input = UserInput::parse(argc, argv);

  RequestManager request_manager("https://api2.binance.com");

  ComputationManager computation_manager(user_input);

  int64_t last_requested_time = 0;

  while (true)
  {
    int64_t current_time = duration_cast<seconds>(system_clock::now().time_since_epoch()).count();

    if (current_time - last_requested_time >= user_input.live)
    {
      nlohmann::json data = request_manager.get("/api/v3/ticker/24hr");
      last_requested_time = duration_cast<seconds>(system_clock::now().time_since_epoch()).count();
      ;

      vector<BinanceDataModel> binance_data_models = BinanceDataModel::parse_array(data);
      computation_manager.add_binance_models(binance_data_models);
    }

    vector<DisplayDataModel> display_models = computation_manager.get_display_models();
    DisplayManager::display(user_input.trend >= 2, last_requested_time, display_models);

    if (user_input.live == 0)
    {
      break;
    }

    sleep(1);
  }

  return 0;
}
