//
//  Portal.cpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 23/07/2017.
//
//

#include "Portal.h"

void Portal::update(std::vector<std::shared_ptr<avatar> > & objects) {
    std::vector<std::shared_ptr<avatar>> clones;
    
    for (auto &obj : objects){
        
        bool intersects = obj->rect.intersects(rect);
        bool cloned = obj->hasClone();
        bool inside = obj->rect.inside(rect);
        
        if (obj->rect.intersects(entranceA, entranceB)) {
            std::cout << "Entrance\n";
        }
        
        if (intersects && !cloned) {
            std::cout << "Clone\n";
            obj->createClone(portal->rect.getCenter() - rect.getCenter());
        }
        
        if (!intersects && !inside && cloned && obj->rect.intersects(entranceA, entranceB)) {
            std::cout << "Back\n";
            obj->removeClone();
        }
        else if (!intersects && !inside && cloned && obj->rect.intersects(exitA, exitB)) {
            std::cout << "Exit\n";
            obj->teleportToClone();
            obj->removeClone();
        }
    }
    
    objects.insert(objects.end(), std::make_move_iterator(clones.begin()), std::make_move_iterator(clones.end()));
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
    portal = p;
    
    portal->portal = this;
    
    long first, second;
    
    if (orientation == Orientation::HORIZONTAL) {
        first = rect.getPosition().x;
        second = portal->rect.getPosition().x;
    }
    else {
        first = rect.getPosition().y;
        second = portal->rect.getPosition().y;
    }
    
    if (first > second) {
        std::swap(entranceA, exitA);
        std::swap(entranceB, exitB);
    }
    else {
        std::swap(portal->entranceA, portal->exitA);
        std::swap(portal->entranceB, portal->exitB);
    }
}

