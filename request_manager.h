#pragma once
#define REQUESTMANAGER
#include <string>
#include <vector>

#include "include/HTTPRequest.hpp"
#include "include/json.hpp"
using namespace std;

class RequestMangeg {
   public:
    string url;
    RequestMangeg(/* args */);
    ~RequestMangeg();
};

RequestMangeg::RequestMangeg(/* args */) {
}

RequestMangeg::~RequestMangeg() {
}
