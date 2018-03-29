//
//  SpritePickup.cpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 30/03/2018.
//
//

#pragma once
#include "ofMain.h"
#include "SpritePickup.h"
#include "WorldsBox2d.h"
#include "Sprite.h"
#include "ObjPickup.h"

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