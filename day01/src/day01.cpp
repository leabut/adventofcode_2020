//============================================================================
// Name        : day01.cpp
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

int main() {
  std::ifstream infile("input.txt");
  std::string line;

  std::array<int, 200> data = {0u};

  infile.clear();
  infile.seekg(0);

  auto i = 0u;
  while (std::getline(infile, line)) {
    data[i] = std::stoi(line);
    i++;
  }

  for (auto i : data) {
    for (auto k : data) {
      if (i + k == 2020) {
        printf("data[i] = %d, data[k] = %d\n", i, k);
        printf("i * k = %d\n", i * k);
        break;
      }
    }
  }

  for (auto i : data) {
    for (auto k : data) {
      for (auto j : data) {
        if (i + k + j == 2020) {
          printf("data[i] = %d, data[k] = %d, data[j] = %d\n", i, k, j);
          printf("i * k * j = %d\n", i * k * j);
          break;
        }
      }
    }
  }

  return 0;
}
