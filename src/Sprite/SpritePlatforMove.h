//
//  SpritePlatforMove.hpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 31/03/2018.
//
//

#pragma once
#include "Sprite.h"
#include "ofMain.h"
#include "b2Fixture.h"

class ObjPlatforMove;
class ObjPlatforMoveDef: public SpriteObj{
public:
    ObjPlatforMoveDef(){
        categoryBits = Category::OBJ;
        maskBits = Category::PORTAL | Category::AVATAR | Category::OBJ  | Category::CLONE | Category::SignageSign ;
        layerIni = layerId =  2;
    }
    
    ObjPlatforMove * pM;
    void draw() override;
    ofVec2f getPositionTranform() override;
    void create() override;
    void reset() override;
    bool isActif() override;
    bool getViewPoint() override;
    ofVec2f vitesse;
    
    
};