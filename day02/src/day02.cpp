//============================================================================
// Name        : day02.cpp
// Author      :
// Version     :
// Copyright   :
// Description :
//============================================================================

#include <array>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>

#define DEBUG_PRINT

std::array<std::string, 4> parseData(std::string str) {
  std::string policy = str.substr(0, str.find(":"));
  printf("%s\n", policy.c_str());

  std::string min = policy.substr(0, policy.find("-"));
  std::string tmp = policy.substr(policy.find("-") + 1, policy.size());
  std::string max = tmp.substr(0, tmp.find(" "));
  std::string character = tmp.substr(tmp.find(" ") + 1, tmp.size());
  std::string password = str.substr(str.find(":") + 2, str.size());

#ifdef DEBUG_PRINT
  printf("min: %s\n", min.c_str());
  printf("max: %s\n", max.c_str());
  printf("character: %s\n", character.c_str());
  printf("password: %s\n", password.c_str());
#endif

  return {min, max, character, password};
}

int main() {
  std::ifstream infile("input.txt");
  std::string line;

  std::array<std::string, 1000> data{};

  infile.clear();
  infile.seekg(0);

  auto i = 0u;
  while (std::getline(infile, line)) {
    data[i] = line;
    i++;
  }

  auto result = 0u;
  auto result2 = 0u;
  for (auto& it : data) {
    auto parsedData = parseData(it);
    auto count = std::count(parsedData[3].begin(), parsedData[3].end(), parsedData[2].c_str()[0]);
    auto min = stoi(parsedData[0]);
    auto max = stoi(parsedData[1]);

    if (count >= min && count <= max) {
      result++;
    }

    if (((parsedData[3].c_str()[min - 1] == parsedData[2].c_str()[0]) &&
          (parsedData[3].c_str()[max - 1] != parsedData[2].c_str()[0])) ||
        ((parsedData[3].c_str()[min - 1] != parsedData[2].c_str()[0]) &&
          (parsedData[3].c_str()[max - 1] == parsedData[2].c_str()[0]))) {
      result2++;
    }
  }

  printf("result: %d\n", result);
  printf("result2: %d\n", result2);

  return 0;
}
