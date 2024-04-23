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
  int limit;

  // flag: --pairs
  vector<string> pairs;

  // flag: --ignore-errors
  bool ignore_errors;

  // flag: --live
  int live; // default is 5 seconds

  // flag: --trend
  int trend;

  static UserInput parse(int argc, char *argv[])
  {

    //
  }
};
