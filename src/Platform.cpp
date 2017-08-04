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
    ground.setPhysics(0, 0, 0);
    ground.create(_b2World);
    
}

void Platform::draw(){
    ground.draw();
}