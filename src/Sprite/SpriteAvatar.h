//
//  SpriteAvatar.hpp
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

class Avatar;
class AvatarDef: public SpriteObj, public Light{
public:
    AvatarDef(){
        categoryBits = Category::AVATAR;
        maskBits  =  Category::AVATAR  | Category::PORTAL | Category::LADDER |Category::OBJ | Category::CLONE | Category::SignageSign;
        layerIni = layerId =  3;
        color.set(ofColor::orange);
        drawMove = &AvatarDef::drawMovePlaform;
        moveImages[0].load("Avatar/pixel_00002.png");
        //moveImages[0].mirror(false, false);
        moveImages[1].load("ava_2.png");
        moveImages[2].load("ava_3.png");
        moveImages[3].load("ava_4.png");
        
    }
    ofImage spriteImage;
    Shift* s;
    Avatar* a;
    void draw()override;
    ofVec2f getPositionTranform() override;
    void create() override;
    void reset() override;
    bool isActif() override;
    bool getViewPoint() override;
    
    
    void setMove(int i);//Deplacement move);
    void drawMovePlaform(ofVec2f p);
    void drawMoveTop(ofVec2f p);
    
    void(AvatarDef::*drawMove)(ofVec2f p);
    
    
    void drawjump();
    
    float n;
    ofImage moveImages[4];
    ofImage jumpImage[3];
    ofImage jadderImage[3];
    
    
};