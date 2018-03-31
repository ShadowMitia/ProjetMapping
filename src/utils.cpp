
#pragma once
#include "ofMain.h"
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


/*std::vector<ofPoint> loadPoints(const std::string& file)
{
    std::vector<ofPoint> pts;
    std::vector <std::string>  ptsStr = ofSplitString(ofBufferFromFile(file).getText(), ",");
    for (unsigned int i = 0; i < ptsStr.size(); i += 2) {
        float x = ofToFloat(ptsStr[i]);
        float y = ofToFloat(ptsStr[i+1]);
        pts.push_back(ofPoint(x, y));
    }
    return pts;
}*/