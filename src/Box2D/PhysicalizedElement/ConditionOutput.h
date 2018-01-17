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


bool leftCondition(float _x ,CloneBox2d* _clone){
    //cout << " leftCondition " << endl;
    if (_x > _clone->portalSource->getPosition().x) return true;
    else return false;
}

bool rightCondition(float _x ,CloneBox2d* _clone){
    //cout << " rightCondition " << endl;
    if (_x < _clone->portalSource->getPosition().x) return true;
    else return false;
}