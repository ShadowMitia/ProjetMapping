
#pragma once
#include "ofMain.h"
#include "utils.h"
#include <iterator>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cctype>
#include "ofxCv.h"

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

vector<ofPolyline> importImage(ofTexture _image){
    std::vector<ofPolyline> poly;
    ofImage image;
    ofPixels temp;
    image.allocate(_image.getWidth(), _image.getHeight(), ofImageType::OF_IMAGE_COLOR_ALPHA);
    _image.readToPixels(temp);
    image.setFromPixels(temp);
    image.update();
    ofxCv::ContourFinder contourFinder;
    contourFinder.setMinAreaRadius(0);
    contourFinder.setMaxAreaRadius(100000); //1000 max
    contourFinder.setThreshold(100);
    contourFinder.setInvert(true);
    contourFinder.setFindHoles(false);
    contourFinder.findContours(image);
    
    for (int i = 0 ; i < contourFinder.getPolylines().size(); i++){
        ofPolyline tempPoly;
        for (int j = 0; j<contourFinder.getPolyline(i).getVertices().size(); j++) {
            tempPoly.addVertex(contourFinder.getPolyline(i).getVertices()[j] + ofPoint(1,1));
        }
        //tempPoly = contourFinder.getPolyline(i);
        tempPoly.addVertex(tempPoly.getVertices().at(0));
        poly.push_back(tempPoly);
    }
    return poly;
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