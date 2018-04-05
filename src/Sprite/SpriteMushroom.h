//
//  ObjMushroom.hpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 30/03/2018.
//
//


#pragma once
#include "Sprite.h"
#include "ofMain.h"
#include "shift.h"
#include "b2Fixture.h"
#include "Light.h"


class ObjMushroom;
class ObjMushroomDef: public SpriteObj{
public:
    ObjMushroomDef(){
        categoryBits = Category::MUSHROOM_top;
        //maskBits =  Category::AVATAR | Category::OBJ | Category::CLONE ;
        maskBits = Category::CLONE | Category::OBJ_top;
        layerIni = layerId =  4;
    }
    
    ofImage spriteImage;
    ObjMushroom * mroom;
    void draw() ;
    ofVec2f getPositionTranform() ;
    void create() ;
    void reset() ;
    bool isActif();
    bool getViewPoint(){return false;};
};