//
//  WorldsBox2d.hpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 16/07/2017.
//
//
#pragma once
#include "ofxBox2d.h"

class WorldsBox2d{
public:
    ofxBox2d                 world_1,world_2;
    ofRectangle              bounds_1,bounds_2;
    vector    <shared_ptr<ofxBox2dCircle> >	circles;
    
    void initWordldsBox2d();
    void creatCircle(float _x,float _y);
    void drawCircles();
    void updateWorldsBox2d();
    
    
    
    
};