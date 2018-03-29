//
//  SpriteAvatar.cpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 30/03/2018.
//
//
#pragma once
#include "ofMain.h"
#include "SpriteAvatar.h"
#include "WorldsBox2d.h"
#include "Sprite.h"
#include "Avatar.h"

void AvatarDef::draw(){
    ofRectangle temp;
    ofVec2f tempP = getPositionTranform();
    temp.setFromCenter(tempP.x, tempP.y, 12, 12);
    ofSetColor(ofColor::orange);
    ofDrawRectangle(temp);
    ofSetColor(ofColor::white);
    drawMovePlaform(getPositionTranform());
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

void AvatarDef::drawMovePlaform(ofVec2f p){
    n = n + 1/10.0;
    ofRectangle temp;
    temp.setFromCenter(p.x, p.y, 12, 12);
    
    ofVec2f v = a->getVelocity();
    if (v.y > 0) {
        ofSetColor(ofColor::orange);
        ofDrawRectangle(temp);
        
    }
    else if(v.y < 0){
        ofSetColor(ofColor::darkBlue);
        ofDrawRectangle(temp);
    }
    else  {
        if (v.x > 0) {
            ofSetColor(ofColor::red);
            ofDrawRectangle(temp);
        }
        else if(v.x < 0){
            ofSetColor(ofColor::blueSteel);
            ofDrawRectangle(temp);
        }
        else{
            ofSetColor(ofColor::violet);
            ofDrawRectangle(temp);
        }
    }
    
    if (v.x > 0) {
        
    }else if(v.x < 0){
        
    }else{
        
    }
    
    //moveImages[((int)floor(n)) % 4].draw(p);
}

void AvatarDef::drawMoveTop(ofVec2f p){
    
}

void AvatarDef::setMove(int i){
    n=0;
    switch (i) {
        case 0:
            drawMove = &AvatarDef::drawMovePlaform;
            break;
            
        case 1:
            drawMove = &AvatarDef::drawMoveTop;
            break;
            
        default:
            drawMove = &AvatarDef::drawMovePlaform;
            break;
    }
    
    
}

