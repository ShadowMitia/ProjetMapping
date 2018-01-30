//
//  ConditionNull.h
//  ProjetMapping
//
//  Created by FatDazz_mac on 17/01/2018.
//
//

#pragma once
#include "Portal.h"
#include "Clone.h"

void leftNull(CloneBox2d* _clone){
    if (_clone->objSource->getPosition().x<_clone->portalSource->getPosition().x + 8 ) {
        _clone->objSource->setPosition(ofVec2f(_clone->portalSource->getPosition().x + 8,_clone->objSource->getPosition().y));
    }
}
void rightNull(CloneBox2d* _clone){
    if (_clone->objSource->getPosition().x>_clone->portalSource->getPosition().x - 6 ) {
        _clone->objSource->setPosition(ofVec2f(_clone->portalSource->getPosition().x - 6,_clone->objSource->getPosition().y));
    }
}


void topNull(CloneBox2d* _clone){
    if (_clone->objSource->getPosition().y<_clone->portalSource->getPosition().y + 8 ) {
        _clone->objSource->setPosition(ofVec2f(_clone->objSource->getPosition().x,_clone->portalSource->getPosition().y + 8));
    }
}


void downNull(CloneBox2d* _clone){
    if (_clone->objSource->getPosition().y>_clone->portalSource->getPosition().y - 6 ) {
        _clone->objSource->setPosition(ofVec2f(_clone->objSource->getPosition().x, _clone->portalSource->getPosition().y - 6));
    }
}
void NoNull(CloneBox2d* _clone){}