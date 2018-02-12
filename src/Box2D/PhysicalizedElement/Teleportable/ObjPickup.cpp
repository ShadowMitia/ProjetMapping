//
//  ObjPickup.cpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 09/02/2018.
//
//

#include "ObjPickup.h"


ObjPickup::ObjPickup(b2World* box2d){
    
    std::vector<ofPoint> pts = loadPoints("avatar.dat");
    polygon.addVertices(pts);
    //polygon.triangulatePoly();
    polygon.setPhysics(VarConst::densityAvatar, VarConst::bounceAvatar, 0);
    //polygon.create(box2d);
    polygon.FilterDataObjet.categoryBits = 0x0004;
    polygon.FilterDataObjet.maskBits = 0x0001 | 0x0008 | 0x0016 | 0x0032 | 0x0064;
    
    polygon.create(box2d, false);
    polygon.body->SetFixedRotation(true);
    
    polygon.setData(new dataSprite());
    dataSprite* data = (dataSprite*)polygon.getData();
    data->sprite = Sprite::BLOCK;
    data->physicalizedElement = this;
}