#pragma once

#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
#include "include/json.hpp"

using namespace std;

class BinanceDataModel
{
public:
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
      model.priceChange = stod(json_object.at("priceChange").get<string>());
      model.priceChangePercent = stod(json_object.at("priceChangePercent").get<string>());
      model.weightedAvgPrice = stod(json_object.at("weightedAvgPrice").get<string>());
      model.prevClosePrice = stod(json_object.at("prevClosePrice").get<string>());
      model.lastPrice = stod(json_object.at("lastPrice").get<string>());
      model.lastQty = stod(json_object.at("lastQty").get<string>());
      model.bidPrice = stod(json_object.at("bidPrice").get<string>());
      model.bidQty = stod(json_object.at("bidQty").get<string>());
      model.askPrice = stod(json_object.at("askPrice").get<string>());
      model.askQty = stod(json_object.at("askQty").get<string>());
      model.openPrice = stod(json_object.at("openPrice").get<string>());
      model.highPrice = stod(json_object.at("highPrice").get<string>());
      model.lowPrice = stod(json_object.at("lowPrice").get<string>());
      model.volume = stod(json_object.at("volume").get<string>());
      model.quoteVolume = stod(json_object.at("quoteVolume").get<string>());
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
