#pragma once
#define USERINPUTCLASS
#include <stdlib.h>

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class SortInput {
   public:
    string column = "";
    string order = "";
};

class UserInput {
   public:
    vector<SortInput> sort;
    int limit = 0;
    vector<string> pairs;
    bool ignoreErrors = false;
    int live = 0;
    bool trend = false;
    vector<vector<string>> userArgsSubVectors;

    static UserInput parse(int argc, char* argv[]) {
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
                userArgsSubVectors.push_back(vector<string>());
                userArgsSubVectors.back().push_back(arg);
            } else {
                if (!userArgsSubVectors.empty()) {
                    userArgsSubVectors.back().push_back(arg);
                }
            }
        }

        UserInput userInput;
        string flag;

        for (const auto& subVector : userArgsSubVectors) {
            flag = subVector[0];
            if (flag == "--ignore-errors") {
                userInput.ignoreErrors = true;
            }
        }

        for (const auto& subVector : userArgsSubVectors) {
            flag = subVector[0];

            // Sort
            if (flag == "--sort") {
                if (subVector.size() % 2 != 1) {
                    if (userInput.ignoreErrors != true) {
                        // throw runtime_error("Invalid input for sorting. Please check your spelling.");
                    }
                }

                for (int i = 1; i < subVector.size(); i += 2) {
                    string sub1 = subVector[i];
                    string sub2 = subVector[i + 1];

                    SortInput newSortInput;

                    {
                        if (sub1 == "symbol") {
                            newSortInput.column = sub1;
                        }

                        if (sub1 == "price") {
                            newSortInput.column = sub1;
                        }

                        if (sub1 == "price_change") {
                            newSortInput.column = sub1;
                        }

                        if (sub1 == "volume") {
                            newSortInput.column = sub1;
                        }

                        if (sub1 == "number_of_trades") {
                            newSortInput.column = sub1;
                        }

                        if (sub1 == "trend") {
                            newSortInput.column = sub1;
                        }
                    }

                    if (sub2 == "asc") {
                        newSortInput.order = sub2;
                    }

                    if (sub2 == "desc") {
                        newSortInput.order = sub2;
                    }

                    if (!newSortInput.column.empty() && !newSortInput.order.empty()) {
                        userInput.sort.push_back(newSortInput);
                    } else {
                        throw runtime_error("Invalid input for sorting. Please check your spelling.");
                    }
                }
            }

            // Pairs
            if (flag == "--pairs") {
                for (int i = 1; i < subVector.size(); i++) {
                    string pairsArg = subVector[i];
                    transform(pairsArg.begin(), pairsArg.end(), pairsArg.begin(), ::toupper);
                    userInput.pairs.push_back(pairsArg);
                }
            }

            // Trend
            if (flag == "--trend") {
                userInput.trend = true;
            }

            // Limit
            // if (flag == "--limit" && subVector.size() > 1) {
            //     string limitArg = subVector[1];
            //     int limitArgInt;
            //     size_t pos{};
            //     try {
            //         cout << "stoi(" << quoted(limitArg) << "): ";
            //         const int i{stoi(limitArg, &pos)};
            //         cout << i << "; pos: " << pos << '\n';
            //         limitArgInt = i;
            //     } catch (invalid_argument const& ex) {
            //         cout << "invalid_argument::what(): " << ex.what() << '\n';
            //         userInput.limit = !limitArgInt;
            //     } catch (out_of_range const& ex) {
            //         cout << "out_of_range::what(): " << ex.what() << '\n';
            //         const long long ll{stoll(limitArg, &pos)};
            //         cout << "stoll(" << quoted(limitArg) << "): " << ll << "; pos: " << pos << '\n';
            //         userInput.limit = limitArgInt;
            //     }

            //     if (limitArgInt > 0) {
            //         userInput.limit = limitArgInt;
            //     } else if (userInput.ignoreErrors == true) {
            //         userInput.limit = limitArgInt;
            //     }
            // }

            // Live
            // if (flag == "--live") {
            //     if (subVector.size() > 1) {
            //         string liveArg = subVector[1];
            //         int liveArgInt = stoi(liveArg);
            //         if (liveArgInt > 0) {
            //             userInput.live = liveArgInt;
            //         } else {
            //             userInput.live = 5;
            //         }
            //     } else {
            //         userInput.live = 5;
            //     }
            // }
        }

        return userInput;
    };
    void print() {
        for (const auto& subVector : userArgsSubVectors) {
            for (const auto& option : subVector) {
                cout << option << " ";
            }
            cout << endl;
        }

        for (const auto& sortInput : sort) {
            cout << "Column: " << sortInput.column << ", Order: " << sortInput.order << endl;
        }

        cout << "Limit: " << limit << endl;

        for (const auto& pairsInput : pairs) {
            cout << "Pair: " << pairsInput << endl;
        }

        cout << "Ignore Errors: " << ignoreErrors << endl;
        cout << "Live: " << live << endl;
        cout << "Trend: " << trend << endl;
    }
};