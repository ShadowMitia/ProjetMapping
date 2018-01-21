//
//  Clone.cpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 05/01/2018.
//
//

#include "Clone.h"
#include "Portal.h"
#include "Avatar.h"
#include "CloneAvatar.h"
#include "CloneOther.h"
CloneBox2d::CloneBox2d(PhysicalizedElement* _objSource, Portal* _portalSource, Portal* _portalDestination){
    
    objSource = static_cast<Teleportable*>(_objSource);
    portalSource = _portalSource;
    portalDestination = _portalDestination;
    statut = 0;
    
}
CloneBox2d::~CloneBox2d(){
    if (portalDestination!=nullptr && portalDestination->conditionFunction(objSource->getPosition(),this)) {
        ofVec2f v = objSource->getVelocity();
        objSource->polygon.setPosition(polygon.getPosition());
        objSource->setVelocity(v);
    }
}
void CloneBox2d::create(){
    statut++;
    polygon.addVertices(objSource->polygon.getVertices());
    //polygon.setPhysics(10.f, 0, 0);
    polygon.setPhysics(VarConst::densityAvatar, VarConst::bounceAvatar, 0);
    polygon.FilterDataObjet.categoryBits = 0x0064;
    polygon.FilterDataObjet.maskBits = 0x0001 | 0x0016;
    polygon.FilterDataSide.categoryBits = 0x0002;
    polygon.FilterDataSide.maskBits = 0x0016;
    polygon.create(portalSource->getb2World(),false);
    
    polygon.setData(new dataSprite());
    dataSprite* data = (dataSprite*)polygon.getData();
    if (data!=nullptr) { // cela ne regle pas la question danger !!!!!!!!!! sleep
        data->sprite = Sprite::CLONE;
        data->physicalizedElement = this;
    }
    polygon.body->SetGravityScale(0.0);
    data = (dataSprite*)(objSource->polygon.body->GetUserData());
    if (data->sprite==Sprite::AVATAR) {
        collisionFonction = &CloneBox2d::collisionFonctionAvatar;
        contactStartFonction = &CloneBox2d::contactStartAvatar;
        contactEndFonction = &CloneBox2d::contactEndAvatar;
    }
    else{
        collisionFonction =  &CloneBox2d::collisionFonctionUnknown;
    }
}
void CloneBox2d::update(){
    if (statut == 0)create();
    
    if (objSource->viewpoint == Viewpoint::MODE_ANGLE) {
        portalDestination = portalSource->linkedPortal[0];}
    else{
        portalDestination = portalSource->linkedPortal[1];
    }
    
    if (portalDestination != nullptr) {
        ofPoint temp;
            //(*this.*collisionFonction)();

        if (polygon.tabCollision[1] || polygon.tabCollision[2]|| polygon.tabCollision[3] || polygon.tabCollision[4]) {
            //cout << "ici "<< ofGetElapsedTimeMillis()<<endl;
            polygon.setVelocity(objSource->getVelocity());
            temp =portalSource->portalRect.position - portalDestination->getObjPosition(polygon.getPosition());
            objSource->setPosition(temp);
        }
        else{
            temp = portalDestination->portalRect.position - portalSource->getObjPosition(objSource->getPosition()); // fonction du portal end
            polygon.setPosition(temp);
        }
        
    }else{
        polygon.setPosition(0., 0.);
        portalSource->nullFunction(this);
    }
}
void CloneBox2d::draw(){
    ofSetColor(ofColor::brown);
    polygon.draw();
}
void CloneBox2d::contactStart(ofxBox2dContactArgs e, b2Fixture* _fixture, dataSprite* OtherSprite){
    //cout << "contactStart Clone: " << endl;
    //(*this.*contactStartFonction)(_fixture,OtherSprite);
    if (abs(e.contact->GetManifold()->localPoint.x) != 0.2f && abs(e.contact->GetManifold()->localPoint.y) != 0.2f) {
    if (e.contact->GetManifold()->localNormal.y < 0.f) {
        //cout << "Start Clone ok  " << ofGetElapsedTimef() <<endl;
        polygon.tabCollision[2]++;
    }
    if (e.contact->GetManifold()->localNormal.y > 0.f) {
        //cout << "Start Clone ok  " << ofGetElapsedTimef() <<endl;
        polygon.tabCollision[1]++;
    }
    if (e.contact->GetManifold()->localNormal.x < 0.f) {
        //cout << "Start Clone Rignt  " << ofGetElapsedTimef() <<endl;
        polygon.tabCollision[4]++;
    }
    if (e.contact->GetManifold()->localNormal.x > 0.f) {
        //cout << "Start Clone ok  " << ofGetElapsedTimef() <<endl;
        polygon.tabCollision[3]++;
    }
    }
    
        //objSource->setVelocity(ofVec2f(0, 0)); // a mettre dans l'le preSolver pour savoir quelle sens

}
void CloneBox2d::contactEnd(ofxBox2dContactArgs e, b2Fixture* _fixture, dataSprite* OtherSprite){
    //PhysicalizedElement::contactEnd(_fixture, OtherSprite);
    //(*this.*contactEndFonction)(_fixture,OtherSprite);
    if (abs(e.contact->GetManifold()->localPoint.x) != 0.2f && abs(e.contact->GetManifold()->localPoint.y) != 0.2f) {
    if (e.contact->GetManifold()->localNormal.y < 0.f) {
        //cout << "Start Clone ok  " << ofGetElapsedTimef() <<endl;
        polygon.tabCollision[2]--;
    }
    if (e.contact->GetManifold()->localNormal.y > 0.f) {
        //cout << "Start Clone ok  " << ofGetElapsedTimef() <<endl;
        polygon.tabCollision[1]--;
    }
    if (e.contact->GetManifold()->localNormal.x < 0.f) {
        //cout << "Start Clone ok  " << ofGetElapsedTimef() <<endl;
        polygon.tabCollision[4]--;
    }
    if (e.contact->GetManifold()->localNormal.x > 0.f) {
        //cout << "Start Clone ok  " << ofGetElapsedTimef() <<endl;
        polygon.tabCollision[3]--;
    }
    }

    

}
void CloneBox2d::PostSolve(b2Fixture* _fixture,dataSprite* OtherSprite, const b2ContactImpulse* impulse)
{
    PhysicalizedElement::PostSolve(_fixture,OtherSprite, impulse);


}
void CloneBox2d::PreSolve(b2Fixture* _fixture,dataSprite* OtherSprite,ofxBox2dPreContactArgs e)
{
    
}
