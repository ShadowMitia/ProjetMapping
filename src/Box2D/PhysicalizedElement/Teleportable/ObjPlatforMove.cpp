//
//  ObjPlatforMove.cpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 29/03/2018.
//
//
#pragma once
#include "ObjPlatforMove.h"
#include "WorldsBox2d.h"

ObjPlatforMove::ObjPlatforMove(ObjPlatforMoveDef* _pM){
    
    sprite = static_cast<SpriteObj*>(_pM);
    _pM->pM = this;
    std::vector<ofPoint> pts = loadPoints("ObjPickup.dat");
    polygon.addVertices(pts);
    polygon.setPhysics(VarConst::densityAvatar, VarConst::bounceAvatar, 0);
    polygon.create(_pM->world->world.getWorld(), false);

    teleportableFilter.categoryBits = _pM->categoryBits ;
    setFilter(_pM->maskBits | Category::PLATFORM |Category::PLATFORM_1);
    polygon.setData(new dataSprite());
    dataSprite* data = (dataSprite*)polygon.getData();
    data->sprite = Sprite::SignageSign;
    data->physicalizedElement = this;
    polygon.body->SetGravityScale(0.0);
    polygon.setVelocity(_pM->vitesse);
}

void ObjPlatforMove::contactStart(ofxBox2dContactArgs e, b2Fixture *_fixture, dataSprite *OtherSprite){
    
}