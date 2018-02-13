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

ofVec2f CloneBox2d::multyMatrix(ofVec2f v)
{
    ofVec2f i;
    i.x = matrixTrans[0]*v.x + matrixTrans[1]*v.y;
    i.y = -matrixTrans[1]*v.x + matrixTrans[0]*v.y;
    return i;
    
}
CloneBox2d::CloneBox2d(Teleportable* _objSource, Portal* _portalSource, Portal* _portalDestination)
{
    
    objSource = _objSource;
    portalSource = _portalSource;
    portalDestination = _portalDestination;
    statut = 0;
    
}
CloneBox2d::~CloneBox2d()
{
    if (portalDestination!=nullptr && portalSource->conditionFunction(objSource->getPosition(),this)) {
        ofVec2f v = objSource->getVelocity();
        objSource->polygon.setPosition(polygon.getPosition());
        objSource->setVelocity(v);
        objSource->sprite->face = portalDestination->face;
        objSource->top = top;
        (*this.*delectClone)();
        
    }
}
void CloneBox2d::create()
{
    statut++;
    polygon.addVertices(objSource->polygon.getVertices());
    //polygon.setPhysics(10.f, 0, 0);
    polygon.setPhysics(VarConst::densityAvatar, VarConst::bounceAvatar, 0);
    polygon.FilterDataObjet.categoryBits = 0x0008;
    polygon.FilterDataObjet.maskBits = 0x0001| 0x0004 | 0x0008 | 0x0010 | 0x0020 | 0x0040 | 0x0080;
    polygon.create(portalSource->getb2World(),false);
    
    polygon.setData(new dataSprite());
    dataSprite* data = (dataSprite*)polygon.getData();
    
    if (data!=nullptr) { // cela ne regle pas la question danger !!!!!!!!!! sleep
        data->sprite = Sprite::CLONE;
        data->physicalizedElement = this;
    }
    
    data = (dataSprite*)(objSource->polygon.body->GetUserData());
    if (data->sprite==Sprite::AVATAR) {
        collisionFonction = &CloneBox2d::collisionFonctionAvatar;
        delectClone = &CloneBox2d::delectCloneAvatar;
        contactStartFonction = &CloneBox2d::contactStartAvatar;
        contactEndFonction = &CloneBox2d::contactEndAvatar;
    }
    else{
        collisionFonction =  &CloneBox2d::collisionFonctionOther;
        delectClone = &CloneBox2d::delectCloneOther;
        contactStartFonction = &CloneBox2d::contactStartOther;
        contactEndFonction = &CloneBox2d::contactEndOther;
    }
    
    if (!objSource->viewPoint){
        portalView = false;
        portalDestination = portalSource->linkedPortal[portalView];}
    else{
        portalView = true;
        portalDestination = portalSource->linkedPortal[portalView];}
    

    
    polygon.body->SetGravityScale(0.0);

}
void CloneBox2d::update()
{
    if (statut == 0)create();
    
    const ofVec2f (Portal::*f)(ofVec2f) = portalSource->getObjPosition;
    ofPoint t = (portalSource->*f)(objSource->getPosition());
    t = t*portalSource->orient;
    if (t.x < - 3  || t.y < -3) {
        Portal *tempPortal = portalDestination;
        if (!objSource->viewPoint){
            portalView = false;
            portalDestination = portalSource->linkedPortal[portalView];}
        else{
            portalView = true;
            portalDestination = portalSource->linkedPortal[portalView];}
        if (tempPortal != portalDestination) {
            for (int i = 1; i<5; ++i) {
                polygon.tabCollision[i] = 0;
            }
        }
    }else objSource->viewPoint=portalView;
    
    
    
    
    if (portalDestination != nullptr) {
        
    (*this.*collisionFonction)();
    
    }else{
        polygon.setPosition(0. , 0.);
        portalSource->nullFunction(this);}
}
void CloneBox2d::draw()
{
    ofSetColor(ofColor::brown);
    polygon.draw();
}
void CloneBox2d::contactStart(ofxBox2dContactArgs e, b2Fixture* _fixture, dataSprite* OtherSprite)
{
    if (abs(e.contact->GetManifold()->localPoint.x) != 0.2f && abs(e.contact->GetManifold()->localPoint.y) != 0.2f) {
        
        if (e.contact->GetManifold()->localNormal.y < 0.f) {
            polygon.tabCollision[2]++;
        }
        if (e.contact->GetManifold()->localNormal.y > 0.f) {
            polygon.tabCollision[1]++;
        }
        if (e.contact->GetManifold()->localNormal.x < 0.f) {
            polygon.tabCollision[4]++;
        }
        if (e.contact->GetManifold()->localNormal.x > 0.f) {
            polygon.tabCollision[3]++;
        }
    }
    (*this.*contactStartFonction)(_fixture,OtherSprite);
    
}
void CloneBox2d::contactEnd(ofxBox2dContactArgs e, b2Fixture* _fixture, dataSprite* OtherSprite)
{
    if (abs(e.contact->GetManifold()->localPoint.x) != 0.2f && abs(e.contact->GetManifold()->localPoint.y) != 0.2f) {
        if (e.contact->GetManifold()->localNormal.y < 0.f) {
            polygon.tabCollision[2]--;
        }
        if (e.contact->GetManifold()->localNormal.y > 0.f) {
            polygon.tabCollision[1]--;
        }
        if (e.contact->GetManifold()->localNormal.x < 0.f) {
            polygon.tabCollision[4]--;
        }
        if (e.contact->GetManifold()->localNormal.x > 0.f) {
            polygon.tabCollision[3]--;
        }
    }
    (*this.*contactEndFonction)(_fixture,OtherSprite);
    
}
void CloneBox2d::PostSolve(b2Fixture* _fixture,dataSprite* OtherSprite, const b2ContactImpulse* impulse)
{
    
}
void CloneBox2d::PreSolve(b2Fixture* _fixture,dataSprite* OtherSprite,ofxBox2dPreContactArgs e)
{
}
