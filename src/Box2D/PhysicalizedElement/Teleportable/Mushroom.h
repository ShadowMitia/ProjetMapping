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
#include "Sprite.h"

class ObjMushroom: public Teleportable{
public:
    ObjMushroom(ObjMushroomDef *_ObjMushroomDef);
    ofxBox2dPolygon MushroomSensor, MushroomTron;
};