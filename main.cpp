#include <stdlib.h>

#include <iostream>

#include "include/HTTPRequest.hpp"
#include "include/VariadicTable.h"
#include "include/color.hpp"
#include "include/json.hpp"
#include "request_manager.h"
#include "test.h"
#include "user_input.h"

using namespace std;

// vector<string> valid_sort_columns = {"symbol", "price", "price_change", "volume", "number_of_trades", "trend"};

int main(int argc, char *argv[]) {
    UserInput userInput = UserInput::parse(argc, argv);
    userInput.print();

    return 0;
}
