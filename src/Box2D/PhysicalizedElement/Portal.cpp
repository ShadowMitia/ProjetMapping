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

bool leftCondition(float _x ,CloneBox2d* _clone){
    //cout << " leftCondition " << endl;
    if (_x > _clone->portalSource->getPosition().x) return true;
    else return false;
}

bool rightCondition(float _x ,CloneBox2d* _clone){
    //cout << " rightCondition " << endl;
    if (_x < _clone->portalSource->getPosition().x) return true;
    else return false;
}

ofVec2f leftDirection(CloneBox2d* _clone){
    return _clone->objSource->getPosition() - _clone->portalSource->getPosition() + _clone->portalDestination->getPosition();
}

ofVec2f rightDirection(CloneBox2d* _clone){
    return _clone->objSource->getPosition() - _clone->portalSource->getPosition() + _clone->portalDestination->getPosition() - ofVec2f(_clone->portalDestination->portalRect.width, 0);
}

Portal::Portal(ofRectangle _portal, WorldsBox2d * _worldsBox2d,PortalDirection _direction,ConditionOutput _output){
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
    polygon.body->SetType(b2BodyType::b2_staticBody); // regard� �a un peut plus pr�
    
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
        case ConditionOutput::VerticalLeft: conditionFunction = leftCondition; break;
        case ConditionOutput::VerticalRight: conditionFunction = rightCondition; break;
    }
    switch (_direction) {
        case PortalDirection::leftDirection : directionFunction = leftDirection; break;
        case PortalDirection::rightDirection : directionFunction = rightDirection; break;
    }
    
}
void Portal::draw(){
    ofSetColor(ofColor::darkRed);
    polygon.draw();
}
b2World* Portal::getb2World(){
    return worldsBox2d->world.getWorld();
}
void Portal::contactStart(b2Fixture* _fixture, dataSprite* OtherSprite){
    PhysicalizedElement::contactStart(_fixture, OtherSprite);
    //cout << "contactStart" << endl;
    CloneBox2d *temp;
    temp  = new CloneBox2d(OtherSprite->physicalizedElement, this, nullptr);
    worldsBox2d->clones.push_back(temp);
    clones.push_back(temp);
}
void Portal::contactEnd(b2Fixture* _fixture, dataSprite* OtherSprite){
    PhysicalizedElement::contactEnd(_fixture, OtherSprite);
    for (int i = 0; i < clones.size(); ++i) {
        Teleportable *objSource = static_cast<Teleportable*>(OtherSprite->physicalizedElement);
        if (clones[i]->objSource == objSource) {
            clones[i]->statut++;
            clones.erase(clones.begin()+i);
            i = clones.size();
        }
    }
    //cout << " contactEnd " << endl;
}
void Portal::linke(Portal *_1, Portal *_2){
    linkedPortal[0] = _1;
    linkedPortal[1] = _2;
}
ofVec2f Portal::getPosition(){
    return portalRect.getPosition();
}