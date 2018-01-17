//
//  CloneAvatar.cpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 17/01/2018.
//
//

#pragma once

#include "Clone.h"
#include "Avatar.h"


void CloneBox2d::collisionFonctionAvatar(){
    Avatar *obj = static_cast<Avatar*>(objSource);
    if (polygon.tabCollision[4]) {
    }
    if (polygon.tabCollision[3]) {
    }
    
    if (polygon.tabCollision[2] && obj->cloneJump && !polygon.tabCollision[1]){
        objSource->setPosition(ofVec2f(objSource->getPosition().x, polygon.getPosition().y));
        obj->setJumping(false);
    }
    if (polygon.tabCollision[1]) {
    }
}

void CloneBox2d::contactStartAvatar(b2Fixture *_fixture, dataSprite *OtherSprite){
    Avatar *obj = static_cast<Avatar*>(objSource);
    b2Fixture * f = polygon.body->GetFixtureList()->GetNext()->GetNext()->GetNext();
    if (f == _fixture) {
        cout << "start Clone Left " << ofGetElapsedTimef() <<endl;
        obj->tabSideClone[3] =false;
    }
    f = polygon.body->GetFixtureList()->GetNext()->GetNext()->GetNext()->GetNext();
    if (f == _fixture) {
        //cout << "Start Clone RIGHT  " << ofGetElapsedTimef() <<endl;
        obj->tabSideClone[4] =false;
    }
    f = polygon.body->GetFixtureList()->GetNext();
    if (f == _fixture) {
        if (!obj->tabSideClone[3] || !obj->tabSideClone[4]) {
            cout << "ici" << endl;
            obj->tabSideClone[1] =false;
        }
    }
}

void CloneBox2d::contactEndAvatar(b2Fixture *_fixture, dataSprite *OtherSprite){
    Avatar *obj = static_cast<Avatar*>(objSource);
    obj->cloneJump = true;
    
    b2Fixture * f = polygon.body->GetFixtureList()->GetNext()->GetNext()->GetNext();
    if (f == _fixture) {
        cout << "End Clone Left " << ofGetElapsedTimef() <<endl;
        obj->tabSideClone[3] =true;
    }
    f = polygon.body->GetFixtureList()->GetNext()->GetNext()->GetNext()->GetNext();
    if (f == _fixture) {
        //cout << "end Clone RIGHT " << ofGetElapsedTimef() <<endl;
        obj->tabSideClone[4] =true;
    }
    f = polygon.body->GetFixtureList()->GetNext();
    if (f == _fixture) {
        obj->tabSideClone[1] =true;
    }
}