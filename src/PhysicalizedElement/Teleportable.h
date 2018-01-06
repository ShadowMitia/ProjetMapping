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
    ofxBox2dPolygon polygon;
    Viewpoint viewpoint = Viewpoint::MODE_ANGLE;
};

