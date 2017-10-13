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

  void setActive(bool active = true)
  {
    activated = active;
  }

  void update(const std::vector<Teleportable*>& objects) override
  {
    if (!activated) return;
    WorldPortal::update(objects);
  }

  bool isActivated()
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

private:



};


/*
  class WorldPortal : public Portal
  {
  public:
  WorldPortal(ofRectangle portal, Orientation orientation) : Portal(portal, orientation)
  {

  }

  void update(const std::vector<Teleportable*>& objects) override
  {
  for (const auto &obj : objects)
  {
  bool intersects = obj->collisionRect.intersects(collisionRect);
  bool cloned = obj->hasClone();
  bool inside = obj->collisionRect.inside(collisionRect);
  // std::cout << std::boolalpha << "Intersects " << intersects << ' '
  // 	  << std::boolalpha << "Cloned " << cloned << ' '
  // 	  << std::boolalpha << "Inside " << inside << '\n';

  if (intersects && !cloned)
  {
  std::cout << "World Portal Clone!\n";
  obj->createClone(linkedPortal->collisionRect.getCenter() - collisionRect.getCenter());
  }

  if (!intersects && !inside && cloned && obj->collisionRect.intersects(entranceA, entranceB))
  {
  std::cout << "World Portal Remove clone\n";
  obj->removeClone();
  }
  else if (!intersects && !inside && cloned && obj->collisionRect.intersects(exitA, exitB))
  {
  std::cout << "World Portal Teleport to clone\n";
  obj->teleportToClone();
  obj->removeClone();
  }
  }
  }

  void draw() override
  {
  ofSetColor(ofColor::orange);
  ofDrawRectangle(collisionRect);

  ofSetColor(ofColor::blue);
  ofDrawLine(entranceA, entranceB);

  ofSetColor(ofColor::red);
  ofDrawLine(exitA, exitB);

  }


  };

  class PerspectivePortal : public Portal {
  public:

  enum class Direction { LEFT, RIGHT };

  Portal(Orientation _ori, Direction _direction, ofRectangle _rect){
  direction = _direction;
  orientation = _ori;
  rect = _rect;
  if (_ori == Orientation::VERTICAL){
  float temp = rect.getWidth();
  rect.setWidth(rect.getHeight());
  rect.setHeight(temp);
  entranceA = ofVec2f(rect.x - 2 , rect.y );
  entranceB = ofVec2f(rect.x - 2 , rect.y + rect.height );
  exitA = ofVec2f(rect.x + rect.width  + 2, rect.y);
  exitB = ofVec2f(rect.x + rect.width + 2, rect.y + rect.height);
  }
  else{
  entranceA = ofVec2f(rect.x , rect.y - 2);
  entranceB = ofVec2f(rect.x + rect.width , rect.y - 2);

  exitA = ofVec2f(rect.x , rect.y + rect.height + 2);
  exitB = ofVec2f(rect.x + rect.width , rect.y + rect.height + 2);
  }
  if (direction == Direction::LEFT) {
  std::swap(entranceA, exitA);
  std::swap(entranceB, exitB);
  }
  connectedPortal_Angle = nullptr;
  connectedPortal_Perspective = nullptr;
  }
    
  Portal(Orientation ori, Direction _direction, int x, int y, int width, int height)
  : Portal(ori, _direction, ofRectangle(x, y,height,width))
  {}
    
  void update(std::vector<Teleportable*> &objects) override;
  void draw() override;
  void linkTo(Portal* p_angle, Portal* p_perspective);
  Portal* GetLinkedPortal(Teleportable* obj) const;


  ofRectangle rect;
  int id;
    
  protected:
  Direction direction;
  Portal* connectedPortal_Angle;
  Portal* connectedPortal_Perspective;
  ofVec2f entranceA, entranceB;
  ofVec2f exitA, exitB;
    
  Orientation orientation;

  bool activated = false;
    
  };
*/
