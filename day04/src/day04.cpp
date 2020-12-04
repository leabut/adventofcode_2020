//============================================================================
// Name        : day04.cpp
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
#include <vector>
#include <regex>

//#define PRINT_DEBUG

const std::array<std::string, 7u> validKeys = {
  "byr",
  "iyr",
  "eyr",
  "hgt",
  "hcl",
  "ecl",
  "pid"};

const std::string optionalKey = {"cid"};

std::vector<std::string> preFormat(std::vector<std::string> data) {
  std::vector<std::string> result;

  std::string tmpStr{};
  for (auto& it : data) {
    if (it.size() == 0) {
      tmpStr = tmpStr.substr(0, tmpStr.size() - 1);
      result.push_back(tmpStr);
      tmpStr.clear();
      continue;
    } else {
      tmpStr.append(it.append(" "));
    }
  }

  return result;
}

bool validate(std::string str) {
  auto count = 0u;
  for (auto& it : validKeys) {
    if (str.find(it) != std::string::npos) {
      count++;
    }
  }

  return count == validKeys.size();
}

std::string regexHelper(std::string str, std::regex reg) {
  std::string result;

  auto begin = std::sregex_iterator(str.begin(), str.end(), reg);
  auto end = std::sregex_iterator();

  auto count = 0u;
  for (auto i = begin; i != end; i++) {
    std::smatch match = *i;
    result = match.str();
    count++;
  }

  if (count != 1) {
    result.clear();
  }

  return result;
}

bool validatePartTwo(std::string str) {
  std::regex regByr{"byr:\\d+"};
  std::regex regIyr{"iyr:\\d+"};
  std::regex regEyr{"eyr:\\d+"};
  std::regex regHgtCm{"hgt:\\d+cm"};
  std::regex regHgtIn{"hgt:\\d+in"};
  std::regex regHcl{"hcl:#[0-9a-f]{6}"};
  std::regex regEcl{"ecl:(amb)|(blu)|(brn)|(gry)|(grn)|(hzl)|(oth)"};
  std::regex regPid{"pid:[0-9]{9}"};

  std::string strByr = regexHelper(str, regByr);
  std::string strIyr = regexHelper(str, regIyr);
  std::string strEyr = regexHelper(str, regEyr);
  std::string strHgtCm = regexHelper(str, regHgtCm);
  std::string strHgtIn = regexHelper(str, regHgtIn);
  std::string strHcl = regexHelper(str, regHcl);
  std::string strEcl = regexHelper(str, regEcl);
  std::string strPid = regexHelper(str, regPid);

  if (strByr.size() == 0 || strIyr.size() == 0 || strEyr.size() == 0 ||
      (strHgtCm.size() == 0 && strHgtIn.size() == 0) || strHcl.size() == 0 ||
      strEcl.size() == 0 || strPid.size() == 0) {
    return false;
  }

  strByr = strByr.replace(0, strByr.find(":") + 1, "");
  strIyr = strIyr.replace(0, strIyr.find(":") + 1, "");
  strEyr = strEyr.replace(0, strEyr.find(":") + 1, "");

  if (strHgtCm.size() != 0) {
    strHgtCm = strHgtCm.replace(0, strHgtCm.find(":") + 1, "");
    strHgtCm = strHgtCm.replace(strHgtCm.find("c"), strHgtCm.size(), "");
  } else {
    strHgtIn = strHgtIn.replace(0, strHgtIn.find(":") + 1, "");
    strHgtIn = strHgtIn.replace(strHgtIn.find("i"), strHgtIn.size(), "");
  }

  strHcl = strHcl.replace(0, strHcl.find(":") + 1, "");
  strEcl = strEcl.replace(0, strEcl.find(":") + 1, "");
  strPid = strPid.replace(0, strPid.find(":") + 1, "");

#ifdef PRINT_DEBUG
  printf("strByr: %s\n", strByr.c_str());
  printf("strIyr: %s\n", strIyr.c_str());
  printf("strEyr: %s\n", strEyr.c_str());
  printf("strHgtCm: %s\n", strHgtCm.c_str());
  printf("strHgtIn: %s\n", strHgtIn.c_str());
  printf("strHcl: %s\n", strHcl.c_str());
  printf("strEcl: %s\n", strEcl.c_str());
  printf("strPid: %s\n", strPid.c_str());
#endif

  auto byr = stoi(strByr);
  auto iyr = stoi(strIyr);
  auto eyr = stoi(strEyr);
  auto hgt = 0;

  if (strHgtCm.size() != 0) {
    hgt = stoi(strHgtCm);
    if (hgt < 150 || hgt > 193) {
      return false;
    }
  } else {
    hgt = stoi(strHgtIn);
    if (hgt < 59 || hgt > 76) {
      return false;
    }
  }

  if (byr < 1920 || byr > 2002) {
    return false;
  }
  if (iyr < 2010 || iyr > 2020) {
    return false;
  }
  if (eyr < 2020 || eyr > 2030) {
    return false;
  }

  return true;
}

int main() {
  std::ifstream infile("input.txt");
  std::string line;

  std::vector<std::string> data{};

  infile.clear();
  infile.seekg(0);

  while (std::getline(infile, line)) {
    data.push_back(line);
  }

  data = preFormat(data);

  auto result = 0u;
  for (auto& it : data) {
    if (validate(it)) {
      result++;
    }
  }

  auto result2 = 0u;
  for (auto& it : data) {
    if (validatePartTwo(it)) {
      result2++;
    }
  }

  printf("result: %d\n", result);
  printf("result2: %d\n", result2);

  return 0;
}
