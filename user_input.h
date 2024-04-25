#pragma once

#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class SortInput
{
public:
  string column;
  string order; // asc or desc
};

class UserInput
{
public:
  // flag: --sort
  vector<SortInput> sort_inputs;

  // flag: --limit
  int limit = 0;

  // flag: --pairs
  vector<string> pairs;

  // flag: --ignore-errors
  bool ignore_errors = false;

  // flag: --live
  int live = 0;

  // flag: --trend
  int trend = 0;

  void my_runtime_error(string error)
  {
    if (!ignore_errors)
    {
      throw runtime_error(error);
    }
  }

  static UserInput parse(int argc, char *argv[])
  {
    // convert char* to string
    vector<string> args;
    for (int i = 0; i < argc; i++)
    {
      string arg(argv[i]);
      args.push_back(arg);
    }

    // split arguments into array of flags with each flag at the beginning of the array
    vector<vector<string>> flags;
    vector<string> tmp_flag_args;

    for (int i = 0; i < args.size(); i++)
    {
      string a = args[i];
      std::size_t found = a.rfind("--");
      if (found == 0)
      {
        if (!tmp_flag_args.empty())
        {
          flags.push_back(tmp_flag_args);
          tmp_flag_args.clear();
        }

        tmp_flag_args.push_back(a);
      }
      else if (!tmp_flag_args.empty())
      {
        tmp_flag_args.push_back(a);
      }
      else
      {
        // TODO: throw exception if we dont want to allow wrong arguments
        // throw runtime_error("Invalid argument: " + a);
      }
    }

    // find if there is a "ignore-errors" flag
    UserInput user_input;
    for (int i = 0; i < flags.size(); i++)
    {
      vector<string> flag_args = flags.at(i);
      if (flag_args.front() == "--ignore-errors")
      {
        user_input.ignore_errors = true;
        break;
      }
    }

    // add flags to user input

    for (int i = 0; i < flags.size(); i++)
    {
      vector<string> flag_args = flags.at(i);

      if (flag_args.front() == "--sort")
      {
        if (flag_args.size() % 2 == 0)
        {
          throw runtime_error("Sort arguments must be of form 'column pair'");
        }

        for (int j = 1; j < flag_args.size(); j += 2)
        {
          string column = flag_args.at(j);
          string order = flag_args.at(j + 1);

          if (order != "asc" && order != "desc")
          {
            user_input.my_runtime_error("Invalid sort order: " + order);
            continue;
          }

          if (column != "symbol" && column != "price" && column != "volume" && column != "price_change" && column != "trend" && column != "number_of_trades")
          {
            user_input.my_runtime_error("Invalid sort column: " + column);
            continue;
          }

          SortInput sort_input;
          sort_input.column = column;
          sort_input.order = order;
          user_input.sort_inputs.push_back(sort_input);
        }
      }
      else if (flag_args.front() == "--limit")
      {
        if (flag_args.size() == 2)
        {
          string limit_arg_str = flag_args.at(1);
          try
          {
            int limit_arg = stoi(limit_arg_str);

            if (limit_arg >= 0 && limit_arg <= 100)
            {
              user_input.limit = limit_arg;
            }
            else
            {
              user_input.my_runtime_error("Invalid limit argument: " + limit_arg_str + ". Only positive integers are allowed between 0 and 100.");
            }
          }
          catch (...)
          {
            user_input.my_runtime_error("Invalid limit argument: " + limit_arg_str);
          }
        }
        else
        {
          user_input.my_runtime_error("Limit must have only 1 argument.");
        }
      }
      else if (flag_args.front() == "--pairs")
      {
        for (int j = 1; j < flag_args.size(); j++)
        {
          string pair = flag_args.at(j);

          bool is_valid_pair = true;

          for (int k = 0; k < pair.size(); k++)
          {
            char c = pair.at(k);
            if (!iswalnum(c) && c != '*')
            {
              user_input.my_runtime_error("Invalid pair argument: " + pair);

              is_valid_pair = false;
              break;
            }
          }

          if (is_valid_pair)
          {
            user_input.pairs.push_back(pair);
          }
        }
      }
      else if (flag_args.front() == "--live")
      {
        user_input.live = 5; // default interval

        if (flag_args.size() == 2)
        {
          string live_arg_str = flag_args.at(1);
          try
          {
            int live_arg = stoi(live_arg_str);

            if (live_arg >= 5 && live_arg <= 60)
            {
              user_input.live = live_arg;
            }
            else
            {
              user_input.my_runtime_error("Invalid live argument: " + live_arg_str + ". Only positive integers are allowed between 5 and 60.");
            }
          }
          catch (...)
          {
            user_input.my_runtime_error("Invalid live argument: " + live_arg_str);
          }
        }
        else
        {
          user_input.my_runtime_error("Live must have only 1 argument or no argument.");
        }
      }
      else if (flag_args.front() == "--trend")
      {
        if (flag_args.size() == 2)
        {
          string trend_arg_str = flag_args.at(1);
          try
          {
            int trend_arg = stoi(trend_arg_str);

            if (trend_arg >= 2 && trend_arg <= 10)
            {
              user_input.trend = trend_arg;
            }
            else
            {
              user_input.my_runtime_error("Invalid trend argument: " + trend_arg_str + ". Only positive integers are allowed between 2 and 10.");
            }
          }
          catch (...)
          {
            user_input.my_runtime_error("Invalid trend argument: " + trend_arg_str);
          }
        }
        else
        {
          user_input.my_runtime_error("Trend must have only 1 argument");
        }
      }
      else if (flag_args.front() == "--ignore-errors")
      {
        user_input.ignore_errors = true;
      }
      else
      {
        throw runtime_error("Invalid flag: " + flag_args.front());
      }
    }

    return user_input;
  }
};
