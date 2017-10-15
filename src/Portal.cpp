//
//  Portal.cpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 23/07/2017.
//
//

#include "Portal.h"
#include "Constant.h"
#include "Avatar.h"
#include "PhysicalizedElement/ObjetBlock.h"
#include "PhysicalizedElement/PickUp.h"
#include "PhysicalizedElement/Avatar.h"

WorldPortal::WorldPortal(Orientation orientation, PortalDirection direction, int x, int y, int width, int height) : WorldPortal(orientation, direction, ofRectangle(x, y, width, height))
  {

  }

WorldPortal::WorldPortal(Orientation orientation, PortalDirection direction, ofRectangle portal) : collisionRect(portal), orientation(orientation), direction(direction)
  {

    
    if (orientation == Orientation::Horizontal)
      {
	std::swap(collisionRect.width, collisionRect.height);
      }

    static int cur_id = 0;
    id = cur_id;
    ++cur_id;
  }

ofRectangle WorldPortal::getCollisionRect() const
{
  return collisionRect;
}


ofVec2f WorldPortal::getPosition() const
{
  return ofVec2f(collisionRect.x, collisionRect.y);
}

void WorldPortal::update(const std::vector<Teleportable*>& objects)
  {
    //if (linkedPortal == nullptr) return; // for debug, to be removed


    for (const auto &obj : objects)
      {
	if (dynamic_cast<ObjectBlock*>(obj))
	      {
		std::cout << "MMMh\n";
	      }
	else if (dynamic_cast<PickUp*>(obj))
	  {
	    std::cout << "pickup\n";
	  }
	else if (dynamic_cast<Avatar*>(obj))
	  {
	    // std::cout << "avatar\n";
	  }


	bool intersects = obj->collisionRect.intersects(collisionRect);
	bool cloned = obj->hasClone();
	bool verticalPortal = (orientation == Orientation::Vertical);
	bool left = (direction == PortalDirection::Left);
	ofVec2f const &objCenter = obj->collisionRect.getCenter();
	ofVec2f const &portalCenter = collisionRect.getCenter();

	if (intersects && !cloned)
	  {


	    if ((left && verticalPortal && objCenter.x < portalCenter.x)
		|| (!left && verticalPortal && objCenter.x > portalCenter.x)
		|| (left && !verticalPortal && objCenter.y > portalCenter.y)
		|| (!left && !verticalPortal && objCenter.y < portalCenter.y)
		)
	      {
		obj->createClone(linkedPortal->collisionRect.getCenter() - portalCenter);
		obj->cloningPortal.push_back(this);
	      }
	  }
	else if (!intersects && cloned && std::find(obj->cloningPortal.begin(), obj->cloningPortal.end(), this) != obj->cloningPortal.end())
	  {
	    if ((left && verticalPortal && objCenter.x < obj->entryPoint.x)
		|| (!left && verticalPortal && objCenter.x > obj->entryPoint.x)
		|| (left && !verticalPortal && objCenter.y > obj->entryPoint.y)
		|| (!left && !verticalPortal && objCenter.y < obj->entryPoint.y))
	      {
		obj->removeClone();
		obj->cloningPortal.erase(std::find(obj->cloningPortal.begin(), obj->cloningPortal.end(), this));
	      }
	    else
	      {
		obj->teleportToClone();
		obj->removeClone();
		obj->cloningPortal.erase(std::find(obj->cloningPortal.begin(), obj->cloningPortal.end(), this));
	      }
	  }
      }
  }

void WorldPortal::draw() const
{
    ofSetColor(ofColor::darkGreen);
    if (linkedPortal == nullptr)
      {
	ofSetColor(ofColor::orange);
      }
    ofDrawRectangle(collisionRect);
    ofSetColor(ofColor::red); // pour debug seulement
    ofDrawBitmapString(id, collisionRect.getCenter()); // pour debug seulement
    ofSetColor(ofColor::white);
  }

EmptyPortal::EmptyPortal(Orientation orientation, PortalDirection direction, int x, int y, int w, int h) : EmptyPortal(orientation, direction, ofRectangle(x, y, w, h))
  {

  }

EmptyPortal::EmptyPortal(Orientation orientation, PortalDirection direction, ofRectangle portal) : WorldPortal(orientation, direction, portal)
  {

  }

  void EmptyPortal::update(const std::vector<Teleportable*>& objects)
  {
    return;
  }

  void EmptyPortal::draw() const
  {
    ofSetColor(ofColor::dimGrey);
    ofDrawRectangle(collisionRect);
    ofSetColor(ofColor::red); // pour debug seulement
    ofDrawBitmapString(id, collisionRect.getCenter()); // pour debug seulement
    ofSetColor(ofColor::white);
  }


void WorldPortal::linkTo(WorldPortal* portal)
  {
    linkedPortal = portal;
  }

PerspectivePortal::PerspectivePortal(Orientation orientation, PortalDirection direction, int x, int y, int w, int h) : PerspectivePortal(orientation, direction, ofRectangle(x, y, w, h))
  {

  }


PerspectivePortal::PerspectivePortal(Orientation orientation, PortalDirection direction, ofRectangle portal) : WorldPortal(orientation, direction, portal)
{

}


void PerspectivePortal::setActive(bool active)
  {
    activated = active;
  }

void PerspectivePortal::update(const std::vector<Teleportable*>& objects)
  {
    if (!activated) return;

    std::cout << "Actif\n";

    for (auto& obj : objects)
      {
	if (dynamic_cast<Avatar*>(obj) != nullptr)
	  {
	    if (obj->perspectivePortal == this && collisionRect.intersects(obj->getCollisionRect()))
	      {
		obj->viewpoint = Viewpoint::MODE_ANGLE;
		obj->createClone(linkedPortal->getPosition());
		obj->teleportToClone();
	      }
	    else
	      {
		activated = false;
	      }
	  }
	else
	  {
	    if (obj->perspectivePortal == this &&  collisionRect.intersects(obj->getCollisionRect()))
	      {
		obj->createClone(linkedPortal->getPosition());
		obj->teleportToClone();
	      }
	  }
      }
  }

bool PerspectivePortal::isActivated() const
  {
    return activated;
  }

void PerspectivePortal::draw() const
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
