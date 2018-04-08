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
        moveImages[0][0].load("Avatar/pixel_00002.png");
        //moveImages[0].mirror(false, false);
        moveImages[1][0].load("Avatar/pixel_00003.png");
        moveImages[2][0].load("Avatar/pixel_00004.png");
        moveImages[3][0].load("Avatar/pixel_00005.png");
        moveImages[4][0].load("Avatar/pixel_00006.png");
        moveImages[5][0].load("Avatar/pixel_00007.png");
        moveImages[6][0].load("Avatar/pixel_00008.png");
        moveImages[7][0].load("Avatar/pixel_00009.png");
        moveImages[8][0].load("Avatar/pixel_00010.png");
        moveImages[9][0].load("Avatar/pixel_00011.png");
        moveImages[10][0].load("Avatar/pixel_00012.png");
        moveImages[11][0].load("Avatar/pixel_00013.png");
        
        moveImages[0][1].load("Avatar/pixel_00002.png");
        moveImages[1][1].load("Avatar/pixel_00003.png");
        moveImages[2][1].load("Avatar/pixel_00004.png");
        moveImages[3][1].load("Avatar/pixel_00005.png");
        moveImages[4][1].load("Avatar/pixel_00006.png");
        moveImages[5][1].load("Avatar/pixel_00007.png");
        moveImages[6][1].load("Avatar/pixel_00008.png");
        moveImages[7][1].load("Avatar/pixel_00009.png");
        moveImages[8][1].load("Avatar/pixel_00010.png");
        moveImages[9][1].load("Avatar/pixel_00011.png");
        moveImages[10][1].load("Avatar/pixel_00012.png");
        moveImages[11][1].load("Avatar/pixel_00013.png");
        motionlessImage.load("Avatar/pixel_00000.png");
        
        for (int i =0; i<12; i++) {
            moveImages[i][1].mirror(false, true);
        }
        
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
    ofImage moveImages[12][2];
    ofImage motionlessImage;
    ofImage jumpImage[3];
    ofImage jadderImage[3];
    
    
};