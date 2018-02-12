//
//  Sprite.cpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 06/02/2018.
//
//

#include "Sprite.h"
#include "Avatar.h"
#include "ObjBlock.h"
#include "ObjPickup.h"

void AvatarDef::draw(){
    ofRectangle temp;
    temp.setFromCenter(160*3/2, 160*3/2, 12, 12);
    ofVec2f tempP = getPositionTranform();
    temp.setFromCenter(tempP.x, tempP.y, 12, 12);
    ofSetColor(ofColor::black);
    ofDrawRectangle(temp);
}
ofVec2f AvatarDef::getPositionTranform(){
    return  a->getPosition() - face->rect.getPosition() + 160;
}
void AvatarDef::reset(){
    a->setPosition(positionInit);
    face = faceIni;
    a->setMove(Deplacement::PLATFORM);
}

ofVec2f ObjBlockDef::getPositionTranform(){
    return b->getPosition() - face->rect.getPosition() + 160;
}
void ObjBlockDef::draw(){
    if (actif) {
        ofRectangle temp;
        temp.setFromCenter(160*3/2, 160*3/2, 12, 12);
        ofVec2f tempP = getPositionTranform();
        temp.setFromCenter(tempP.x, tempP.y, 12, 12);
        ofSetColor(ofColor::red);
        ofDrawRectangle(temp);
    }

}
void ObjBlockDef::reset(){}

ofVec2f ObjPickupDef::getPositionTranform(){
    return pkup->getPosition() - face->rect.getPosition() + 160;

}
void ObjPickupDef::draw(){
    if (actif) {
        ofRectangle temp;
        temp.setFromCenter(160*3/2, 160*3/2, 12, 12);
        ofVec2f tempP = getPositionTranform();
        temp.setFromCenter(tempP.x, tempP.y, 12, 12);
        ofSetColor(ofColor::yellow);
        ofDrawRectangle(temp);
    }
}
void ObjPickupDef::reset(){}
