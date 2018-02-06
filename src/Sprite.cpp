//
//  Sprite.cpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 06/02/2018.
//
//

#include "Sprite.h"
#include "Avatar.h"
void AvatarDef::draw(){
    ofRectangle temp;
    temp.setFromCenter(a->getPosition().x, a->getPosition().y, 12, 12);
    ofSetColor(ofColor::azure);
    ofDrawRectangle(temp);
}