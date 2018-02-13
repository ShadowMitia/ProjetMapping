//
//  ObjBlock.cpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 02/02/2018.
//
//
#include "ObjBlock.h"
#include "WorldsBox2d.h"
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

ObjBlock::ObjBlock(ObjBlockDef* _objBlockDef){
    
    sprite = static_cast<SpriteObj*>(_objBlockDef);
    _objBlockDef->b = this;
    std::vector<ofPoint> pts = loadPoints("avatar.dat");
    polygon.addVertices(pts);
    //polygon.triangulatePoly();
    polygon.setPhysics(VarConst::densityAvatar, VarConst::bounceAvatar, 0);
    //polygon.create(box2d);
    polygon.create(_objBlockDef->world->world.getWorld(), false);
    polygon.body->SetFixedRotation(true);
    
    _objBlockDef->setFilter();
    polygon.setData(new dataSprite());
    dataSprite* data = (dataSprite*)polygon.getData();
    data->sprite = Sprite::BLOCK;
    data->physicalizedElement = this;
}

void ObjBlock::draw(){
    ofSetColor(ofColor::navajoWhite);
    polygon.draw();
    ofSetColor(ofColor::white);
}

void ObjBlock::contactStart(ofxBox2dContactArgs e, b2Fixture *_fixture, dataSprite *OtherSprite){
    if (OtherSprite->sprite == Sprite::AVATAR) {
        polygon.body->SetLinearVelocity(_fixture->GetBody()->GetLinearVelocity());
    }
}
void ObjBlock::contactEnd(ofxBox2dContactArgs e, b2Fixture* _fixture, dataSprite* OtherSprite){
    if (OtherSprite->sprite == Sprite::AVATAR) {
        polygon.body->SetLinearVelocity(b2Vec2(0, 0));
    }
}