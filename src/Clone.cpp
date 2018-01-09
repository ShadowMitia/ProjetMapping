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
        if (collision) {
            objSource->setPosition(ofVec2f(portalSource->getPosition().x - objSource->polygon.getBoundingBox().getMaxX(), objSource->getPosition().y));
            collision = false;
        }
        ofPoint temp;
        PositionObjSource = objSource->getPosition();
        temp = PositionObjSource - portalSource->getPosition() + portalDestination->getPosition();
        polygon.setPosition(temp);
    }
}
void CloneBox2d::create(){
    statut++;
    polygon.addVertices(objSource->polygon.getVertices());
    polygon.setPhysics(10.f, 0, 0);
    //polygon.setPhysics(VarConst::densityAvatar, VarConst::bounceAvatar, 0);
    polygon.FilterDataObjet.categoryBits = 0x0064;
    polygon.FilterDataObjet.maskBits = 0x0001 | 0x0016;
    polygon.FilterDataSide.categoryBits = 0x0002;
    polygon.FilterDataSide.maskBits = 0x0016;
    polygon.create(portalSource->getb2World(),true);

    polygon.setData(new dataSprite());
    dataSprite* data = (dataSprite*)polygon.getData();
    if (data!=nullptr) { // cela ne regle pas la question danger !!!!!!!!!! sleep
        data->sprite = Sprite::CLONE;
        data->physicalizedElement = this;
    }
}
void CloneBox2d::draw(){
    ofSetColor(ofColor::brown);
    polygon.draw();
}

void CloneBox2d::contactStart(b2Fixture* _fixture, dataSprite *OtherSprite){
    //cout << "contactStart Clone: " << endl;
        b2Fixture * f = polygon.body->GetFixtureList()->GetNext()->GetNext()->GetNext()->GetNext();
        if (f == _fixture) {
            cout << "Star Clone RIGHT " << ofGetElapsedTimef() <<endl;
            collision = true;
        }
        f = polygon.body->GetFixtureList()->GetNext()->GetNext()->GetNext();
        if (f == _fixture) {
            cout << "Star Clone LEFT " << ofGetElapsedTimef() <<endl;}
}
void CloneBox2d::contactEnd(b2Fixture* _fixture, dataSprite* OtherSprite){
    PhysicalizedElement::contactEnd(_fixture, OtherSprite);
    b2Fixture * f = polygon.body->GetFixtureList()->GetNext()->GetNext()->GetNext()->GetNext();
    if (f == _fixture) {
        cout << "End Clone RIGHT " << ofGetElapsedTimef() <<endl;}
    f = polygon.body->GetFixtureList()->GetNext()->GetNext()->GetNext();
    if (f == _fixture) {
        cout << "End Clone LEFT " << ofGetElapsedTimef() <<endl;}
}

