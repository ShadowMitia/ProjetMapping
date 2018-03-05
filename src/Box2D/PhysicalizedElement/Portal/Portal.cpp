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

Portal::Portal(ofRectangle _portal, WorldsBox2d * _worldsBox2d,Deplacement _direction,ConditionOutput _output, Face* _face){
    face = _face;
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
    tempFilter.categoryBits = Category::PORTAL;
    tempFilter.maskBits = Category::AVATAR |  Category::OBJ;
    polygon.setFilterData(tempFilter);
    
    polygon.setData(new dataSprite());
    dataSprite* data = (dataSprite*) polygon.getData();
    data->sprite = Sprite::PORTAL;
    data->physicalizedElement = this;
    polygon.setPosition(_portal.getCenter());
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
            nullFunction = topNull;
            break;
        case ConditionOutput::HorizontalDown: conditionFunction = downCondition;
            orient = ofVec2f(0, -1);
            getObjPosition = &Portal::getObjPositionLeft;
            nullFunction = downNull;
            break;
            
        case ConditionOutput::CornerDownLeft: conditionFunction = nonCondition;
            orient = ofVec2f(-1, 0);
            getObjPosition = &Portal::getObjPositionLeft;
            nullFunction = NoNull;
            break;
            
        case ConditionOutput::CornerTopRight: conditionFunction = nonCondition;
            orient = ofVec2f(1, 0);
            getObjPosition = &Portal::getObjPositionLeft;
            nullFunction = NoNull;
            break;
        case ConditionOutput::CornerDownRight: conditionFunction = nonCondition;
            orient = ofVec2f(0, -1);
            getObjPosition = &Portal::getObjPositionLeft;
            nullFunction = NoNull;
            break;
            
        case ConditionOutput::CornerTopLeft: conditionFunction = nonCondition;
            orient = ofVec2f(0, 1);
            getObjPosition = &Portal::getObjPositionLeft;
            nullFunction = NoNull;
            break;
    }
    direct = _direction;
}
void Portal::draw(){
    ofSetColor(ofColor::darkSlateBlue);
    polygon.draw();
}
b2World* Portal::getb2World(){
    return worldsBox2d->world.getWorld();
}
void Portal::contactStart(ofxBox2dContactArgs e, b2Fixture* _fixture, dataSprite* OtherSprite){
    //PhysicalizedElement::contactStart(_fixture, OtherSprite);
    CloneBox2d *temp;
    Teleportable *objSource = static_cast<Teleportable*>(OtherSprite->physicalizedElement);

    temp  = new CloneBox2d(objSource, this, nullptr);
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
