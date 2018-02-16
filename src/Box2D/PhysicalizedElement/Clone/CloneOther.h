//
//  CloneOther.h
//  ProjetMapping
//
//  Created by FatDazz_mac on 17/01/2018.
//
//


#pragma once
#include "Clone.h"


void CloneBox2d::collisionFonctionOther(){
    ofPoint temp;
    if (lockTransfer) {
        for (int i=1; i<5; ++i) {
            polygon.tabCollision[i]=0;
        }
        !lockTransfer;
    }
    
    if (polygon.tabCollision[1] || polygon.tabCollision[2]|| polygon.tabCollision[3] || polygon.tabCollision[4]) {
        
        ofVec2f vTemp = ofVec2f(0.f, 0.f);
        vTemp = objSource->getVelocity();
        
        if (polygon.tabCollision[2]) {
            if (vTemp.y > 0) {
                vTemp.y = 0;
            }
        }
        
        polygon.setVelocity(objSource->getVelocity()); // << ici le probleme du clone qui acroche les sides  <<-----
        
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
        temp = (portalSource->*fonction)(objSource->getPosition());
        matrixTrans[0] = - (portalSource->orient.x * portalDestination->orient.x) - (portalSource->orient.y * portalDestination->orient.y);
        matrixTrans[1] = (portalSource->orient.x * portalDestination->orient.y) - (portalSource->orient.y * portalDestination->orient.x);
        temp = portalDestination->portalRect.getCenter() -  multyMatrix(temp);
        polygon.setPosition(temp);
    }

    

}
void CloneBox2d::contactStartOther(b2Fixture *_fixture, dataSprite *OtherSprite){}
void CloneBox2d::contactEndOther(b2Fixture *_fixture, dataSprite *OtherSprite){}
void CloneBox2d::delectCloneOther(){
    objSource->SetGravityScale(1.0);
    
}