//
//  Platform.cpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 02/08/2017.
//
//

#include "Platform.h"

void Platform::create(b2World *_b2World, ofPolyline _groundLine,ofx::LightSystem2D* _LightSystem){
    
    //ground.clear();
    LightSystem =_LightSystem;
    ground.addVertexes(_groundLine);
    ground.setPhysics(0, 0, 0); // (0.0, 0.1, 0.7)
    ground.create(_b2World);
    shape = std::make_shared<ofx::Shape2D>();
    shape->setShape(_groundLine);
    shape->setColor(ofColor::white);
    shape->bVisible = false;
    LightSystem->add(shape);
    
}

void Platform::draw(){
    ground.draw();
}