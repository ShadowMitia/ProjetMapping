//
//  SpritePlatforMove.cpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 31/03/2018.
//
//

#pragma once
#include "ofMain.h"
#include "SpritePlatforMove.h"
#include "ObjPlatforMove.h"
#include "WorldsBox2d.h"




ofVec2f ObjPlatforMoveDef::getPositionTranform(){
    return pM->getPosition() - face->rect.getPosition() + 320;
}
void ObjPlatforMoveDef::draw(){
    ofRectangle temp;
    temp.setFromCenter(320*3/2, 320*3/2, 18, 18);
    ofVec2f tempP = getPositionTranform();
    temp.setFromCenter(tempP.x, tempP.y, 18, 18);
    ofSetColor(ofColor::lawnGreen);
    ofDrawRectangle(temp);
    
}
void ObjPlatforMoveDef::reset(){
    pM->polygon.body->SetActive(true);
    pM->setPosition(positionInit);
}
bool ObjPlatforMoveDef::isActif(){
    return pM->polygon.body->IsActive();
}
void ObjPlatforMoveDef::create(){
    world->createPlatforMove(this);
    
}
bool ObjPlatforMoveDef::getViewPoint(){
    return pM->viewPoint;
}
