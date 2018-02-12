//
//  CloneAvatar.cpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 17/01/2018.
//
//

#pragma once

#include "Clone.h"
#include "Avatar.h"


void CloneBox2d::collisionFonctionAvatar(){
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
            Avatar* a = static_cast<Avatar*>(objSource);
            a->setJumping(false); // il y a de l'idŽe mais a ne marche pas
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
        polygon.setPosition(temp);  // *this.*contactStartFonction
    }
    
}

void CloneBox2d::contactStartAvatar(b2Fixture *_fixture, dataSprite *OtherSprite){
    Avatar *obj = static_cast<Avatar*>(objSource);
    if (OtherSprite->sprite==Sprite::LADDER) {
        Ladder *l = static_cast<Ladder*>(OtherSprite->physicalizedElement);
        
        ladder = true;
    }
}

void CloneBox2d::contactEndAvatar(b2Fixture *_fixture, dataSprite *OtherSprite){
    Avatar *obj = static_cast<Avatar*>(objSource);
    if (OtherSprite->sprite==Sprite::LADDER) {
        ladder = false;
    }
    
}

void CloneBox2d::delectCloneAvatar(){
    Avatar* objAvatar = static_cast<Avatar*>(objSource);
    if (ladder) {
        objAvatar->lockLadder.ladderDown = objAvatar->lockLadder.ladderTop = false;
        objAvatar->SetGravityScale(0.0); // regardŽ si bien ici
        objAvatar->setMove(Deplacement::DOWN); // changer pas Ladder
    }
    else{
    objAvatar->lockLadder.ladder =  objAvatar->lockLadder.ladderDown = objAvatar->lockLadder.ladderTop = false;
    objAvatar->SetGravityScale(1.0); // regardŽ si bien ici
        if (objAvatar->modeDeplace == Deplacement::PLATFORM || objAvatar->modeDeplace == Deplacement::LADDER) {
            cout << "changement de mode "<< endl;
            objAvatar->setMove(portalDestination->direct);
        }
    }
}