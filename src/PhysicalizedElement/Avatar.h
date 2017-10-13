//
//  Avatar.hpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 22/07/2017.
//
//
#pragma once

#include "ofMain.h"
#include "ofxBox2d.h"
#include "Teleportable.h"
#include "ofxGLFWJoystick.h"
#include "ObjetBlock.h"
#include "PhysicalizedElement.h"

class PerspectivePortal;

class Avatar : public Teleportable {

public:

  Avatar(b2World* box2d);

  ofxBox2dPolygon polygon;
  ofxBox2dRect    foot;

  ofRectangle rect;
  bool jumping;
  bool ClicJump;
  Deplacement modeDeplace;

    
private:
  std::unique_ptr<Avatar> clone;
  ofVec2f cloneTranslation;
  float moveInputX;
  float moveInputY;
  //std::vector<bool>  pickupAvatar;
  Viewpoint viewpoint = Viewpoint::MODE_ANGLE;

public:

  void presUpdate();
  void update() override;
  void draw() override;
  void createClone(ofVec2f cloneTranslation) override;
  void removeClone() override;
  void teleportToClone() override;
  bool hasClone() override;

  void processPerspectivePortals(std::vector<PerspectivePortal*>& portals);


  ofVec2f getPosition() const
  {
    return ofVec2f(rect.x, rect.y);
  }

  ofVec2f getFootPosition()
  {
    return foot.getPosition();
  }


  ofVec2f getCenter() const
  {
    return collisionRect.getCenter();
  }


  ofRectangle getCollisionRect() const
  {
    return collisionRect;
  }

  void setPosition(ofVec2f vec);
  void setPosition(int x, int y);


  void jump();
  //void move(Direction _direction);
  void move(float inputX);
  void move(float inputX, float inputY);

  void keyPressed(int key);
  void keyReleased(int key);

  virtual void contactStart(dataSprite* OtherSprite) override;
  virtual void contactEnd(dataSprite* OtherSprite) override;
  virtual void PostSolve(dataSprite* OtherSprite, const b2ContactImpulse* impulse) override;

};
