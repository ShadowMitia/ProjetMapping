//
//  PickUp.cpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 29/09/2017.
//
//

#include "PickUp.h"

PickUp::PickUp(b2World* box2d, ofPolyline polyline)
{

  pickUp.addVertices(polyline.getVertices());

    pickUp.setPhysics(3.0, 0.0, 10.0);
    pickUp.create(box2d);

    pickUp.body->SetType(b2BodyType::b2_dynamicBody);
    pickUp.body->SetFixedRotation(true);

    width = 1000000;
    height = 1000000;
    
    const auto& p = polyline.getVertices();
    for (int i = 0; i < p.size(); i++)
    {
        if (p[i].x < width) { width = p[i].x; }
        
        if (p[i].y < height) { height = p[i].y; }
    }

    collisionRect.set(pickUp.getPosition().x, pickUp.getPosition().y, width, height);
    
    b2Filter tempFilter;
    tempFilter.categoryBits = 0x0010;
    tempFilter.maskBits = 0xFFFF;
    pickUp.setFilterData(tempFilter);

    pickUp.setData(new dataSprite);
    dataSprite* data = (dataSprite*)pickUp.getData();
    data->sprite = Sprite::PICKUP;
    data->physicalizedElement = this;

    pickUp.body->SetGravityScale(0.0);
}

void PickUp::update(ofRectangle gravityWell)
{


  gravityCheck(gravityWell);
  collisionRect.set(pickUp.getPosition().x - collisionRect.width / 2, pickUp.getPosition().y - height / 2, width, height);
    
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
    
    if (clone)
    {
        clone->draw();
    }
}

void PickUp::createClone(ofVec2f translateClone)
{
    if (clone) { return; }

    std::cout << "Create pickup clone\n";

    cloneTranslation = translateClone;
    
    ofPolyline p;
    
    for (int i = 0; i < pickUp.getVertices().size(); i++)
    {
      p.addVertex(pickUp.getVertices()[i].x, pickUp.getVertices()[i].y, 0);
    }
    
    clone = std::make_unique<PickUp>(pickUp.getWorld(), p);
    clone->setPosition(translateClone.x, translateClone.y);

    clone->pickUp.setVelocity(pickUp.getVelocity());
    clone->pickUp.create(pickUp.getWorld());

    entryPoint = pickUp.getPosition();
}

void PickUp::removeClone()
{

  std::cout << "Remove pickup clone\n";

    clone = nullptr;
    cloneTranslation.zero();
    entryPoint.zero();
}

void PickUp::teleportToClone()
{
  std::cout << "Teleport pickup\n";
  auto vel = pickUp.getVelocity();
  pickUp.setPosition(clone->pickUp.getPosition());
  pickUp.setVelocity(vel);
  cloneTranslation.zero();
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
