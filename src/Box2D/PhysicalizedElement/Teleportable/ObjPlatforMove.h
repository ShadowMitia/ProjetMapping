//
//  ObjPlatforMove.hpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 29/03/2018.
//
//

#pragma once

#include "ofMain.h"
#include "ofxBox2d.h"
#include "Teleportable.h"
#include "AllSprite.h"


class ObjPlatforMove: public Teleportable{
public:
    
    
    ObjPlatforMove(ObjPlatforMoveDef* _pM);
    virtual void contactStart(ofxBox2dContactArgs e, b2Fixture* _fixture, dataSprite* OtherSprite) override;
    
};