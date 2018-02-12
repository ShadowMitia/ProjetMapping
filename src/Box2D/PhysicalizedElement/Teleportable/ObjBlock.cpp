//
//  ObjBlock.cpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 02/02/2018.
//
//
#include "ObjBlock.h"

ObjBlock::ObjBlock(b2World* box2d){
    
    std::vector<ofPoint> pts = loadPoints("avatar.dat");
    polygon.addVertices(pts);
    //polygon.triangulatePoly();
    polygon.setPhysics(VarConst::densityAvatar, VarConst::bounceAvatar, 0);
    //polygon.create(box2d);
    polygon.FilterDataObjet.categoryBits = 0x0008;
    polygon.FilterDataObjet.maskBits = 0x0001 | 0x0016 | 0x0032 | 0x0008 |0x0064 ;
    
    polygon.create(box2d, false);
    polygon.body->SetFixedRotation(true);
    
    polygon.setData(new dataSprite());
    dataSprite* data = (dataSprite*)polygon.getData();
    data->sprite = Sprite::BLOCK;
    data->physicalizedElement = this;
}

void ObjBlock::setPosition(float x, float y){
    polygon.setPosition(x, y);
}

void ObjBlock::draw(){
    ofSetColor(ofColor::black);
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