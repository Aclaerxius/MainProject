#pragma once

#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
#include <format>
#include "include/termcolor.hpp"
#include "include/json.hpp"
#include "display_data_model.h"
#include <chrono>

#include <unistd.h>
#include <term.h>

using namespace std;
using namespace std::chrono;

string get_formatted_number(double number)
{
  string scale = "";
  if (number >= 1000000000000)
  {
    scale = "T";
    number /= 1000000000000.0;
  }
  else if (number >= 1000000000)
  {
    scale = "B";
    number /= 1000000000.0;
  }
  else if (number >= 1000000)
  {
    scale = "M";
    number /= 1000000.0;
  }
  else if (number >= 1000)
  {
    scale = "K";
    number /= 1000.0;
  }

  string formatted = std::format("{:.2f}", number);

  if (!scale.empty())
  {
    formatted += " " + scale;
  }

  return formatted;
}

string get_formatted_time(time_t unix_timestamp)
{
  struct tm ts;
  ts = *localtime(&unix_timestamp);

  return std::format("{}-{}-{} {}:{}:{}", ts.tm_year + 1900, ts.tm_mon + 1, ts.tm_mday, ts.tm_hour, ts.tm_min, ts.tm_sec);
}

class DisplayManager
{
public:
  static void display(bool has_trend, int64_t last_updated, vector<DisplayDataModel> display_data_models)
  {
    int64_t current_time = duration_cast<seconds>(system_clock::now().time_since_epoch()).count();

    int64_t time_difference = current_time - last_updated;

    string formatted_time = get_formatted_time(current_time);

    string time_ago = std::format("{} seconds ago", time_difference);

    printf("\033[2J");

    std::cout
        << "Last updated: " << formatted_time << " "
        << "(" + time_ago + ")" << std::endl;

    VariadicTable<string, string, string, string, int, string> table({"Symbol", "Price", "Price change", "Volume", "Number of trades", "Trend"}, 10);

    for (auto display_data_model : display_data_models)
    {
      string symbol = display_data_model.symbol;
      string price = std::format("{:.2f}", display_data_model.price);
      string price_change = std::format("{:.2f}%", display_data_model.price_change);

      string volume = get_formatted_number(display_data_model.volume);

      int number_of_trades = display_data_model.number_of_trades;

      // TODO: fix trend color
      // int red_channel = 255;
      // int green_channel = 255;
      // int blue_channel = 255;

      // if (display_data_model.trend < 0)
      // {
      //   double trend_abs = abs(display_data_model.trend);
      //   double intensity = (trend_abs / 100.0 * 255.0);
      //   double inverse_intensity = 255 - (int)intensity;

      //   blue_channel = (int)inverse_intensity;
      //   green_channel = (int)inverse_intensity;
      // }
      // else if (display_data_model.trend > 0)
      // {
      //   double trend_abs = abs(display_data_model.trend);
      //   double intensity = (trend_abs / 100.0 * 255.0);
      //   double inverse_intensity = 255 - (int)intensity;

      //   blue_channel = (int)inverse_intensity;
      //   red_channel = (int)inverse_intensity;
      // }

      // string s = termcolor::color<211, 54, 130> << "World!";

      string trend = std::format("{:.2f}", display_data_model.trend);

      if (!has_trend)
      {
        trend = "-";
      }

      table.addRow(symbol, price, price_change, volume, number_of_trades, trend);
    }

    table.print(std::cout);
  }
};
