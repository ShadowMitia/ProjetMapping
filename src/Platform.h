//
//  Platform.hpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 02/08/2017.
//

#pragma once
#include "ofxBox2d.h"

class Platform {
public:
    
    ofxBox2dEdge ground;
    
    
private:
    float scale;
    float rad;
    ofVec2f translat;
    
    
public:
    
    void create(b2World* _b2World, ofPolyline _groundLine);
    void draw();
    
};