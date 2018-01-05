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
#include "Clone.h"

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

class Portal:public PhysicalizedElement{
public:
    Portal(b2World* box2d,ofRectangle _portal){
        
        polygon.setPhysics(0.0, 0.0, 0.0);
        polygon.addVertex(-10,-10);
        polygon.addVertex(10, -10);
        polygon.addVertex(10, 10);
        polygon.addVertex(-10,10);

        
        polygon.create(box2d);
        polygon.body->SetGravityScale(0.0);
        polygon.body->SetType(b2BodyType::b2_dynamicBody);

        b2Filter tempFilter;
        tempFilter.categoryBits = 0x0036;
        tempFilter.maskBits =  0x0001;
        polygon.setFilterData(tempFilter);
        
        polygon.setData(new dataSprite());
        dataSprite* data = (dataSprite*) polygon.getData();
        data->sprite = Sprite::PORTAL;
        data->physicalizedElement = this;
        data->teleportable = nullptr;
        
        polygon.setPosition(_portal.getX()+ _portal.width/2 + 20, _portal.getY()+_portal.height/2);
        polygon.body->GetFixtureList()->SetSensor(true);
        cout << polygon.body->GetFixtureList()->IsSensor() << endl;
        
    }
    
    void draw(){
        ofSetColor(ofColor::darkRed);
        polygon.draw();
    }
    
    void contactStart(dataSprite* OtherSprite){
        //PhysicalizedElement::contactStart(OtherSprite);
        cout << "contactStart" << endl;
        //new CloneBox2d(OtherSprite->teleportable);
    }
    void contactEnd(dataSprite* OtherSprite){
        //PhysicalizedElement::contactEnd(OtherSprite);
        cout << " contactEnd " << endl;
    }
private:
    Portal *linkedPortal[2];
    ofxBox2dPolygon polygon;
    
};

