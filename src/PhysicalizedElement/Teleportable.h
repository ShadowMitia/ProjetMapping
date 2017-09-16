//
//  Teleportable.h
//  ProjetMapping
//
//  Created by FatDazz_mac on 08/08/2017.
//
//
#pragma once

#include "ofMain.h"
#include "../Constant.h"
#include "PhysicalizedElement.h"

class Teleportable : public PhysicalizedElement {
public:
    virtual void update() = 0;
    virtual void draw() = 0;
    
    virtual void createClone(ofVec2f translationClone) = 0;
    virtual void removeClone() = 0;
    virtual void teleportToClone() = 0;
    virtual bool hasClone() = 0;
    
public:
    ofRectangle collisionRect;

	Viewpoint viewpoint = Viewpoint::MODE_ANGLE;
};

