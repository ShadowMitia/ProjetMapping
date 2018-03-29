//
//  SpriteBlock.hpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 30/03/2018.
//
//

#pragma once
#include "Sprite.h"
#include "ofMain.h"
#include "b2Fixture.h"

class ObjBlock;
class ObjBlockDef: public SpriteObj{
public:
    ObjBlockDef(){
        categoryBits = Category::OBJ;
        maskBits = Category::PORTAL | Category::AVATAR | Category::OBJ | Category::CLONE ;
        layerIni = layerId =  2;
    }
    ofImage spriteImage;
    ObjBlock * b;
    void draw() override;
    ofVec2f getPositionTranform() override;
    void create() override;
    void reset() override;
    bool isActif() override;
    bool getViewPoint() override;
    
    
};
