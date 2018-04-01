//
//  SpriteTrampoline.cpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 30/03/2018.
//
//

#pragma once
#include "ofMain.h"
#include "WorldsBox2d.h"
#include "SpriteTrampoline.h"
#include "Sprite.h"
#include "ObjTrampoline.h"

ofVec2f ObjTrampolineDef::getPositionTranform(){
    return t->getPosition() - face->rect.getPosition() + 320;
}
void ObjTrampolineDef::draw(){
    ofRectangle temp;
    temp.setFromCenter(320*3/2, 320*3/2, 18, 18);
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
