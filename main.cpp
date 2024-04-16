#include <stdlib.h>

#include <iostream>

#include "include/VariadicTable.h"
#include "include/color.hpp"
#include "include/json.hpp"
#include "request_manager.h"
#include "user_input.h"

using namespace std;

// vector<string> valid_sort_columns = {"symbol", "price", "price_change", "volume", "number_of_trades", "trend"};

int main(int argc, char *argv[])
{
    UserInput userInput = UserInput::parse(argc, argv);
    userInput.print();

    RequestManager requestManager;
    vector<BianceDataModel> dataModels = requestManager.get_data();

    for (const auto &model : dataModels)
    {
        std::cout << "Symbol: " << model.symbol << std::endl;
        std::cout << "Price: " << model.price << std::endl;
        std::cout << "Price Change: " << model.priceChange << std::endl;
        std::cout << "Volume: " << model.volume << std::endl;
        std::cout << "Number of Trades: " << model.numberOfTrades << std::endl;
        std::cout << "-------------------------" << std::endl;
    }

    return 0;
}
