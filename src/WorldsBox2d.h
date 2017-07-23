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

class WorldsBox2d{
public:
    ofxBox2d                 world;
    ofRectangle              bounds;
    vector<shared_ptr<ofxBox2dCircle>>	circles;
    std::vector< std::shared_ptr<avatar> > avatars;
    std::vector< std::shared_ptr<Portal> > portals;
    
    
    void initWordldsBox2d();
    void creatCircle(float _x,float _y);
    void drawCircles();
    void updateWorldsBox2d();
    
    void creatAvatar();
    
};