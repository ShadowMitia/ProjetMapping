//
//  Block.hpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 05/08/2017.
//
//
#pragma once

#include "ofMain.h"
#include "ofxBox2d.h"
#include "Teleportable.h"
#include "../Constant.h"
#include "PhysicalizedElement.h"

class ObjetBlock : public Teleportable {

public:


  ObjetBlock(ofxBox2d* _box2d, int x, int y, int width, int height)
  {
    box.setPhysics(3.0, 0.53, 0.1);
    box.setup(box2d->getWorld(), x, y, width, height);
    collisionRect.set(box.getPosition().x, box.getPosition().y, box.getWidth(), box.getHeight());
    box.body->SetFixedRotation(true);
    dataSprite* data = new dataSprite;
    data->setSprite(Sprite::BLOCK);
    box.setData(data);
    this->box2d = _box2d;
  }

  void update() override
  {

    collisionRect.set(box.getPosition().x - box.getWidth() / 2, box.getPosition().y - box.getHeight() / 2, box.getWidth(), box.getHeight());

    if (clone)
      {
	clone->box.setVelocity(box.getVelocity());
	clone->box.setPosition(box.getPosition() + cloneTranslation);
      }
  }

  void draw() override
  {
    box.draw();

    //ofSetColor(ofColor::orange);
    //ofDrawRectangle(collisionRect);

    if (clone)
      {
	clone->draw();
      }
  }

  void createClone(ofVec2f translateClone) override
  {
    if (clone) { return; }

    this->cloneTranslation = translateClone;

    clone = std::make_unique<ObjetBlock>(box2d, static_cast<int>(translateClone.x), static_cast<int>(translateClone.y), 100, 100);
  }

  void removeClone() override
  {
    clone = nullptr;
    cloneTranslation.zero();
  }

  void teleportToClone() override
  {
    box.setPosition(clone->box.getPosition());

  }

  bool hasClone() override
  {
    return clone ? true : false;
  }


private:
  ofxBox2dRect box;

  std::unique_ptr<ObjetBlock> clone;

  ofxBox2d* box2d;

  ofVec2f cloneTranslation;

};

