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
#include "Face.h"

class SpriteObj;
class Teleportable : public PhysicalizedElement {
public:
    SpriteObj* sprite;
    ObjectGame polygon;
    ofVec2f getPosition();
    ofVec2f getVelocity();
    void setPosition(ofVec2f p);
    void setVelocity(ofVec2f v);
    void SetGravityScale(float32 scale);
    bool viewPoint = false;
};
