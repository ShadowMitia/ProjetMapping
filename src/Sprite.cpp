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
#include "WorldsBox2d.h"

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
void AvatarDef::create(){
    world->createAvatar(this);
}
void AvatarDef::reset(){
    a->setPosition(positionInit);
    face = faceIni;
    a->setMove(Deplacement::PLATFORM);
}
bool AvatarDef::isActif(){
    return a->polygon.body->IsActive();
}

ofVec2f ObjBlockDef::getPositionTranform(){
    return b->getPosition() - face->rect.getPosition() + 160;
}
void ObjBlockDef::draw(){
        ofRectangle temp;
        temp.setFromCenter(160*3/2, 160*3/2, 12, 12);
        ofVec2f tempP = getPositionTranform();
        temp.setFromCenter(tempP.x, tempP.y, 12, 12);
        ofSetColor(ofColor::red);
        ofDrawRectangle(temp);

}
void ObjBlockDef::reset(){
    b->polygon.body->SetActive(true);
    b->setPosition(positionInit);
}
bool ObjBlockDef::isActif(){
    return b->polygon.body->IsActive();
}
void ObjBlockDef::create(){
    world->creataBlock(this);
}

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
bool ObjPickupDef::isActif(){
    return pkup->polygon.body->IsActive();
}
void ObjPickupDef::create(){
    
}
