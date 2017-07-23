//
//  Avatar.hpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 22/07/2017.
//
//
#pragma once

#include "ofMain.h"
#include "ofxBox2d.h"
#include "Light2D.h"

class avatar{
public:
    
    ofxBox2dPolygon polygon;
    ofx::Light2D    light;
    ofRectangle     rect;
    
private:
    std::unique_ptr<avatar> clone = nullptr;
    ofVec2f cloneTranslation;
    
public:
    
    void create(b2World* _b2World);
    void update();
    void draw();
    void handleInputs(int key);
    void createClone(ofVec3f cloneTranslation);
    void removeClone();
    void teleportTo(ofVec2f destination);
    void teleportToClone();
    bool hasClone();
    
};