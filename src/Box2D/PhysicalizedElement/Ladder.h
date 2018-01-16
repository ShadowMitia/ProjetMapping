//
//  Ladder.hpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 21/08/2017.
//
//

#pragma once
#include "ofMain.h"
#include "Constant.h"
#include "Avatar.h"


class Ladder: public PhysicalizedElement{
public:
    ofxBox2dPolygon polygon;
    void create(b2World* _b2World, ofPolyline _groundLine);
    void draw();
    void contactStart(b2Fixture* _fixture, dataSprite* OtherSprite);
    void contactEnd(b2Fixture* _fixture, dataSprite* OtherSprite);
};