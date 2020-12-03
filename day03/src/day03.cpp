//============================================================================
// Name        : day03.cpp
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
#include <cstring>

//#define PRINT_DEBUG

long long iterateWithSlope(char data[323][32], int right, int down) {
  auto i = 0u;
  for (auto k = down; k < 323; k += down) {
    i += right;
    i %= 31;
    if (data[k][i] == '#') {
      data[k][i] = 'X';
    } else {
      data[k][i] = 'O';
    }
  }

  auto result = 0u;
  for (auto i = 0u; i < 323u; i++) {
#ifdef PRINT_DEBUG
    printf("%s\n", data[i]);
#endif
    for (auto k = 0u; k < 31; k++) {
      if (data[i][k] == 'X') {
        result++;
      }
    }
  }

  return result;
}

int main() {
  std::ifstream infile("input.txt");
  std::string line;

  char data[323u][32u]{};

  infile.clear();
  infile.seekg(0);

  auto i = 0u;
  while (std::getline(infile, line)) {
    std::strncpy(data[i], line.c_str(), 31);
    i++;
  }

  char data1[323u][32u]{};
  char data2[323u][32u]{};
  char data3[323u][32u]{};
  char data4[323u][32u]{};
  char data5[323u][32u]{};

  std::memcpy(data1, data, 323 * 32);
  std::memcpy(data2, data, 323 * 32);
  std::memcpy(data3, data, 323 * 32);
  std::memcpy(data4, data, 323 * 32);
  std::memcpy(data5, data, 323 * 32);

  auto result1 = iterateWithSlope(data1, 1u, 1u);
  auto result2 = iterateWithSlope(data2, 3u, 1u);
  auto result3 = iterateWithSlope(data3, 5u, 1u);
  auto result4 = iterateWithSlope(data4, 7u, 1u);
  auto result5 = iterateWithSlope(data5, 1u, 2u);
  auto result22 = result1 * result2 * result3 * result4 * result5;

  printf("result: %lld\n", result2);

  printf("result2: %lld\n", result22);

  return 0;
}
