#include <iostream>
#include <stdlib.h>
#include "include/color.hpp"
#include "include/VariadicTable.h"
#include "include/json.hpp"
#include "include/HTTPRequest.hpp"
#include "test.h"
#include "user_input.h"

using namespace std;

vector<string> valid_sort_columns = {"symbol", "price", "price_change", "volume", "number_of_trades", "trend"};

int main(int argc, char *argv[])
{
  for (const auto &sortInput : userInput.sort)
  {
    cout << "Column: " << sortInput.column << ", Order: " << sortInput.order << endl;
  }
  cout << "Limit: " << userInput.limit << endl;
  for (const auto &pairsInput : userInput.pairs)
  {
    cout << "Pair: " << pairsInput << endl;
  }
  cout << "Ignore Errors: " << userInput.ignoreErrors << endl;
  cout << "Live: " << userInput.live << endl;
  cout << "Trend: " << userInput.trend << endl;
  // // Print the sub-vectors to verify the result
  // for (const auto &subVector : userArgsSubVectors)
  // {
  //   for (const auto &option : subVector)
  //   {
  //     cout << option << " ";
  //   }
  //   cout << endl;
  // }

  return 0;
}
