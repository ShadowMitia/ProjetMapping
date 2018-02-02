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


enum class Viewpoint { MODE_ANGLE, MODE_PERSPECTIVE };

class Teleportable : public PhysicalizedElement {
public:
    ObjectGame polygon;
    ofVec2f getPosition();
    ofVec2f getVelocity();
    void setPosition(ofVec2f p);
    void setVelocity(ofVec2f v);
    void SetGravityScale(float32 scale);
    Viewpoint viewpoint = Viewpoint::MODE_ANGLE;
    bool viewPoint = false;
};

