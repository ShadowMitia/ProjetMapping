//
//  Platform.cpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 02/08/2017.
//
//

#include "Platform.h"
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

void Platform::create(b2World *_b2World, ofPolyline _groundLine, uint16 mask){
    
    //ground.clear();
    ground.addVertexes(_groundLine);
    ground.setPhysics(0, 0, 0.5f); // (0.0, 0.1, 0.7)
    ground.create(_b2World);

    ground.setData(new dataSprite());
    dataSprite* data = (dataSprite*)ground.getData();
    data->sprite = Sprite::PLATFORM;
    data->physicalizedElement = this;

    b2Filter tempFilter;
    tempFilter.categoryBits = mask;
    tempFilter.maskBits = 0x0008 | 0x0010 | 0x0020 | 0x0040 | 0x0080;
    ground.setFilterData(tempFilter);
}

void Platform::draw(){
    ground.draw();
}

