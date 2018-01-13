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
#include "PhysicalizedElement.h"

class PerspectivePortal;

class Avatar : public Teleportable {
public:

  Avatar(b2World* box2d);

  bool jumping;
  bool ClicJump;
  Deplacement modeDeplace;

  void processPerspectivePortals(std::vector<PerspectivePortal*>& portals);

    
private:
  std::unique_ptr<Avatar> clone;
  ofVec2f cloneTranslation;
  float moveInputX;
  float moveInputY;
  Viewpoint viewpoint = Viewpoint::MODE_ANGLE;

  void gravityCheck(ofRectangle gravityWell) ;

public:

  void presUpdate();
  void update(ofRectangle gravityWell) ;
  void draw() ;
  void createClone(ofVec2f cloneTranslation) ;
  void removeClone() ;
  void teleportToClone() ;
  bool hasClone() ;


  ofVec2f getFootPosition();

  void setPosition(ofVec2f vec);
  void setPosition(int x, int y);


  void jump();
  //void move(Direction _direction);
  void move(float inputX);
  void move(float inputX, float inputY);

  void keyPressed(int key);
  void keyReleased(int key);

  virtual void contactStart(b2Fixture* _fixture, dataSprite* OtherSprite) override;
  virtual void contactEnd(b2Fixture* _fixture, dataSprite* OtherSprite) override;
  virtual void PostSolve(dataSprite* OtherSprite, const b2ContactImpulse* impulse) override;

};
