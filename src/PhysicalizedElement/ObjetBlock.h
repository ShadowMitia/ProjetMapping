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

  void update(ofRectangle gravityWell) override;
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
    return box.getPosition() - ofVec2f(width / 2, height / 2);
  }

  void setPosition(ofVec2f pos)
  {
    box.setPosition(pos.x + width / 2, pos.y + height / 2);
  }

  void setPosition(int x, int y)
  {
    box.setPosition(x + width / 2, y + height / 2);
  }
  
private:
  ofxBox2dPolygon box;

  void gravityCheck(ofRectangle gravityWell) override
  {
    if (gravityWell.inside(box.getPosition()))
      {
	box.body->SetGravityScale(0.0);
      }
    else
      {
	box.body->SetGravityScale(1.0);
      }
  }


  int width;
  int height;
  
  std::unique_ptr<ObjectBlock> clone;

  ofVec2f cloneTranslation;

  bool blocked = false;
  bool pushed = false;
  bool falling = false;

  enum class PUSHED_FROM { Left, Right, Top, Bottom, NONE };
  PUSHED_FROM from = PUSHED_FROM::NONE;
  
};
