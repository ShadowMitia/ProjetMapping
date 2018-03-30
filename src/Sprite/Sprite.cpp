//
//  Sprite.cpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 06/02/2018.
//
//

#include "Sprite.h"
#include "Avatar.h"
#include "ObjBlock.h"
#include "ObjPickup.h"
#include "ObjTrampoline.h"
#include "WorldsBox2d.h"
#include "SpriteAvatar.h"
/*
Category bits:
PLATFORM : 0x0001
PORTAL   : 0x0002
LADDER   : 0x0004
CLONE    : 0x0008
AVATAR   : 0x0010
BLOCK    : 0x0020
PICKUP   : 0x0040
MUSHROOM : 0x0080
*/
