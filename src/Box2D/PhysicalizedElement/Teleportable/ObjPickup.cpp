//
//  ObjPickup.cpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 09/02/2018.
//
//

#include "ObjPickup.h"
#include "WorldsBox2d.h"

/*
 Category bits:
 PLATFORM       : 0x0001
 PLATFORM-1     : 0x0002
 PLATFORM-2     : 0x0004
 PORTAL         : 0x0008
 LADDER         : 0x0010
 AVATAR         : 0x0020
 AVATAR-top     : 0x0040
 OBJ            : 0x0080
 OBJ-top        : 0x0100
 MUSHROOM-top   : 0x0200
 */

ObjPickup::ObjPickup(ObjPickupDef* _objPickupDef){
    
    
    sprite = static_cast<SpriteObj*>(_objPickupDef);
    _objPickupDef->pkup = this;
    deactive = new deActive(100000,this);
    
    std::vector<ofPoint> pts = loadPoints("ObjPickup.dat");
    polygon.addVertices(pts);
    //polygon.triangulatePoly();
    polygon.setPhysics(VarConst::densityAvatar, VarConst::bounceAvatar, 0);

    polygon.create(_objPickupDef->world->world.getWorld(), false);
    polygon.body->SetFixedRotation(true);
    
    teleportableFilter.categoryBits = _objPickupDef->categoryBits;
    setFilter(_objPickupDef->maskBits | Category::PLATFORM_1);
    
    polygon.setData(new dataSprite());
    dataSprite* data = (dataSprite*)polygon.getData();
    data->sprite = Sprite::PICKUP;
    data->physicalizedElement = this;
}

void ObjPickup::contactStart(ofxBox2dContactArgs e, b2Fixture *_fixture, dataSprite *OtherSprite){
    if (OtherSprite->sprite == Sprite::AVATAR) {
        deactive->startThread();
    }
}

void ObjPickup::contactEnd(ofxBox2dContactArgs e, b2Fixture *_fixture, dataSprite *OtherSprite){
    
}

void deActive::threadedFunction()
{
    pckup->setPosition(ofVec2f(0, 0));
    time.reset();
    time.waitNext();
    pckup->polygon.body->SetActive(false);
}