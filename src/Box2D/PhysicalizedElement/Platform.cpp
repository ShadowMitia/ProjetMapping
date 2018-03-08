//
//  Platform.cpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 02/08/2017.
//
//

#include "Platform.h"
#include "Sprite.h"
/*
 Category bits:
 PLATFORM       : 0x0001
 PLATFORM-1     : 0x0002
 PLATFORM-2     : 0x0004
 PORTAL         : 0x0008
 LADDER         : 0x0010
 AVATAR         : 0x0020
 AVATAR-top     : 0x0040
 OBJ            : 0x0080
 OBJ-top        : 0x0100
 MUSHROOM-top   : 0x0200
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
    tempFilter.maskBits =   Category::AVATAR | Category::OBJ;
    ground.setFilterData(tempFilter);
}

void Platform::draw(){
    ground.draw();
}

void Platform::contactStart(ofxBox2dContactArgs e, b2Fixture *_fixture, dataSprite *OtherSprite){

}