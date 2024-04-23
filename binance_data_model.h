#pragma once

#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
#include "include/json.hpp"

using namespace std;

class BinanceDataModel
{
  string symbol;
  double priceChange;
  double priceChangePercent;
  double weightedAvgPrice;
  double prevClosePrice;
  double lastPrice;
  double lastQty;
  double bidPrice;
  double bidQty;
  double askPrice;
  double askQty;
  double openPrice;
  double highPrice;
  double lowPrice;
  double volume;
  double quoteVolume;
  long openTime;  // ms unix time
  long closeTime; // ms unix time
  long firstId;   // First tradeId
  long lastId;    // Last tradeId
  long count;     // Trade count

public:
  static BinanceDataModel parse(const nlohmann::json &json_object)
  {
    BinanceDataModel model;

    try
    {
      model.symbol = json_object.at("symbol").get<string>();
      model.priceChange = json_object.at("priceChange").get<double>();
      model.priceChangePercent = json_object.at("priceChangePercent").get<double>();
      model.weightedAvgPrice = json_object.at("weightedAvgPrice").get<double>();
      model.prevClosePrice = json_object.at("prevClosePrice").get<double>();
      model.lastPrice = json_object.at("lastPrice").get<double>();
      model.lastQty = json_object.at("lastQty").get<double>();
      model.bidPrice = json_object.at("bidPrice").get<double>();
      model.bidQty = json_object.at("bidQty").get<double>();
      model.askPrice = json_object.at("askPrice").get<double>();
      model.askQty = json_object.at("askQty").get<double>();
      model.openPrice = json_object.at("openPrice").get<double>();
      model.highPrice = json_object.at("highPrice").get<double>();
      model.lowPrice = json_object.at("lowPrice").get<double>();
      model.volume = json_object.at("volume").get<double>();
      model.quoteVolume = json_object.at("quoteVolume").get<double>();
      model.openTime = json_object.at("openTime").get<long>();
      model.closeTime = json_object.at("closeTime").get<long>();
      model.firstId = json_object.at("firstId").get<long>();
      model.lastId = json_object.at("lastId").get<long>();
      model.count = json_object.at("count").get<long>();
    }
    catch (const json::parse_error &e)
    {
      throw e;
    }

    return model;
  }

  static vector<BinanceDataModel> parse_array(const nlohmann::json &json_array)
  {
    vector<BinanceDataModel> binance_models;
    for (const auto &json_object : json_array)
    {
      auto binance_model = BinanceDataModel::parse(json_object);
      binance_models.push_back(binance_model);
    }
    return binance_models;
  }
};
