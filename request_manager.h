#pragma once
#define REQUESTMANAGER
#include <string>
#include <vector>

#define CPPHTTPLIB_OPENSSL_SUPPORT
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

    static BianceDataModel parse(const json &json_object) {
        BianceDataModel model;

        try {
            model.symbol = json_object.at("symbol").get<string>();
            model.price = stod(json_object.at("lastPrice").get<string>());
            model.priceChange = stod(json_object.at("priceChangePercent").get<string>());
            model.volume = stod(json_object.at("quoteVolume").get<string>());
            model.numberOfTrades = json_object.at("lastId").get<int>();
        } catch (const json::parse_error &e) {
            cerr << "Error parsing JSON: " << e.what() << endl;
        }
        return model;
    }
};

class RequestManager {
   private:
    string url = "https://api2.binance.com/api/v3/ticker/24hr";

   public:
    RequestManager getUrl(const string &url) {
        this->url = url;
        return *this;
    };

    json request() {
        json jsonResponse;

        try {
            httplib::Client cli{"https://api2.binance.com"};
            const auto response = cli.Get("/api/v3/ticker/24hr");
            jsonResponse = json::parse(response->body);
            cout << string{response->body.begin(), response->body.end()} << '\n';
        } catch (const exception &e) {
            cerr << "Request failed, error: " << e.what() << '\n';
        }
        return jsonResponse;
    }

    vector<BianceDataModel> response(const json &jsonResponse) {
        vector<BianceDataModel> binance_models;
        for (const auto &json_object : jsonResponse) {
            auto binance_model = BianceDataModel::parse(json_object);
            binance_models.push_back(binance_model);
        }
        return binance_models;
    }

    vector<BianceDataModel> get_data() {
        json jsonResponse = request();
        return response(jsonResponse);
    }
};

void print_data() {
    RequestManager requestManager;
    vector<BianceDataModel> dataModels = requestManager.get_data();
    for (const auto &model : dataModels) {
        std::cout << "Symbol: " << model.symbol << std::endl;
        std::cout << "Price: " << model.price << std::endl;
        std::cout << "Price Change: " << model.priceChange << std::endl;
        std::cout << "Volume: " << model.volume << std::endl;
        std::cout << "Number of Trades: " << model.numberOfTrades << std::endl;
        std::cout << "-------------------------" << std::endl;
    }
}
