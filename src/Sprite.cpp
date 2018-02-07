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
    temp.setFromCenter(160*3/2, 160*3/2, 12, 12);
    //temp.setFromCenter(160, 160, 12, 12);
    ofSetColor(ofColor::black);
    ofDrawRectangle(temp);
}