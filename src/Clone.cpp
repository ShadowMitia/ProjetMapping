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
CloneBox2d::~CloneBox2d(){
    if (objSource->getPosition().x > portalSource->getPosition().x) {
        objSource->polygon.setPosition(polygon.getPosition());
    }
}
void CloneBox2d::update(){
    if (statut == 0) {
        create();
    }
    
    if (objSource->viewpoint == Viewpoint::MODE_ANGLE) {
        portalDestination = portalSource->linkedPortal[0];}
    else{
        portalDestination = portalSource->linkedPortal[1];
    }
    
    if (portalDestination != nullptr) {
        ofPoint temp;
        temp = objSource->getPosition() - portalSource->getPosition() + portalDestination->getPosition();
        polygon.setPosition(temp);
    }
}
void CloneBox2d::create(){
    statut++;
    polygon.addVertices(objSource->polygon.getVertices());
    polygon.setPhysics(0, 0, 0);
    polygon.create(portalSource->getb2World());
    
    polygon.body->SetType(b2BodyType::b2_dynamicBody);
    polygon.body->SetFixedRotation(true);
    
    b2Filter tempFilter;
    tempFilter.categoryBits = 0x0064;
    tempFilter.maskBits = 0x0001 | 0x0004 | 0x0008 | 0x0016 ;
    polygon.setFilterData(tempFilter);
    
    polygon.setData(new dataSprite());
    dataSprite* data = (dataSprite*)polygon.getData();
    data->sprite = Sprite::CLONE;
    data->physicalizedElement = this;
    
    
}
void CloneBox2d::draw(){
    ofSetColor(ofColor::brown);
    polygon.draw();
}

void CloneBox2d::contactStart(dataSprite *OtherSprite){
    cout << "contactStart Clone" << ofGetElapsedTimeMillis() << endl;
}