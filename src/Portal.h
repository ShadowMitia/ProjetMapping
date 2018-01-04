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
#include "PhysicalizedElement/Teleportable.h"

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

  ofRectangle getCollisionRect() const;

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
  EmptyPortal(Orientation orientation, PortalDirection direction, int x, int y, int w, int h);
  EmptyPortal(Orientation orientation, PortalDirection direction, ofRectangle portal);

  void update(const std::vector<Teleportable*>& objects) override;

  void draw() const override;
};


class PerspectivePortal : public WorldPortal
{
public:
  PerspectivePortal() = delete;
  PerspectivePortal(Orientation orientation, PortalDirection direction, int x, int y, int h, int w);
  PerspectivePortal(Orientation orientation, PortalDirection direction, ofRectangle portal);

  void setActive(bool active);

  void update(const std::vector<Teleportable*>& objects) override;

  bool isActivated() const;

  void draw() const override;


  bool activated = false;

private:



};

class Portal{
    
};
