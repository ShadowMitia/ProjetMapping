//
//  Block.cpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 05/08/2017.
//
//

#include "ObjetBlock.h"


ObjectBlock::ObjectBlock(b2World* _box2d, ofPolyline _polyline)
  {
    box.setPhysics(3.0, 0.0, 0.0);
    
    box.addVertices(_polyline.getVertices());

    int width = 1000000;
    int height = 1000000;

    const auto& p = _polyline.getVertices();
    for (int i = 0; i < p.size(); i++)
      {
	if (p[i].x < width) { width = p[i].x; }

	if (p[i].y < height) { height = p[i].y; }
      }

    this->width = width;
    this->height = height;

    box.create(_box2d);
    box.body->SetFixedRotation(true);

    collisionRect.set(box.getPosition().x, box.getPosition().y, width, height);
    
    b2Filter tempFilter;
    tempFilter.categoryBits = 0x0001;
    tempFilter.maskBits = 0xFFFF;
    box.setFilterData(tempFilter);
    
    dataSprite* data = new dataSprite;
    data->setSprite(Sprite::BLOCK);
    data->Element = this;
    box.setData(data);
    
    this->box2d = _box2d;
  }

void ObjectBlock::update()
  {

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

    cloneTranslation = translateClone;

    ofPolyline p;
    
    for (int i = 0; i < box.getVertices().size(); i++)
      {
	p.addVertex(box.getVertices()[i].x + translateClone.x, box.getVertices()[i].y + translateClone.y, 0);
      }
    
    clone = std::make_unique<ObjectBlock>(box2d, p);
  }

void ObjectBlock::removeClone()
  {
    clone = nullptr;
    cloneTranslation.zero();
  }

void ObjectBlock::teleportToClone()
  {
    box.setPosition(clone->box.getPosition());
  }

bool ObjectBlock::hasClone()
  {
    return clone ? true : false;
  }

void ObjectBlock::contactStart(dataSprite* OtherSprite) {
  if (OtherSprite->getSprite() == Sprite::AVATAR)
    {
      pushed = true;
      if (static_cast<Avatar*>(OtherSprite->Element)->polygon.getPosition().x < box.getPosition().x)
	{
	  from = PUSHED_FROM::Left;
	}
      else if (static_cast<Avatar*>(OtherSprite->Element)->polygon.getPosition().x > box.getPosition().x)
	{
	  from = PUSHED_FROM::Right;
	}
      else if (static_cast<Avatar*>(OtherSprite->Element)->polygon.getPosition().y < box.getPosition().y)
	{
	  from = PUSHED_FROM::Top;
	}
      else if (static_cast<Avatar*>(OtherSprite->Element)->polygon.getPosition().y <= box.getPosition().y)
	{
	  from = PUSHED_FROM::Bottom;
	}
    }
  else if (OtherSprite->getSprite() == Sprite::BLOCK)
    {
      blocked = true;
    }
  else if (OtherSprite->getSprite() == Sprite::PLATFORM || OtherSprite->getSprite() == Sprite::BLOCK || OtherSprite->getSprite() == Sprite::AVATAR)
    {
      falling = false;
      box.setVelocity(0, 0);
      box.setDamping(0);
    }
}

void ObjectBlock::contactEnd(dataSprite* OtherSprite)
{


}

void ObjectBlock::PostSolve(dataSprite* OtherSprite, const b2ContactImpulse* impulse) {
    if (OtherSprite->getSprite() == Sprite::PLATFORM)
    {
      falling = true;
    }
}
