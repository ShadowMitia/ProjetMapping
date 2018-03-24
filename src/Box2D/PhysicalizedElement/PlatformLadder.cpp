//
//  PlatformLadder.cpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 28/01/2018.
//
//

#include "PlatformLadder.h"

void PlatformLadder::create(b2World* _b2World, ofPolyline _groundLine){
    
    polygon.addVertexes(_groundLine);
    polygon.setPhysics(0, 0, 0.5f); // (0.0, 0.1, 0.7)
    polygon.create(_b2World);
    
    polygon.setData(new dataSprite());
    dataSprite* data = (dataSprite*)polygon.getData();
    data->sprite = Sprite::LADDER;
    data->physicalizedElement = this;
    
    b2Filter tempFilter;
    tempFilter.categoryBits = 0x0128;
    tempFilter.maskBits = 0x0001;
    polygon.setFilterData(tempFilter);
    polygon.body->GetFixtureList()->SetSensor(true);
    
}


void PlatformLadder::contactStart(ofxBox2dContactArgs e,b2Fixture* _fixture, dataSprite* OtherSprite){
    Avatar *objSource = static_cast<Avatar*>(OtherSprite->physicalizedElement);
    if (abs(e.contact->GetManifold()->localPoint.x) != 0.2f && abs(e.contact->GetManifold()->localPoint.y) != 0.2f) {
        if (e.contact->GetManifold()->localNormal.y < 0.f) {
            objSource->SetGravityScale(.0f);
            objSource->setMove(Deplacement::PLATFORMLADDER);
        }
    }
}

void PlatformLadder::contactEnd(ofxBox2dContactArgs e,b2Fixture* _fixture, dataSprite* OtherSprite){
    Avatar *objSource = static_cast<Avatar*>(OtherSprite->physicalizedElement);
    objSource->SetGravityScale(1.0f);
    objSource->setMove(Deplacement::PLATFORM);
}

