//
//  Portal.cpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 23/07/2017.
//
//

#include "Portal.h"

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

void WorldPortal::update(const std::vector<Teleportable*>& objects)
  {
    if (linkedPortal == nullptr) return; // for debug, to be removed

    for (const auto &obj : objects)
      {
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

ofVec2f WorldPortal::getPosition() const
  {
    return ofVec2f(collisionRect.x, collisionRect.y);
  }

void WorldPortal::linkTo(WorldPortal* portal)
  {
    linkedPortal = portal;
  }
