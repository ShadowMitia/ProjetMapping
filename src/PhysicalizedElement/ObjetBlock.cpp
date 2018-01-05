//
//  Block.cpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 05/08/2017.
//
//

#include "ObjetBlock.h"


ObjectBlock::ObjectBlock(b2World* box2d, ofPolyline polyline)
{
    box.setPhysics(3.0, 0.0, 0.0);
    
    box.addVertices(polyline.getVertices());
    box.create(box2d);
    
    int width = 1000000;
    int height = 1000000;
    const auto& p = polyline.getVertices();
    for (int i = 0; i < p.size(); i++)
    {
        if (p[i].x < width) { width = p[i].x; }
        
        if (p[i].y < height) { height = p[i].y; }
    }
    this->width = width;
    this->height = height;
    
    box.body->SetType(b2BodyType::b2_dynamicBody);
    box.body->SetFixedRotation(true);
    
    collisionRect.set(box.getPosition().x - width / 2, box.getPosition().y - height / 2, width, height);
    
    b2Filter tempFilter;
    tempFilter.categoryBits = 0x0040;
    tempFilter.maskBits = 0xFFFF;
    box.setFilterData(tempFilter);
    
    box.setData(new dataSprite());
    dataSprite* data = (dataSprite*)box.getData();
    data->physicalizedElement = this;
    data->sprite = Sprite::BLOCK;
    
    box.body->SetGravityScale(0.0);
}

void ObjectBlock::update(ofRectangle gravityWell)
{
    
    gravityCheck(gravityWell);
    
    if (blocked)
    {
        return;
    }
    
    if (falling)
    {
        box.setVelocity(0, box.getVelocity().y);
    }
    
    collisionRect.set(box.getPosition().x - width / 2, box.getPosition().y - height / 2, width, height);
    
    if (clone)
    {
        clone->box.setVelocity(box.getVelocity());
        clone->box.setPosition(box.getPosition() + cloneTranslation);
    }
}

void ObjectBlock::draw()
{
    box.draw();
    
    //ofSetColor(ofColor::orange);
    //ofDrawRectangle(collisionRect);
    
    if (clone)
    {
        clone->draw();
    }
}

void ObjectBlock::createClone(ofVec2f translateClone)
{
    if (clone) { return; }
    std::cout << "Create object block clone\n";
    cloneTranslation = translateClone;
    
    ofPolyline p;
    
    for (int i = 0; i < box.getVertices().size(); i++)
    {
        p.addVertex(box.getVertices()[i].x, box.getVertices()[i].y, 0);
    }
    
    clone = std::make_unique<ObjectBlock>(box.getWorld(), p);
    clone->box.setPosition(cloneTranslation);
    clone->box.setVelocity(box.getVelocity());
    clone->box.create(box.getWorld());
    
    entryPoint = box.getPosition();
}

void ObjectBlock::removeClone()
{
    std::cout << "Remove object block clone\n";
    clone = nullptr;
    cloneTranslation.zero();
    entryPoint.zero();
}

void ObjectBlock::teleportToClone()
{
    std::cout << "Teleport object block clone\n";
    auto vel = box.getVelocity();
    box.setPosition(clone->box.getPosition());
    box.setVelocity(vel);
    cloneTranslation.zero();
}

bool ObjectBlock::hasClone()
{
    return clone ? true : false;
}

void ObjectBlock::contactStart(dataSprite* OtherSprite) {
    if (OtherSprite->sprite == Sprite::PLATFORM || OtherSprite->sprite == Sprite::BLOCK || OtherSprite->sprite == Sprite::AVATAR)
    {
        falling = false;
        box.setVelocity(0, 0);
        box.setDamping(0);
    }
}

void ObjectBlock::contactEnd(dataSprite* OtherSprite)
{
    if (OtherSprite->sprite == Sprite::PLATFORM || OtherSprite->sprite == Sprite::BLOCK || OtherSprite->sprite == Sprite::AVATAR)
    {
        box.setVelocity(0, 0);
        box.setDamping(0);
    }
}

void ObjectBlock::PostSolve(dataSprite* OtherSprite, const b2ContactImpulse* impulse) {
    if (OtherSprite->sprite == Sprite::PLATFORM)
    {
        falling = true;
    }
}
