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

  bool inside(ofVec2f pos)
  {
    return collisionRect.inside(pos);
  }

  ofRectangle getCollisionRect() const
  {
    return collisionRect;
  }


  ofVec2f getPosition() const;


protected:
  ofRectangle collisionRect;
  Orientation orientation;
  PortalDirection direction;

  WorldPortal* linkedPortal;
};

class EmptyPortal : public WorldPortal
{
public:
  EmptyPortal() = delete;
  EmptyPortal(Orientation orientation, PortalDirection direction, int x, int y, int w, int h) : EmptyPortal(orientation, direction, ofRectangle(x, y, w, h))
  {

  }
  EmptyPortal(Orientation orientation, PortalDirection direction, ofRectangle portal) : WorldPortal(orientation, direction, portal)
  {

  }

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
  PerspectivePortal() = delete;
  PerspectivePortal(Orientation orientation, PortalDirection direction, int x, int y, int h, int w) : PerspectivePortal(orientation, direction, ofRectangle(x, y, w, h))
  {

  }

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

    for (auto& obj : objects)
      {
	if ( dynamic_cast<Avatar*>(obj) != nullptr)
	  {
	    std::cout << "Avatar stuff\n";
	    auto pos = std::find(linked.begin(), linked.end(), obj);
	    if (pos != linked.end() && collisionRect.intersects(static_cast<Avatar*>(obj)->getCollisionRect()))
	      {
		obj->viewpoint = Viewpoint::MODE_ANGLE;
		obj->createClone(linkedPortal->getPosition());
		obj->teleportToClone();
		linked.erase(pos);
	      }
	    else
	      {
		activated = false;
	      }
	  }
	else
	  {
	    std::cout << "Other stuff\n";
	    //obj->createClone(linkedPortal->getPosition());
	    //obj->teleportToClone();
	  }
      }

    if (linked.size() == 0)
      {
	activated = false;
      }

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
