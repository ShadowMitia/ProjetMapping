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
 // if (connectedPortal_Angle == nullptr /*|| !activated*/) { return; }
    
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
	return connectedPortal_Perspective;
}

