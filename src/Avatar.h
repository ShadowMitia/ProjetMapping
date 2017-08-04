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
#include "LightSystem2D.h"

class Avatar {
public:
    
    ofxBox2dPolygon polygon;
    ofxBox2dRect    foot;
    ofx::Light2D::SharedPtr   light;
	ofRectangle rect;
    
private:
    std::unique_ptr<Avatar> clone = nullptr;
    ofVec2f cloneTranslation;
    bool jumping = false;
    int cont;
    int forceJump, speed;
    ofx::LightSystem2D *lightSystem2D;
    
public:
    
    void create(b2World* _b2World, ofx::LightSystem2D * _lightSystem2D);
    void update();
    void draw();
    void handleInputs(int key);
    void createClone(ofVec3f cloneTranslation);
    void removeClone();
    void teleportTo(ofVec2f destination);
    void teleportToClone();
    bool hasClone();
    
};