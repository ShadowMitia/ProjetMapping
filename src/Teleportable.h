#ifndef TELEPORTABLE_H
#define TELEPORTABLE_H

#include "ofMain.h"

class Teleportable {


public:
  virtual void update() = 0;
  virtual void draw() = 0;

  virtual void createClone(ofVec2f translationClone) = 0;
  virtual void removeClone() = 0;
  virtual void teleportToClone() = 0;
  virtual bool hasClone() = 0;

public:
  ofRectangle collisionRect;
};

#endif
