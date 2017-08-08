//
//  Block.hpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 05/08/2017.
//
//

#ifndef Block_hpp
#define Block_hpp

#include "ofMain.h"
#include "ofxBox2d.h"

#include "Teleportable.h"


class Block : public Teleportable {

public:


  Block(ofxBox2d* box2d, int x, int y, int width, int height)
  {

    box.setPhysics(3.0, 0.53, 0.1);
    box.setup(box2d->getWorld(), x, y, width, height);
    collisionRect.set(box.getPosition().x, box.getPosition().y, box.getWidth(), box.getHeight());
    box.body->SetFixedRotation(true);

    this->box2d = box2d;

  }

  void update() override
  {
    collisionRect.set(box.getPosition().x, box.getPosition().y, box.getWidth(), box.getHeight());

    if (clone)
      {
	clone->box.setVelocity(box.getVelocity());
	clone->box.setPosition(box.getPosition() + cloneTranslation);
      }
  }

  void draw() override
  {
    box.draw();

    if (clone)
      {
	clone->draw();
      }
  }

  void createClone(ofVec2f translateClone) override
  {
    if (clone) { return; }

    this->cloneTranslation = translateClone;

    clone = std::make_unique<Block>(box2d, static_cast<int>(translateClone.x), static_cast<int>(translateClone.y), 100, 100);
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

  std::unique_ptr<Block> clone;

  ofxBox2d* box2d;

  ofVec2f cloneTranslation;

};

#endif /* Block_hpp */
