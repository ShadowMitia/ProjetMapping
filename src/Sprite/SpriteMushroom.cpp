//
//  ObjMushroom.cpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 30/03/2018.
//
//


#pragma once
#include "ofMain.h"
#include "SpriteMushroom.h"
#include "WorldsBox2d.h"
#include "Sprite.h"
#include "Mushroom.h"

ofVec2f ObjMushroomDef::getPositionTranform(){
    return mroom->getPosition() - face->rect.getPosition() + 320;
    
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

