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

class Portal {
public:
    
    enum class Orientation { VERTICAL, HORIZONTAL };
    
    Portal(Orientation ori, int x, int y, int width, int height, ofxBox2d &world)
    : rect(x, y, width, height), world(world), orientation(ori) {
        if (ori == Orientation::HORIZONTAL) {
            entranceA = ofVec2f(x - 10, y - 50);
            entranceB = ofVec2f(x - 10, y + height + 50);
            exitA = ofVec2f(x + width + 10, y - 50);
            exitB = ofVec2f(x + width + 10, y + height + 50);
        }
        else {
            entranceA = ofVec2f(x - 50, y - 10);
            entranceB = ofVec2f(x + width + 50, y - 10);
            
            exitA = ofVec2f(x - 50, y + height + 10);
            exitB = ofVec2f(x + width + 50, y + height + 10);
        }
    }
    
    void update(std::vector<Avatar> &objects);
        
    void draw();
    void linkTo(Portal* p);
    ofRectangle rect;
    int id;
    
private:
    Portal* portal = nullptr;
    ofxBox2d &world;
    ofVec2f entranceA, entranceB;
    ofVec2f exitA, exitB;
    
    Orientation orientation;
    
};
