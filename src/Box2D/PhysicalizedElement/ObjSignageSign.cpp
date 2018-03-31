//
//  ObjSignageSign.cpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 29/03/2018.
//
//

#include "ObjSignageSign.h"
#include "Teleportable.h"

void ObjSignageSign::contactStart(ofxBox2dContactArgs e, b2Fixture *_fixture, dataSprite *OtherSprite){
    Teleportable * t = static_cast<Teleportable*>(OtherSprite->physicalizedElement);
    t->setVelocity(vitesse);
}