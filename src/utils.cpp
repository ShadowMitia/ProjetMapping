#include "utils.h"

#include <iterator>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cctype>

std::string trim(std::string const& s)
{
    auto it = s.begin();
    while (it != s.end() && std::isspace(*it))
        it++;

    auto rit = s.rbegin();
    while (rit.base() != it && std::isspace(*rit))
        rit++;

    return std::string(it, rit.base());
}

std::vector<std::vector<std::string>> readCSV(std::string const& csvFile)
{
  std::vector<std::vector<std::string>> values;
  std::ifstream csv(csvFile);

  if (!csv.is_open())
    {
      std::cout << "Couldn't open: " << csvFile << '\n';
    }

  std::string line;
  std::getline(csv, line);
  while (std::getline(csv, line))
    {
      std::istringstream iss(line);
      values.emplace_back();
      std::string tmp;
      while (std::getline(iss, tmp, ','))
      {
        values.back().push_back(trim(tmp));
       }
    }
  return values;
  }
