#pragma once
#define USERINPUTCLASS
#include <stdlib.h>

#include <iostream>
#include <string>
#include <vector>

class SortInput {
   public:
    string column;
    string order;
};

class UserInput {
   public:
    std::vector<SortInput> sort;
    int limit;
    vector<string> pairs;
    bool ignoreErrors;
    int live;
    bool trend;

    static UserInput parse(int argc, char* argv[]) {
        UserInput userInput;

        // store user input arguments in a vector string
        vector<string> userArgs;
        for (int i = 0; i < argc; i++) {
            string s(argv[i]);
            userArgs.push_back(s);
        };

        vector<vector<string>> userArgsSubVectors;

        for (int i = 1; i < userArgs.size(); i++) {
            string arg = userArgs.at(i);

            if (arg.length() > 1 && arg.at(0) == '-' && arg.at(1) == '-') {
                userArgsSubVectors.push_back(std::vector<std::string>());
                userArgsSubVectors.back().push_back(arg);
            } else {
                if (!userArgsSubVectors.empty()) {
                    userArgsSubVectors.back().push_back(arg);
                }
            }
        }

        for (const auto& subVector : userArgsSubVectors) {
            string sub = subVector[0];
            // Sort

            if (sub == "--sort" && subVector.size() > 1 && subVector.size() <= 12) {
                for (int i = 1; i < subVector.size(); i++) {
                    string sub1 = subVector[i];
                    string sub2 = subVector[i + 1];

                    SortInput newSortInput;
                    newSortInput.column = sub1;

                    if (sub1 == "symbol") {
                        newSortInput.column = "symbol";
                    }

                    if (sub1 == "price") {
                        newSortInput.column = "price";
                    }

                    if (sub1 == "price_change") {
                        newSortInput.column = "price_change";
                    }

                    if (sub1 == "volume") {
                        newSortInput.column = "volume";
                    }

                    if (sub1 == "number_of_trades") {
                        newSortInput.column = "number_of_trades";
                    }

                    if (sub1 == "trend") {
                        newSortInput.column = "trend";
                    }

                    if (sub2 == "asc") {
                        newSortInput.order = "asc";
                    }

                    if (sub2 == "desc") {
                        newSortInput.order = "desc";
                    }

                    if (!newSortInput.column.empty() && !newSortInput.order.empty()) {
                        userInput.sort.push_back(newSortInput);
                    }
                    // if (sub1 != "symbol" && sub1 != "price" && sub1 != "price_change" && sub1 != "volume" && sub1 != "number_of_trades" && sub1 != "trend" && sub2 != "asc" && sub2 != "desc")
                    // {
                    //   cout << "ERROR" << endl;
                    // }
                }
            }

            // Limit
            if (sub == "--limit") {
                for (int i = 1; i < subVector.size(); i++) {
                    if (i > 0) {
                        userInput.limit = stoi(subVector[i]);
                    }
                }
            }

            // Pairs
            if (sub == "--pairs") {
                for (int i = 1; i < subVector.size(); i++) {
                    string newPair;
                    newPair = subVector[i];
                    userInput.pairs.push_back(newPair);
                }
            }

            // Ignore errors
            if (sub != "--ignore-errors") {
                userInput.ignoreErrors = false;
            } else {
                userInput.ignoreErrors = true;
            }

            // Live
            if (sub != "--live") {
                userInput.live = 0;
            } else {
                userInput.live = 5;
                for (int i = 1; i < subVector.size(); i++) {
                    if (i > 0 && i < 100) {
                        userInput.live = stoi(subVector[i]);
                    } else if (i > 100) {
                        userInput.live = 100;
                    }
                }
            }

            // Trend
            if (sub != "--trend") {
                userInput.trend = false;
            } else {
                userInput.trend = true;
            }
        }

        return userInput;
    };

    void print();
};
void UserInput::print() {
    for (const auto& sortInput : sort) {
        std::cout << "Column: " << sortInput.column << ", Order: " << sortInput.order << std::endl;
    }
    std::cout << "Limit: " << limit << std::endl;
    for (const auto& pairsInput : pairs) {
        std::cout << "Pair: " << pairsInput << std::endl;
    }
    std::cout << "Ignore Errors: " << ignoreErrors << std::endl;
    std::cout << "Live: " << live << std::endl;
    std::cout << "Trend: " << trend << std::endl;
};