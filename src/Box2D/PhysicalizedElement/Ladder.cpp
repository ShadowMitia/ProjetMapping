//
//  Ladder.cpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 21/08/2017.
//
//

#include "Ladder.h"

void Ladder::create(b2World *_b2World, ofPolyline _groundLine){
    
    //ground.clear();
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
void Ladder::contactStart(ofxBox2dContactArgs e,b2Fixture* _fixture, dataSprite* OtherSprite){
    Avatar *objSource = static_cast<Avatar*>(OtherSprite->physicalizedElement);
    objSource->SetGravityScale(.0f);
    objSource->setMove(Deplacement::TOP);
}
void Ladder::contactEnd(ofxBox2dContactArgs e,b2Fixture* _fixture, dataSprite* OtherSprite){
    Avatar *objSource = static_cast<Avatar*>(OtherSprite->physicalizedElement);
    objSource->SetGravityScale(1.0f);
    objSource->setMove(Deplacement::PLATFORM);
}