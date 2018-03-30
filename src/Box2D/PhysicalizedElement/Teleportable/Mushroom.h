//
//  Mushroom.hpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 12/02/2018.
//
//

#pragma once

#include "ofMain.h"
#include "ofxBox2d.h"
#include "Teleportable.h"
#include "AllSprite.h"

class ObjMushroom: public Teleportable{
public:
    ObjMushroom(ObjMushroomDef *_ObjMushroomDef);
    
    void draw();
    //ofxBox2dPolygon MushroomSensor, MushroomTron;
    virtual void contactStart(ofxBox2dContactArgs e, b2Fixture* _fixture, dataSprite* OtherSprite) override;
    virtual void contactEnd(ofxBox2dContactArgs e, b2Fixture* _fixture, dataSprite* OtherSprite) override;
};