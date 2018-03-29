//
//  SpriteBlock.cpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 30/03/2018.
//
//


#pragma once
#include "ofMain.h"
#include "SpriteBlock.h"
#include "WorldsBox2d.h"
#include "Sprite.h"
#include "ObjBlock.h"


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
