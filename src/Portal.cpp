//
//  Portal.cpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 23/07/2017.
//
//

#include "Portal.h"

void Portal::update(std::vector<Teleportable*>& objects)
{
  if (connectedPortal == nullptr /*|| !activated*/) { return; }
    
    for (auto &obj : objects)
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
            obj->createClone(connectedPortal->rect.getCenter() - rect.getCenter());
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

void Portal::linkTo(Portal* p) {

  if (connectedPortal != nullptr) { return; }

  connectedPortal = p;

  connectedPortal->connectedPortal = this;

  int portalDistance = 0;

  if (orientation == Orientation::HORIZONTAL)
    {
      portalDistance = rect.getPosition().x - connectedPortal->rect.getPosition().x;
    }
  else
    {
      portalDistance = rect.getPosition().y - connectedPortal->rect.getPosition().y;
    }

  if (portalDistance > 0)
    {
      std::swap(entranceA, exitA);
      std::swap(entranceB, exitB);
    }
  else if (portalDistance < 0)
    {
      std::swap(connectedPortal->entranceA, connectedPortal->exitA);
      std::swap(connectedPortal->entranceB, connectedPortal->exitB);
    }
}

