//
//  SpriteAvatar.h
//  ProjetMapping
//
//  Created by FatDazz_mac on 24/03/2018.
//
//

#pragma once

#include "ofMain.h"
#include "Sprite.h"
#include "Avatar.h"

void AvatarDef::drawMove(ofVec2f p){
    n = n + 1/10.0;
    moveImages[((int)floor(n)) % 4].draw(p);
}