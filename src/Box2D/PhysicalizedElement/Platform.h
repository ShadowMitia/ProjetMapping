//
//  Platform.hpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 02/08/2017.
//

#pragma once
#include "ofxBox2d.h"
#include "../Constant.h"
#include "PhysicalizedElement.h"


class Platform : public PhysicalizedElement {
public:
    ofxBox2dEdge ground;
public:
    void create(b2World* _b2World, ofPolyline _groundLine);
    void draw();
};
