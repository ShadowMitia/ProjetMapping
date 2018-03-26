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
#include "ObjTrampoline.h"
#include "WorldsBox2d.h"
#include "SpriteAvatar.h"
/*
Category bits:
PLATFORM : 0x0001
PORTAL   : 0x0002
LADDER   : 0x0004
CLONE    : 0x0008
AVATAR   : 0x0010
BLOCK    : 0x0020
PICKUP   : 0x0040
MUSHROOM : 0x0080
*/


void AvatarDef::draw(){
    ofRectangle temp;
    temp.setFromCenter(160*3/2, 160*3/2, 12, 12);
    ofVec2f tempP = getPositionTranform();
    temp.setFromCenter(tempP.x, tempP.y, 12, 12);
    ofSetColor(ofColor::orange);
    ofDrawRectangle(temp);
    ofSetColor(ofColor::white);
    //drawMove(tempP);
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
bool AvatarDef::getViewPoint(){
    return a->viewPoint;
}



ofVec2f ObjBlockDef::getPositionTranform(){
    return b->getPosition() - face->rect.getPosition() + 160;
}
void ObjBlockDef::draw(){
        ofRectangle temp;
        //temp.setFromCenter(160*3/2, 160*3/2, 48, 48);
        ofVec2f tempP = getPositionTranform();
        temp.setFromCenter(tempP.x, tempP.y, 28, 28);
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
bool ObjBlockDef::getViewPoint(){
    return b->viewPoint;
}

ofVec2f ObjPickupDef::getPositionTranform(){
    return pkup->getPosition() - face->rect.getPosition() + 160;

}
void ObjPickupDef::draw(){
    if (actif) {
        ofRectangle temp;
        temp.setFromCenter(160*3/2, 160*3/2, 8, 8);
        ofVec2f tempP = getPositionTranform();
        temp.setFromCenter(tempP.x, tempP.y, 8, 8);
        ofSetColor(ofColor::yellow);
        ofDrawRectangle(temp);
    }
}
void ObjPickupDef::reset(){}
bool ObjPickupDef::isActif(){
    return pkup->polygon.body->IsActive();
}
void ObjPickupDef::create(){
    world->createPickUp(this);
}
bool ObjPickupDef::getViewPoint(){
    return pkup->viewPoint;
}

ofVec2f ObjMushroomDef::getPositionTranform(){
    return mroom->getPosition() - face->rect.getPosition() + 160;
    
}
void ObjMushroomDef::draw(){
        ofRectangle temp;
        //temp.setFromCenter(160*3/2, 160*3/2, 12, 12);
        ofVec2f tempP = getPositionTranform();
        temp.setFromCenter(tempP.x, tempP.y, 48, 48);
        ofSetColor(ofColor::darkViolet);
        ofDrawRectangle(temp);
}
void ObjMushroomDef::reset(){}
bool ObjMushroomDef::isActif(){
    return mroom->polygon.body->IsActive();
}
void ObjMushroomDef::create(){
    world->createMushroom(this);
}





ofVec2f ObjTrampolineDef::getPositionTranform(){
    return t->getPosition() - face->rect.getPosition() + 160;
}
void ObjTrampolineDef::draw(){
    ofRectangle temp;
    temp.setFromCenter(160*3/2, 160*3/2, 18, 18);
    ofVec2f tempP = getPositionTranform();
    temp.setFromCenter(tempP.x, tempP.y, 18, 18);
    ofSetColor(ofColor::mediumVioletRed);
    ofDrawRectangle(temp);
    
}
void ObjTrampolineDef::reset(){
    t->polygon.body->SetActive(true);
    t->setPosition(positionInit);
}
bool ObjTrampolineDef::isActif(){
    return t->polygon.body->IsActive();
}
void ObjTrampolineDef::create(){
    world->creataBlock(this);
}
bool ObjTrampolineDef::getViewPoint(){
    return t->viewPoint;
}
