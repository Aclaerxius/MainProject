#pragma once
#define REQUESTMANAGER
#include <string>
#include <vector>

#include "include/httplib.h"
#include "include/json.hpp"
using namespace std;
using json = nlohmann::json;

class BianceDataModel {
   public:
    string symbol;
    double price;
    double priceChange;
    double volume;
    int numberOfTrades;

    static BianceDataModel parse(const json& json_object) {
        BianceDataModel model;

        try {
            model.symbol = json_object.at("symbol").get<string>();
            model.price = json_object.at("lastPrice").get<double>();
            model.priceChange = json_object.at("priceChangePercent").get<double>();
            model.volume = json_object.at("quoteVolume").get<int>();
            model.numberOfTrades = json_object.at("lastId").get<double>();
        } catch (const json::parse_error& e) {
            cerr << "Error parsing JSON: " << e.what() << endl;
        }
        return model;
    }
};

class RequestManager {
   private:
    string url = "https://api2.binance.com/api/v3/ticker/24hr";

   public:
    RequestManager getUrl(const string& url) {
        this->url = url;
        return *this;
    };

    vector<BianceDataModel> get_data() {
        vector<BianceDataModel> binance_models;
        json jsonResponse;
        try {
            httplib::Client cli{url};
            const auto response = cli.Get("/hi");
            jsonResponse = json::parse(response->body);
            cout << string{response->body.begin(), response->body.end()} << '\n';
        } catch (const exception& e) {
            cerr << "Request failed, error: " << e.what() << '\n';
        }
        for (const auto& json_object : jsonResponse) {
            auto binance_model = BianceDataModel::parse(json_object);
            binance_models.push_back(binance_model);
        }
        return binance_models;
    }
};