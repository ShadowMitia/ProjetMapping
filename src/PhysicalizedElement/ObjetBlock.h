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
#include "Avatar.h"

class ObjectBlock : public Teleportable {

public:


  ObjectBlock(b2World* _box2d, ofPolyline _polyline);

  void update() override;
  void draw() override;

  void createClone(ofVec2f translateClone) override;
  void removeClone() override;
  void teleportToClone() override;
  bool hasClone() override;

  void contactStart(dataSprite* OtherSprite) override;
  void contactEnd(dataSprite* OtherSprite) override;
  void PostSolve(dataSprite* OtherSprite, const b2ContactImpulse* impulse) override;

  ofVec2f getPosition()
  {
    return box.getPosition();
  }

  void setPosition(int x, int y)
  {
    box.setPosition(x, y);
  }
  
private:
  ofxBox2dPolygon box;

  int width;
  int height;
  
  std::unique_ptr<ObjectBlock> clone;

  b2World* box2d;

  ofVec2f cloneTranslation;

  bool blocked = false;
  bool pushed = false;
  bool falling = false;

  enum class PUSHED_FROM { Left, Right, Top, Bottom, NONE };
  PUSHED_FROM from = PUSHED_FROM::NONE;
  
};
