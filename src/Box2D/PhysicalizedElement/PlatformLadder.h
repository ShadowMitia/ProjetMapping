//
//  PlatformLadder.hpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 28/01/2018.
//
//


#pragma once

#include "ofMain.h"
#include "Constant.h"
#include "Avatar.h"


class PlatformLadder: public PhysicalizedElement{
public:
    ofxBox2dPolygon polygon;
    void create(b2World* _b2World, ofPolyline _groundLine);
    void draw();
    void contactStart(ofxBox2dContactArgs e,b2Fixture* _fixture, dataSprite* OtherSprite);
    void contactEnd(ofxBox2dContactArgs e,b2Fixture* _fixture, dataSprite* OtherSprite);
};
