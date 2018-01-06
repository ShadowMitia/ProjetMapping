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
    worldsBox2d = _worldsBox2d;
    polygon.setPhysics(0.0, 0.0, 0.0);
    polygon.addVertex(-10,-10);
    polygon.addVertex(10, -10);
    polygon.addVertex(10, 10);
    polygon.addVertex(-10,10);
    
    
    polygon.create(box2d);
    polygon.body->SetGravityScale(0.0);
    polygon.body->SetType(b2BodyType::b2_dynamicBody);
    
    b2Filter tempFilter;
    tempFilter.categoryBits = 0x0036;
    tempFilter.maskBits =  0x0001;
    polygon.setFilterData(tempFilter);
    
    polygon.setData(new dataSprite());
    dataSprite* data = (dataSprite*) polygon.getData();
    data->sprite = Sprite::PORTAL;
    data->physicalizedElement = this;
    
    polygon.setPosition(_portal.getX()+ _portal.width/2 + 20, _portal.getY()+_portal.height/2);
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
    cout << "contactStart" << endl;
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
    cout << " contactEnd " << endl;
}
