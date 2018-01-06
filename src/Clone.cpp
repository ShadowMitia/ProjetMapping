//
//  Clone.cpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 05/01/2018.
//
//

#include "Clone.h"
#include "Portal.h"



CloneBox2d::CloneBox2d(PhysicalizedElement* _objSource, Portal* _portalSource, Portal* _portalDestination){
    
    objSource = static_cast<Teleportable*>(_objSource);
    portalSource = _portalSource;
    portalDestination = _portalDestination;
    statut = 0;

}
void CloneBox2d::update(){
    if (statut == 0) {
        create();
    }
    polygon.setPosition(objSource->polygon.getPosition().x + 100, objSource->polygon.getPosition().y);
}
void CloneBox2d::create(){
    statut++;
    polygon.addVertices(objSource->polygon.getVertices());
    polygon.setPhysics(0, 0, 0);
    polygon.create(portalSource->getb2World());
}
void CloneBox2d::draw(){
    ofSetColor(ofColor::brown);
    polygon.draw();
}