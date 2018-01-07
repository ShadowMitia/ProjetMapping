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

Portal::Portal(b2World* _box2d,ofRectangle _portal, WorldsBox2d * _worldsBox2d){
    box2d = _box2d;
    portalRect = _portal;
    linkedPortal[0] = nullptr;
    linkedPortal[1] = nullptr;
    worldsBox2d = _worldsBox2d;
    polygon.setPhysics(0.0, 0.0, 0.0);
    polygon.addVertex(-_portal.width/2,-_portal.height/2);
    polygon.addVertex(_portal.width/2, -_portal.height/2);
    polygon.addVertex(_portal.width/2, _portal.height/2);
    polygon.addVertex(-_portal.width/2,_portal.height/2);
    
    
    polygon.create(box2d);
    polygon.body->SetGravityScale(0.0);
    polygon.body->SetType(b2BodyType::b2_kinematicBody); // regardŽ a un peut plus prŽ
    
    b2Filter tempFilter;
    tempFilter.categoryBits = 0x0036;
    tempFilter.maskBits =  0x0001;
    polygon.setFilterData(tempFilter);
    
    polygon.setData(new dataSprite());
    dataSprite* data = (dataSprite*) polygon.getData();
    data->sprite = Sprite::PORTAL;
    data->physicalizedElement = this;
    
    polygon.setPosition(_portal.x + _portal.width/2 , _portal.y + _portal.height/2);
    polygon.body->GetFixtureList()->SetSensor(true);
}

void Portal::draw(){
    ofSetColor(ofColor::darkRed);
    polygon.draw();
}
b2World* Portal::getb2World(){
    return box2d;
}

void Portal::contactStart(dataSprite* OtherSprite){
    PhysicalizedElement::contactStart(OtherSprite);
    //cout << "contactStart" << endl;
    CloneBox2d *temp;
    temp  = new CloneBox2d(OtherSprite->physicalizedElement, this, nullptr);
    worldsBox2d->clones.push_back(temp);
    clones.push_back(temp);
}

void Portal::contactEnd(dataSprite* OtherSprite){
    PhysicalizedElement::contactEnd(OtherSprite);
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