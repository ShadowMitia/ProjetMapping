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


ofVec2f CloneBox2d::multyMatrix(ofVec2f v)
{
    ofVec2f i;
    i.x = matrixTrans[0]*v.x + matrixTrans[1]*v.y;
    i.y = -matrixTrans[1]*v.x + matrixTrans[0]*v.y;
    return i;
    
}
CloneBox2d::CloneBox2d(PhysicalizedElement* _objSource, Portal* _portalSource, Portal* _portalDestination)
{
    
    objSource = static_cast<Teleportable*>(_objSource);
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
        
        //// atention bug ici
        Avatar* objAvatar = static_cast<Avatar*>(objSource);
        objAvatar->setMove(portalDestination->direct);
        
    }
}
void CloneBox2d::create()
{
    statut++;
    polygon.addVertices(objSource->polygon.getVertices());
    //polygon.setPhysics(10.f, 0, 0);
    polygon.setPhysics(VarConst::densityAvatar, VarConst::bounceAvatar, 0);
    polygon.FilterDataObjet.categoryBits = 0x0064;
    polygon.FilterDataObjet.maskBits = 0x0001 | 0x0016| 0x0008;
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
    
    if (!objSource->viewPoint){
        portal = false;
        portalDestination = portalSource->linkedPortal[portal];}
    else{
        portal = true;
        portalDestination = portalSource->linkedPortal[portal];}
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
            portal = false;
            portalDestination = portalSource->linkedPortal[portal];}
        else{
            portal = true;
            portalDestination = portalSource->linkedPortal[portal];}
        if (tempPortal != portalDestination) {
            for (int i = 1; i<5; ++i) {
                polygon.tabCollision[i] = 0;
            }
        }
    }else objSource->viewPoint=portal;
    
    if (portalDestination != nullptr) {
        ofPoint temp;
        if (lockTransfer) {
            for (int i=1; i<5; ++i) {
                polygon.tabCollision[i]=0;
            }
            !lockTransfer;
        }
        if (polygon.tabCollision[1] || polygon.tabCollision[2]|| polygon.tabCollision[3] || polygon.tabCollision[4]) {
            
            if (objSource->polygon.tabCollision[2]) {
                //polygon.body->SetGravityScale(0.0);
            }else{ //polygon.body->SetGravityScale(1.0);
            }
            
            ofVec2f vTemp = ofVec2f(0.f, 0.f);
            vTemp = objSource->getVelocity();
            if (polygon.tabCollision[2]) {
                Avatar* a = static_cast<Avatar*>(objSource);
                a->setJumping(false); // il y a de l'idŽe mais a ne marche pas
                if (vTemp.y > 0) {
                    vTemp.y = 0;
                }
            }
            polygon.setVelocity(objSource->getVelocity()); // << ici le probleme du clone qui acroche les sides  <<-----
            //temp = portalSource->portalRect.position - (portalDestination->*fonction)(polygon.getPosition());
            const ofVec2f (Portal::*fonction)(ofVec2f) = portalSource->getObjPosition;
            
            temp = (portalDestination->*fonction)(polygon.getPosition());
            matrixTrans[0] =  -(portalSource->orient.x * portalDestination->orient.x) -(portalSource->orient.y * portalDestination->orient.y);
            matrixTrans[1] =  (portalSource->orient.x * portalDestination->orient.y) - (portalSource->orient.y * portalDestination->orient.x);
            matrixTrans[1] = - matrixTrans[1];
            temp = portalSource->portalRect.getCenter() -  multyMatrix(temp);
            
            objSource->setPosition(temp);
            objSource->setVelocity(vTemp);
        }
        else{
            const ofVec2f (Portal::*fonction)(ofVec2f) = portalDestination->getObjPosition;
            //temp = portalDestination->portalRect.position - (portalSource->*fonction)(objSource->getPosition());
            //temp = portalDestination->portalRect.position - (portalSource->*getObjPosition)(objSource->getPosition()); // fonction du portal end
            temp = (portalSource->*fonction)(objSource->getPosition());
            matrixTrans[0] = - (portalSource->orient.x * portalDestination->orient.x) - (portalSource->orient.y * portalDestination->orient.y);
            matrixTrans[1] = (portalSource->orient.x * portalDestination->orient.y) - (portalSource->orient.y * portalDestination->orient.x);
            temp = portalDestination->portalRect.getCenter() -  multyMatrix(temp);
            polygon.setPosition(temp);  // *this.*contactStartFonction
        }
        
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
        //cout << "clone Start contact" << endl;
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
    
    //objSource->setVelocity(ofVec2f(0, 0)); // a mettre dans l'le preSolver pour savoir quelle sens
    
}
void CloneBox2d::contactEnd(ofxBox2dContactArgs e, b2Fixture* _fixture, dataSprite* OtherSprite)
{
    if (abs(e.contact->GetManifold()->localPoint.x) != 0.2f && abs(e.contact->GetManifold()->localPoint.y) != 0.2f) {
        //cout << "clone End contact" << endl;
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
    
}
void CloneBox2d::PostSolve(b2Fixture* _fixture,dataSprite* OtherSprite, const b2ContactImpulse* impulse)
{
    
}
void CloneBox2d::PreSolve(b2Fixture* _fixture,dataSprite* OtherSprite,ofxBox2dPreContactArgs e)
{
}
