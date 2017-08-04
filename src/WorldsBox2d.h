//
//  WorldsBox2d.hpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 16/07/2017.
//
//
#pragma once
#include "ofxBox2d.h"
#include "Avatar.h"
#include "Portal.h"
#include "Platform.h"
class typeBox2d{
public:
    enum class Type { AVATAR, PLATFORM,FOOT};
    Type type;
};

class WorldsBox2d {
public:
    ofxBox2d                 world;
    ofRectangle              bounds;
    vector<shared_ptr<ofxBox2dCircle>>	circles;
    std::vector< Avatar > avatars;
    std::vector< Portal > portals;
    std::vector< Platform * > platforms;
    
    void setup();
    void createCircle(float _x,float _y);
    void draw();
    void update();
    
    void createAvatar();
    void createPlatform(ofPolyline _polyline);
    
};