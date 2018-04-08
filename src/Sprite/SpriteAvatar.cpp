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
#include "shift.h"

void AvatarDef::draw(){
    //ofRectangle temp;
    //ofVec2f tempP = getPositionTranform();
    //temp.setFromCenter(tempP.x, tempP.y, 12, 12);
    //ofSetColor(ofColor::orange);
    //ofDrawRectangle(temp);
    ofSetColor(ofColor::white);
    drawMovePlaform(getPositionTranform());
}


ofVec2f AvatarDef::getPositionTranform(){
    return  a->getPosition() - face->rect.getPosition() + 320;
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
    ofPushView();
    n = n + 1/2.0;
    ofRectangle temp;
    temp.setFromCenter(p.x, p.y, 36, 36);
    temp.setFromCenter(0, 0, 36/2, 36/2);
    ofTranslate(p.x/2, p.y/2);
    ofRotate(a->polygon.getRotation());
    ofVec2f v = a->getVelocity();
    /*
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
            ofSetColor(ofColor::blueSteel);
            //ofDrawRectangle(temp);
            moveImages[((int)floor(n)) % 12][0].draw(-moveImages[((int)floor(n)) % 12][0].getWidth()/4, -moveImages[((int)floor(n)) % 12][0].getHeight()/4 -10/2, moveImages[((int)floor(n)) % 12][0].getWidth()/2, moveImages[((int)floor(n)) % 12][0].getHeight()/2);
        }
        else if(v.x < 0){
            ofSetColor(ofColor::blueSteel);
            //ofDrawRectangle(temp);
            moveImages[((int)floor(n)) % 12][1].draw(-moveImages[((int)floor(n)) % 12][1].getWidth()/4, -moveImages[((int)floor(n)) % 12][1].getHeight()/4 -10/2, moveImages[((int)floor(n)) % 12][1].getWidth()/2, moveImages[((int)floor(n)) % 12][1].getHeight()/2);

        }
        else{
            
            ofSetColor(ofColor::blueSteel);
            ofDrawRectangle(temp);
            ofSetColor(ofColor::violet);
            ofDrawRectangle(temp);
            //moveImages[0].draw(-moveImages[0].getWidth()/4, -moveImages[0].getHeight()/4 -10/2, moveImages[0].getWidth()/2, moveImages[0].getHeight()/2);
            //moveImages[((int)floor(n)) % 12].draw(-moveImages[((int)floor(n)) % 12].getWidth()/2, -moveImages[((int)floor(n)) % 12].getHeight()/2 -10/2, moveImages[((int)floor(n)) % 12].getWidth(), moveImages[((int)floor(n)) % 12].getHeight());
        }
    }
    
    if (v.x > 0) {
        
    }else if(v.x < 0){
        
    }else{
        
    }
    */
    ofSetColor(ofColor::violet);
    int InputX  = a->s->directionalCross[1] - a->s->directionalCross[0];
    if (InputX == -1) {
        moveImages[((int)floor(n)) % 12][1].draw(-moveImages[((int)floor(n)) % 12][1].getWidth()/4, -moveImages[((int)floor(n)) % 12][1].getHeight()/4 -10/2, moveImages[((int)floor(n)) % 12][1].getWidth()/2, moveImages[((int)floor(n)) % 12][1].getHeight()/2);
    }
    else if (InputX == 1){
        moveImages[((int)floor(n)) % 12][0].draw(-moveImages[((int)floor(n)) % 12][0].getWidth()/4, -moveImages[((int)floor(n)) % 12][0].getHeight()/4 -10/2, moveImages[((int)floor(n)) % 12][0].getWidth()/2, moveImages[((int)floor(n)) % 12][0].getHeight()/2);
    }
    else{
        motionlessImage.draw(-motionlessImage.getWidth()/4, -motionlessImage.getHeight()/4 -10/2, motionlessImage.getWidth()/2,motionlessImage.getHeight()/2);
    }

    
    ofPopView();

    
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

