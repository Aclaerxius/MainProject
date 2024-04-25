#pragma once

#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
#include "include/json.hpp"
#include "binance_data_model.h"
#include "display_data_model.h"
#include "user_input.h"
#include <map>

using namespace std;

bool should_show_symbol(string symbol, vector<string> pair_patterns)
{
  for (int i = 0; i < pair_patterns.size(); i++)
  {
    string pattern = pair_patterns.at(i);

    if (pattern.length() == symbol.length())
    {
      bool is_match = true;

      for (int j = 0; j < symbol.length(); j++)
      {
        char symbol_char = toupper(symbol.at(j));
        char pattern_char = toupper(pattern.at(j));

        if (symbol_char != pattern_char && pattern_char != '*')
        {
          is_match = false;
          break;
        }
      }

      if (is_match)
      {
        return true;
      }
    }
  }

  return false;
}

double calculate_trend(vector<double> prices, int trend_length)
{
  if (prices.size() < trend_length)
  {
    return 0.0;
  }

  return 0.0;
}

class ComputationManager
{
  UserInput user_input;
  vector<DisplayDataModel> display_models;

  vector<map<string, BinanceDataModel>> trend_history;

public:
  ComputationManager(UserInput user_input)
  {
    this->user_input = user_input;
  }

  void add_binance_models(vector<BinanceDataModel> binance_data_models)
  {
    // filter by pairs pattern from user input
    vector<BinanceDataModel> filtered_binance_data_models;
    for (int i = 0; i < binance_data_models.size(); i++)
    {
      BinanceDataModel binance_data_model = binance_data_models.at(i);
      bool show = should_show_symbol(binance_data_model.symbol, user_input.pairs);

      if (show)
      {
        filtered_binance_data_models.push_back(binance_data_model);
      }
    }

    vector<DisplayDataModel> display_data_models;

    // convert binance data models to display data models
    for (int i = 0; i < filtered_binance_data_models.size(); i++)
    {
      BinanceDataModel model = filtered_binance_data_models.at(i);

      DisplayDataModel display_model;
      display_model.symbol = model.symbol;
      display_model.price = model.lastPrice;
      display_model.price_change = model.priceChangePercent;
      display_model.volume = model.volume;
      display_model.number_of_trades = model.count;
      display_model.trend = 0.0;

      // calculate trend
      if (user_input.trend >= 2)
      {
        vector<BinanceDataModel> trend_history_models;
        for (int j = 0; j < trend_history.size(); j++)
        {
          map<string, BinanceDataModel> trend_map = trend_history.at(j);
          BinanceDataModel trend_model = trend_map[model.symbol];
          trend_history_models.push_back(trend_model);
        }

        // add history prices
        vector<double> symbol_price_history;
        for (int j = 0; j < trend_history_models.size(); j++)
        {
          BinanceDataModel trend_model = trend_history_models.at(j);
          symbol_price_history.push_back(trend_model.lastPrice);
        }
        // add new model price
        symbol_price_history.push_back(model.lastPrice);

        display_model.trend = calculate_trend(symbol_price_history, user_input.trend);
      }

      display_data_models.push_back(display_model);
    }

    // add binance data models to history if we have trend set
    if (user_input.trend >= 2)
    {
      map<string, BinanceDataModel> tmp_map;
      for (int i = 0; i < filtered_binance_data_models.size(); i++)
      {
        BinanceDataModel binance_data_model = filtered_binance_data_models.at(i);

        tmp_map[binance_data_model.symbol] = binance_data_model;
      }

      trend_history.push_back(tmp_map);

      // remove older trend history
      if (trend_history.size() > user_input.trend)
      {
        trend_history.erase(trend_history.begin());
      }
    }

    for (int i = 0; i < user_input.sort_inputs.size(); i++)
    {
      SortInput sort_input = user_input.sort_inputs.at(i);

      if (sort_input.column == "symbol")
      {
        sort(display_data_models.begin(), display_data_models.end(), [](DisplayDataModel a, DisplayDataModel b)
             { return a.symbol < b.symbol; });
      }
      else if (sort_input.column == "price")
      {
        sort(display_data_models.begin(), display_data_models.end(), [](DisplayDataModel a, DisplayDataModel b)
             { return a.price < b.price; });
      }
      else if (sort_input.column == "price_change")
      {
        sort(display_data_models.begin(), display_data_models.end(), [](DisplayDataModel a, DisplayDataModel b)
             { return a.price_change < b.price_change; });
      }
      if (sort_input.column == "volume")
      {
        sort(display_data_models.begin(), display_data_models.end(), [](DisplayDataModel a, DisplayDataModel b)
             { return a.volume < b.volume; });
      }
      else if (sort_input.column == "number_of_trades")
      {
        sort(display_data_models.begin(), display_data_models.end(), [](DisplayDataModel a, DisplayDataModel b)
             { return a.number_of_trades < b.number_of_trades; });
      }
      else if (sort_input.column == "trend")
      {
        sort(display_data_models.begin(), display_data_models.end(), [](DisplayDataModel a, DisplayDataModel b)
             { return a.trend < b.trend; });
      }

      if (sort_input.order == "desc")
      {
        reverse(display_data_models.begin(), display_data_models.end());
      }

      break;
    }

    // limit display models
    if (user_input.limit > 0)
    {
      vector<DisplayDataModel> limited_display_models;
      int display_ct = min((int)display_data_models.size(), user_input.limit);

      for (int i = 0; i < display_ct; i++)
      {
        DisplayDataModel display_model = display_data_models.at(i);

        limited_display_models.push_back(display_model);
      }

      display_models = limited_display_models;
    }
    else
    {
      display_models = display_data_models;
    }
  }

  vector<DisplayDataModel> get_display_models()
  {
    return display_models;
  }
};
