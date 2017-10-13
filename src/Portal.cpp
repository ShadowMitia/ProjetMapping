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
	    std::cout << "Intersects\n";
	    std::cout << objCenter.x << ' ' << portalCenter.x << '\n';
	    if ((left && verticalPortal && objCenter.x < portalCenter.x)
		|| (!left && verticalPortal && objCenter.x > portalCenter.x)
		|| (left && !verticalPortal && objCenter.y > portalCenter.y)
		|| (!left && !verticalPortal && objCenter.y < portalCenter.y)
		)
	      {
		obj->createClone(linkedPortal->collisionRect.getCenter() - portalCenter);
		obj->cloningPortal = this;
	      }
	  }
	else if (!intersects && cloned && obj->cloningPortal == this)
	  {
	    if ((left && verticalPortal && objCenter.x < obj->entryPoint.x)
		|| (!left && verticalPortal && objCenter.x > obj->entryPoint.x)
		|| (!left && !verticalPortal && objCenter.y < obj->entryPoint.y)
		|| (left && !verticalPortal && objCenter.y > obj->entryPoint.y))
	      {
		obj->removeClone();
		obj->cloningPortal = nullptr;
	      }
	    else
	      {
		obj->teleportToClone();
		obj->removeClone();
		obj->cloningPortal = nullptr;
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

void WorldPortal::linkTo(WorldPortal* portal)
  {
    linkedPortal = portal;
  }


/*
void Portal::update(std::vector<Teleportable*>& objects)
{
 // if (connectedPortal_Angle == nullptr || !activated) { return; }
    
    for (auto &obj : objects)
      {
		if (GetLinkedPortal(obj))
		{

			bool intersects = obj->collisionRect.intersects(rect);
			bool cloned = obj->hasClone();
			bool inside = obj->collisionRect.inside(rect);
			// std::cout << std::boolalpha << "Intersects " << intersects << ' '
			// 	  << std::boolalpha << "Cloned " << cloned << ' '
			// 	  << std::boolalpha << "Inside " << inside << '\n';

			if (intersects && !cloned)
			{
				std::cout << "Clone!\n";
				obj->createClone(GetLinkedPortal(obj)->rect.getCenter() - rect.getCenter());
			}

			// PAS FINI!
			if (intersects && !inside && obj->viewpoint != Viewpoint::MODE_PERSPECTIVE && cloned)
			{
				std::cout << "close portal\n";
				obj->removeClone();
			}

			if (!intersects && !inside && cloned && obj->collisionRect.intersects(entranceA, entranceB))
			{
				std::cout << "Remove clone\n";
				obj->removeClone();
			}
			else if (!intersects && !inside && cloned && obj->collisionRect.intersects(exitA, exitB))
			{
				std::cout << "Teleport to clone\n";
				obj->teleportToClone();
				obj->removeClone();
			}
		}
    }
}

void Portal::draw() {
    
    ofSetLineWidth(3);
    ofSetColor(ofColor::blue);
    ofDrawLine(entranceA, entranceB);
    ofSetLineWidth(3);
    ofSetColor(ofColor::red);
    ofDrawLine(exitA, exitB);
    
    ofPushMatrix();
    ofSetColor(ofColor::orange);
    ofDrawRectangle(rect);
    ofSetColor(ofColor::white);
    ofPopMatrix();
}

void Portal::linkTo(Portal* p_angle, Portal* p_perspective) 
{
  //if (connectedPortal != nullptr) { return; }

  connectedPortal_Angle = p_angle;
  connectedPortal_Perspective = p_perspective;

}

Portal* Portal::GetLinkedPortal(Teleportable* obj) const
{
  if (obj->viewpoint == Viewpoint::MODE_ANGLE)
    {
      return connectedPortal_Angle;
    }

  //return connectedPortal_Perspective != nullptr ? connectedPortal_Perspective : connectedPortal_Angle;
  return connectedPortal_Perspective;
}

*/
