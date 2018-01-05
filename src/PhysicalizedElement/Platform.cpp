//
//  Platform.cpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 02/08/2017.
//
//

#include "Platform.h"

void Platform::create(b2World *_b2World, ofPolyline _groundLine){
    
    //ground.clear();
    ground.addVertexes(_groundLine);
    ground.setPhysics(0, 0, 0.5f); // (0.0, 0.1, 0.7)
    ground.create(_b2World);

    ground.setData(new dataSprite());
    dataSprite* data = (dataSprite*)ground.getData();
    data->sprite = Sprite::PLATFORM;
    data->physicalizedElement = this;

    b2Filter tempFilter;
    tempFilter.categoryBits = 0x0016;
    tempFilter.maskBits = 0x0001 | 0x0002 | 0x0004 | 0x0008;
    ground.setFilterData(tempFilter);
    
}

void Platform::draw(){
    ground.draw();
}
