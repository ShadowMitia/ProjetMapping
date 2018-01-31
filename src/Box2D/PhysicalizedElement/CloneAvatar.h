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

    
    
}

void CloneBox2d::contactStartAvatar(b2Fixture *_fixture, dataSprite *OtherSprite){
    Avatar *obj = static_cast<Avatar*>(objSource);
    b2Fixture * f = polygon.body->GetFixtureList();
    if (f == _fixture){
        
    }
    
    /*
    b2Fixture * f = polygon.body->GetFixtureList()->GetNext()->GetNext()->GetNext();
    if (f == _fixture) {
        //cout << "start Clone Left " << ofGetElapsedTimef() <<endl;
        obj->tabSideClone[3] =false;
    }*/
}

void CloneBox2d::contactEndAvatar(b2Fixture *_fixture, dataSprite *OtherSprite){
    Avatar *obj = static_cast<Avatar*>(objSource);
    obj->cloneJump = true;
    
    /*b2Fixture * f = polygon.body->GetFixtureList()->GetNext()->GetNext()->GetNext();
    if (f == _fixture) {
        //out << "End Clone Left " << ofGetElapsedTimef() <<endl;
        obj->tabSideClone[3] =true;
    }*/
}