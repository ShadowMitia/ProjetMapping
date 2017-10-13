//
//  Teleportable.h
//  ProjetMapping
//
//  Created by FatDazz_mac on 08/08/2017.
//
//
#pragma once

#include "ofMain.h"
#include "../Constant.h"
#include "PhysicalizedElement.h"

class PerspectivePortal;
class WorldPortal;

class Teleportable : public PhysicalizedElement {
public:
    virtual void update() = 0;
    virtual void draw() = 0;
    
    virtual void createClone(ofVec2f translationClone) = 0;
    virtual void removeClone() = 0;
    virtual void teleportToClone() = 0;
    virtual bool hasClone() = 0;

  ofVec2f getCenter() const;

  ofRectangle getCollisionRect() const;

  bool inside(ofVec2f pos) const;

  ofVec2f getPosition() const;
    
public:
  ofRectangle collisionRect;

  PerspectivePortal* perspectivePortal;

  Viewpoint viewpoint = Viewpoint::MODE_ANGLE;

  std::vector<WorldPortal*> cloningPortal;
  ofVec2f entryPoint;


};

