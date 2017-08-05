//
//  Portal.cpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 23/07/2017.
//
//

#include "Portal.h"

void Portal::update(std::vector<Avatar> & objects) {
    
    for (auto &obj : objects){
        
        bool intersects = obj.rect.intersects(rect);
        bool cloned = obj.hasClone();
        bool inside = obj.rect.inside(rect);
        
        if (intersects && !cloned) {
	  //std::cout << "Clone\n";
            obj.createClone(connectedPortal->rect.getCenter() - rect.getCenter());
        }
        
        if (!intersects && !inside && cloned && obj.rect.intersects(entranceA, entranceB)) {
	  //std::cout << "Back\n";
            obj.removeClone();
        }
        else if (!intersects && !inside && cloned && obj.rect.intersects(exitA, exitB)) {
	  //std::cout << "Exit\n";
            obj.teleportToClone();
            obj.removeClone();
        }
    }

}

void Portal::draw() {
    
    ofSetColor(ofColor::blue);
    ofDrawLine(entranceA, entranceB);
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

  long first, second;

  if (orientation == Orientation::HORIZONTAL) {
    first = rect.getPosition().x;
    second = connectedPortal->rect.getPosition().x;
  }
  else {
    first = rect.getPosition().y;
    second = connectedPortal->rect.getPosition().y;
  }

  if (first > second) {
    std::swap(entranceA, exitA);
        std::swap(entranceB, exitB);
  }
  else {
    std::swap(connectedPortal->entranceA, connectedPortal->exitA);
    std::swap(connectedPortal->entranceB, connectedPortal->exitB);
  }
}

