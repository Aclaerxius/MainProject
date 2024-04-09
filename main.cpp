#include <iostream>
#include <stdlib.h>
#include "include/color.hpp"
#include "include/VariadicTable.h"
#include "include/json.hpp"
#include "include/HTTPRequest.hpp"
#include "test.h"

using namespace std;

vector<string> valid_sort_columns = {"symbol", "price", "price_change", "volume", "number_of_trades", "trend"};

class SortInput
{
public:
  string column;
  string order;
};

class UserInput
{
public:
  vector<SortInput> sortArg;
  int limitArg;
  vector<string> pairsArg;
  bool ignoreErrorsArg;
  int liveArg;
  int trendArg;

  UserInput parse(int argc, char *argv[])
  {
    void print_help();

    // store user input arguments in a vector string
    vector<string> userArgs;
    for (int i = 0; i < argc; i++)
    {
      string s(argv[i]);
      userArgs.push_back(s);
    };

    UserInput userInput;

    return userInput;
  };
};

int main(int argc, char *argv[])
{

  vector<string> userArgs;
  for (int i = 0; i < argc; i++)
  {
    string s(argv[i]);
    userArgs.push_back(s);
  }

  vector<vector<string>> userArgsSubVectors;

  for (int i = 1; i < userArgs.size(); i++)
  {
    string arg = userArgs.at(i);

    if (arg.length() > 1 && arg.at(0) == '-' && arg.at(1) == '-')
    {
      userArgsSubVectors.push_back(std::vector<std::string>());
      userArgsSubVectors.back().push_back(arg);
    }
    else
    {
      if (!userArgsSubVectors.empty())
      {
        userArgsSubVectors.back().push_back(arg);
      }
    }
  }

  class SortInput
  {
  public:
    string column;
    string order;
  };

  class UserInputArgs
  {
  public:
    vector<SortInput> sort;
    int limit;
    vector<string> pairs;
    bool ignoreErrors;
    int live;
    bool trend;
  };

  UserInputArgs userInputArgs;

  for (const auto &subVector : userArgsSubVectors)
  {
    string sub = subVector[0];
    // Sort
    // if (find(subVector.begin(), subVector.end(), "--sort") != subVector.end())
    // {
    //     // Element in vector.
    //   }
    if (sub == "--sort" && subVector.size() > 1 && subVector.size() <= 12)
    {
      for (int i = 1; i < subVector.size(); i++)
      {
        string sub1 = subVector[i];
        string sub2 = subVector[i + 1];

        SortInput newSortInput;
        newSortInput.column = sub1;

        if (sub1 == "symbol")
        {
          newSortInput.column = "symbol";
        }

        if (sub1 == "price")
        {
          newSortInput.column = "price";
        }

        if (sub1 == "price_change")
        {
          newSortInput.column = "price_change";
        }

        if (sub1 == "volume")
        {
          newSortInput.column = "volume";
        }

        if (sub1 == "number_of_trades")
        {
          newSortInput.column = "number_of_trades";
        }

        if (sub1 == "trend")
        {
          newSortInput.column = "trend";
        }

        if (sub2 == "asc")
        {
          newSortInput.order = "asc";
        }

        if (sub2 == "desc")
        {
          newSortInput.order = "desc";
        }

        if (!newSortInput.column.empty() && !newSortInput.order.empty())
        {
          userInputArgs.sort.push_back(newSortInput);
        }
        // if (sub1 != "symbol" && sub1 != "price" && sub1 != "price_change" && sub1 != "volume" && sub1 != "number_of_trades" && sub1 != "trend" && sub2 != "asc" && sub2 != "desc")
        // {
        //   cout << "ERROR" << endl;
        // }
      }
    }

    // Limit
    if (sub == "--limit")
    {
      for (int i = 1; i < subVector.size(); i++)
      {
        if (i > 0)
        {
          userInputArgs.limit = stoi(subVector[i]);
        }
      }
    }

    // Pairs
    if (sub == "--pairs")
    {
      for (int i = 1; i < subVector.size(); i++)
      {
        string newPair;
        newPair = subVector[i];
        userInputArgs.pairs.push_back(newPair);
      }
    }

    // Ignore errors
    if (sub != "--ignore-errors")
    {
      userInputArgs.ignoreErrors = false;
    }
    else
    {
      userInputArgs.ignoreErrors = true;
    }

    // Live
    if (sub != "--live")
    {
      userInputArgs.live = 0;
    }
    else
    {
      userInputArgs.live = 5;
      for (int i = 1; i < subVector.size(); i++)
      {
        if (i > 0 && i < 100)
        {
          userInputArgs.live = stoi(subVector[i]);
        }
        else if (i > 100)
        {
          userInputArgs.live = 100;
        }
      }
    }

    // Trend
    if (sub != "--trend")
    {
      userInputArgs.trend = false;
    }
    else
    {
      userInputArgs.trend = true;
    }
  }

  for (const auto &sortInput : userInputArgs.sort)
  {
    cout << "Column: " << sortInput.column << ", Order: " << sortInput.order << endl;
  }
  cout << "Limit: " << userInputArgs.limit << endl;
  for (const auto &pairsInput : userInputArgs.pairs)
  {
    cout << "Pair: " << pairsInput << endl;
  }
  cout << "Ignore Errors: " << userInputArgs.ignoreErrors << endl;
  cout << "Live: " << userInputArgs.live << endl;
  cout << "Trend: " << userInputArgs.trend << endl;

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
