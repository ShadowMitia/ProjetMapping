//
//  SpriteTrampoline.hpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 30/03/2018.
//
//
#pragma once
#include "Sprite.h"
#include "ofMain.h"
#include "b2Fixture.h"

class ObjTrampoline;
class ObjTrampolineDef: public SpriteObj{
public:
    ObjTrampolineDef(){
        categoryBits = Category::OBJ;
        maskBits = Category::PORTAL | Category::AVATAR | Category::OBJ  | Category::CLONE;
        layerIni = layerId =  2;
    }
    
    ObjTrampoline * t;
    void draw() override;
    ofVec2f getPositionTranform() override;
    void create() override;
    void reset() override;
    bool isActif() override;
    bool getViewPoint() override;
    
    
};
