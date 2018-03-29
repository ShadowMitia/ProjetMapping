//
//  ObjPlatforMove.hpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 29/03/2018.
//
//

#pragma once

#include "ofMain.h"
#include "Teleportable.h"
#include "Sprite.h"

class ObjPlatforMove: public Teleportable{
public:
    
    
    virtual void contactStart(ofxBox2dContactArgs e, b2Fixture* _fixture, dataSprite* OtherSprite) override;
    

    
};