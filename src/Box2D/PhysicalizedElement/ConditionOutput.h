//
//  ConditionOutput.h
//  ProjetMapping
//
//  Created by FatDazz_mac on 17/01/2018.
//
//
#pragma once
#include "Portal.h"
#include "Clone.h"


bool leftCondition(ofVec2f p ,CloneBox2d* _clone){
    //cout << " leftCondition " << endl;
    if (p.x < _clone->portalSource->getPosition().x) return true;
    else return false;
}
bool rightCondition(ofVec2f p ,CloneBox2d* _clone){
    //cout << " rightCondition " << endl;
    if (p.x > _clone->portalSource->getPosition().x) return true;
    else return false;
}
bool topCondition(ofVec2f p ,CloneBox2d* _clone){
    //cout << " rightCondition " << endl;
    if (p.y < _clone->portalSource->getPosition().y) return true;
    else return false;
}
bool downCondition(ofVec2f p ,CloneBox2d* _clone){
    //cout << " rightCondition " << endl;
    if (p.y > _clone->portalSource->getPosition().y) return true;
    else return false;
}
