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
    if (portalDestination->conditionFunction(objSource->getPosition().x,this)) {
        objSource->polygon.setPosition(polygon.getPosition());
    }
    
}
void CloneBox2d::create(){
    statut++;
    for (int i= 0; i < 5; ++i) {
        polygon.tabCollision[i]= false;
    }
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
    polygon.body->SetGravityScale(0.0);
}
void CloneBox2d::update(){
    if (statut == 0) {
        create();
        PositionClone = polygon.getPosition();
    }
    
    if (objSource->viewpoint == Viewpoint::MODE_ANGLE) {
        portalDestination = portalSource->linkedPortal[0];}
    else{
        portalDestination = portalSource->linkedPortal[1];
    }
    
    if (portalDestination != nullptr) {
        ofPoint temp;

        if (polygon.tabCollision[4] && !polygon.tabCollision[2]) {
            //objSource->setPosition(ofVec2f(portalSource->getPosition().x - objSource->polygon.getBoundingBox().getMaxX(), objSource->getPosition().y));
        }
        
        if (polygon.tabCollision[2]){
            objSource->setPosition(ofVec2f(objSource->getPosition().x, this->polygon.getPosition().y));
        }
            PositionClone = polygon.getPosition();
            temp = portalDestination->directionFunction(this); // fonction du portal end
            polygon.setPosition(temp);
    

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
            //cout << "Star Clone RIGHT " << ofGetElapsedTimef() <<endl;
            polygon.tabCollision[4] = true;
            
            
        }
        f = polygon.body->GetFixtureList()->GetNext()->GetNext();
        if (f == _fixture) {
            cout << "Star Clone DONW " << ofGetElapsedTimef() <<endl;
            polygon.tabCollision[2] = true;
            objSource->SetGravityScale(0.0f);

        }
}
void CloneBox2d::contactEnd(b2Fixture* _fixture, dataSprite* OtherSprite){
    PhysicalizedElement::contactEnd(_fixture, OtherSprite);
    b2Fixture * f = polygon.body->GetFixtureList()->GetNext()->GetNext()->GetNext()->GetNext();
    if (f == _fixture) {
        //cout << "End Clone RIGHT " << ofGetElapsedTimef() <<endl;
        polygon.tabCollision[4] = false; 
    }
    
    f = polygon.body->GetFixtureList()->GetNext()->GetNext();
    if (f == _fixture) {
        cout << "End Clone DONW " << ofGetElapsedTimef() <<endl;
        polygon.tabCollision[2] = false;
        objSource->SetGravityScale(1.0f);
    }
}
