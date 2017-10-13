//
//  Portal.hpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 23/07/2017.
//
//
#pragma once
#include "ofMain.h"
#include "ofxBox2d.h"
#include "Avatar.h"
#include "PhysicalizedElement.h"
#include "Constant.h"

class Teleportable;

enum class Orientation { Horizontal, Vertical };
enum class PortalDirection { Left, Right };

class WorldPortal
{
public:

  int id; // pour debug seulement

  WorldPortal() = delete;
  WorldPortal(Orientation orientation, PortalDirection direction, int x, int y, int width, int height);
  WorldPortal(Orientation orientation, PortalDirection direction, ofRectangle portal);

  virtual void update(const std::vector<Teleportable*>& objects);
  virtual void draw() const;

  void linkTo(WorldPortal* portal);


  ofVec2f getPosition() const;


protected:
  ofRectangle collisionRect;
  Orientation orientation;
  PortalDirection direction;

  WorldPortal* linkedPortal;
};

class EmptyPortal : public WorldPortal
{
  void update(const std::vector<Teleportable*>& objects) override
  {
    return;
  }

  void draw() const override
  {
    ofSetColor(ofColor::dimGrey);
    ofDrawRectangle(collisionRect);
    ofSetColor(ofColor::red); // pour debug seulement
    ofDrawBitmapString(id, collisionRect.getCenter()); // pour debug seulement
    ofSetColor(ofColor::white);
  }
};


class PerspectivePortal : public WorldPortal
{
public:
  PerspectivePortal(Orientation orientation, PortalDirection direction, ofRectangle portal) : WorldPortal(orientation, direction, portal)
  {

  }

  void setActive(bool active)
  {
    activated = active;
  }

  void update(const std::vector<Teleportable*>& objects) override
  {
    if (!activated) return;
    WorldPortal::update(objects);
    for (auto& a : linked)
      {
	if (!collisionRect.inside(a->getCenter()))
	  {
	    linked.erase(std::find(linked.begin(), linked.end(), a));
	  }
      }
    if (linked.size() == 0) activated = false;
  }

  bool isActivated() const
  {
    return activated;
  }

  void draw() const override
  {
    ofSetColor(ofColor::green);
    if (linkedPortal == nullptr)
      {
	ofSetColor(ofColor::brown);
      }
    if (activated)
      {
	ofSetColor(ofColor::violet);
      }
    ofDrawRectangle(collisionRect);
    ofSetColor(ofColor::red); // pour debug seulement
    ofDrawBitmapString(id, collisionRect.getCenter()); // pour debug seulement
    ofSetColor(ofColor::white);
  }


  bool activated = false;

  std::vector<Avatar*> linked;



private:



};
