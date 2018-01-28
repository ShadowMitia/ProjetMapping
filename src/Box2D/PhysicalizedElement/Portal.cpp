//
//  Portal.cpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 23/07/2017.
//
//

#include "Portal.h"
#include "Constant.h"
#include "WorldsBox2d.h"
#include "ConditionOutput.h"
#include "ConditionNull.h"

Portal::Portal(ofRectangle _portal, WorldsBox2d * _worldsBox2d,Deplacement _direction,ConditionOutput _output){
    portalRect = _portal;
    linkedPortal[0] = nullptr;
    linkedPortal[1] = nullptr;
    worldsBox2d = _worldsBox2d;
    polygon.setPhysics(0.0, 0.0, 0.0);
    polygon.addVertex(-_portal.width/2,-_portal.height/2);
    polygon.addVertex(_portal.width/2, -_portal.height/2);
    polygon.addVertex(_portal.width/2, _portal.height/2);
    polygon.addVertex(-_portal.width/2,_portal.height/2);
    
    
    polygon.create(worldsBox2d->world.getWorld());
    polygon.body->SetType(b2BodyType::b2_staticBody); // regardŽ a un peut plus prŽ
    
    b2Filter tempFilter;
    tempFilter.categoryBits = 0x0032;
    tempFilter.maskBits =  0x0001;
    polygon.setFilterData(tempFilter);
    
    polygon.setData(new dataSprite());
    dataSprite* data = (dataSprite*) polygon.getData();
    data->sprite = Sprite::PORTAL;
    data->physicalizedElement = this;
    
    polygon.setPosition(_portal.x + _portal.width/2 , _portal.y + _portal.height/2);
    polygon.body->GetFixtureList()->SetSensor(true);
    
    switch(_output){
        case ConditionOutput::VerticalLeft: conditionFunction = leftCondition;
            orient = ofVec2f(1, 0);
            getObjPosition = &Portal::getObjPositionLeft;
            nullFunction = leftNull;
            break;
        case ConditionOutput::VerticalRight: conditionFunction = rightCondition;
            orient = ofVec2f(-1, 0);
            nullFunction = rightNull;
            getObjPosition = &Portal::getObjPositionRight;
            break;
        case ConditionOutput::HorizontalTop: conditionFunction = topCondition;
            orient = ofVec2f(0, 1);
            getObjPosition = &Portal::getObjPositionLeft;
            nullFunction = rightNull;// a faire
            break;
        case ConditionOutput::HorizontalDown: conditionFunction = downCondition;
            orient = ofVec2f(0, -1);
            getObjPosition = &Portal::getObjPositionLeft;
            nullFunction = rightNull; // a faire
            break;
    }
    direct = _direction;
}
void Portal::draw(){
    ofSetColor(ofColor::darkRed);
    polygon.draw();
}
b2World* Portal::getb2World(){
    return worldsBox2d->world.getWorld();
}
void Portal::contactStart(ofxBox2dContactArgs e, b2Fixture* _fixture, dataSprite* OtherSprite){
    //PhysicalizedElement::contactStart(_fixture, OtherSprite);
    //cout << "contactStart" << endl;
    CloneBox2d *temp;
    temp  = new CloneBox2d(OtherSprite->physicalizedElement, this, nullptr);
    worldsBox2d->clones.push_back(temp);
    clones.push_back(temp);
}
void Portal::contactEnd(ofxBox2dContactArgs e,b2Fixture* _fixture, dataSprite* OtherSprite){
    //PhysicalizedElement::contactEnd(_fixture, OtherSprite);
    for (int i = 0; i < clones.size(); ++i) {
        Teleportable *objSource = static_cast<Teleportable*>(OtherSprite->physicalizedElement);
        if (clones[i]->objSource == objSource) {
            clones[i]->statut++;
            clones.erase(clones.begin()+i);
            i = clones.size();
        }
    }
}
void Portal::linke(Portal *_1, Portal *_2){
    linkedPortal[0] = _1;
    linkedPortal[1] = _2;
}
ofVec2f Portal::getPosition(){
    return portalRect.getCenter();
}
