//
//  PickUp.cpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 29/09/2017.
//
//

#include "PickUp.h"

PickUp::PickUp(b2World* _box2d, ofPolyline _polyline)
{
    pickUp.setPhysics(3.0, 0.0, 10.0);
    
    pickUp.addVertices(_polyline.getVertices());
    
    int width = 1000000;
    int height = 1000000;
    
    const auto& p = _polyline.getVertices();
    for (int i = 0; i < p.size(); i++)
    {
        if (p[i].x < width) { width = p[i].x; }
        
        if (p[i].y < height) { height = p[i].y; }
    }

    collisionRect.width = width;
    collisionRect.height = height;

    auto pos = pickUp.getPosition();
    collisionRect.x = pos.x;
    collisionRect.y = pos.y;

    pickUp.create(_box2d);


    pickUp.body->SetFixedRotation(true);

    collisionRect.set(pickUp.getPosition().x, pickUp.getPosition().y, collisionRect.width, collisionRect.height);
    
    b2Filter tempFilter;
    tempFilter.categoryBits = 0x0001;
    tempFilter.maskBits = 0xFFFF;
    pickUp.setFilterData(tempFilter);

    pickUp.setData(new dataSprite);
    dataSprite* data = (dataSprite*)pickUp.getData();
    data->sprite = Sprite::PICKUP;
    data->Element = this;

    
    this->box2d = _box2d;
}

void PickUp::update()
{
    
  //collisionRect.set(pickUp.getPosition().x - collisionRect.width / 2, pickUp.getPosition().y - height / 2, width, height);
    
    if (clone)
    {
        clone->pickUp.setVelocity(pickUp.getVelocity());
        clone->pickUp.setPosition(pickUp.getPosition() + cloneTranslation);
    }
}

void PickUp::draw()
{
  ofSetColor(ofColor::green);
  pickUp.draw();
    
    //ofSetColor(ofColor::orange);
    //ofDrawCollisionRect(collisionRect);
    
    if (clone)
    {
        clone->draw();
    }
}

void PickUp::createClone(ofVec2f translateClone)
{
    if (clone) { return; }
    
    cloneTranslation = translateClone;
    
    ofPolyline p;
    
    for (int i = 0; i < pickUp.getVertices().size(); i++)
    {
        p.addVertex(pickUp.getVertices()[i].x + translateClone.x, pickUp.getVertices()[i].y + translateClone.y, 0);
    }
    
    clone = std::make_unique<PickUp>(box2d, p);
}

void PickUp::removeClone()
{
    clone = nullptr;
    cloneTranslation.zero();
}

void PickUp::teleportToClone()
{
    pickUp.setPosition(clone->pickUp.getPosition());
}

bool PickUp::hasClone()
{
    return clone ? true : false;
}

void PickUp::contactStart(dataSprite* OtherSprite)
{
  PhysicalizedElement::contactStart(OtherSprite);
}

void PickUp::contactEnd(dataSprite* OtherSprite)
{
  PhysicalizedElement::contactEnd(OtherSprite);
    
}

void PickUp::PostSolve(dataSprite* OtherSprite, const b2ContactImpulse* impulse)
{
  PhysicalizedElement::PostSolve(OtherSprite, impulse);
}
