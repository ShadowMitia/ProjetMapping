//
//  Platform.hpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 02/08/2017.
//

#pragma once
#include "ofxBox2d.h"
#include "Shape2D.h"
#include "LightSystem2D.h"
#include "Constant.h"

class dataPlatform: public dataSprite {
public:
    int alex; 
};

class Platform {
public:
    
    ofxBox2dEdge ground;
    ofx::Shape2D::SharedPtr shape;
    ofx::LightSystem2D* LightSystem;
    
    
private:
    float scale;
    float rad;
    ofVec2f translat;
    
    
public:
    
    void create(b2World* _b2World, ofPolyline _groundLine,ofx::LightSystem2D* _LightSystem);
    void draw();
    
};