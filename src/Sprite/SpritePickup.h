//
//  SpritePickup.hpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 30/03/2018.
//
//
#pragma once
#include "Sprite.h"
#include "ofMain.h"
#include "b2Fixture.h"


class ObjPickup;
class ObjPickupDef: public SpriteObj, public Light {
public:
    
    ObjPickupDef(){
        categoryBits = Category::OBJ;
        maskBits = Category::PORTAL | Category::AVATAR | Category::OBJ  | Category::CLONE;
        radius = 0.2;
        layerIni = layerId =  3;
        color.set(ofColor::yellow);
    }
    bool actif  = true;
    ofImage spriteImage;
    ObjPickup * pkup;
    void draw() override;
    
    
    
    ofVec2f getPositionTranform() override;
    void create() override;
    void reset() override;
    bool isActif() override;
    bool getViewPoint() override;
    
};