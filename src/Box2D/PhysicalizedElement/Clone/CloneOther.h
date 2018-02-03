//
//  CloneOther.h
//  ProjetMapping
//
//  Created by FatDazz_mac on 17/01/2018.
//
//


#pragma once
#include "Clone.h"


void CloneBox2d::collisionFonctionUnknown(){ // le 1.5 est arbitraire √† changer
    if (polygon.tabCollision[4] && !polygon.tabCollision[2]) {
        objSource->setPosition(ofVec2f(objSource->getPosition().x-1.5, objSource->getPosition().y));
    }
    if (polygon.tabCollision[3] && !polygon.tabCollision[2]) {
        objSource->setPosition(ofVec2f(objSource->getPosition().x+1.5, objSource->getPosition().y));
    }
    if (polygon.tabCollision[2]){
        objSource->setPosition(ofVec2f(objSource->getPosition().x, this->polygon.getPosition().y));
    }
}
void CloneBox2d::contactStartUnknown(b2Fixture *_fixture, dataSprite *OtherSprite){}
void CloneBox2d::contactEndUnknown(b2Fixture *_fixture, dataSprite *OtherSprite){}
