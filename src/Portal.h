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

class Teleportable;

class Portal {
public:

  /*
   * Possible TODO: custom orientations for exits (now are relative to create "tunnels")
   *
   */


  enum class Direction {LEFT, RIGHT};
  enum class Orientation { VERTICAL, HORIZONTAL };

 Portal(Orientation ori, ofRectangle rect)
     : rect(rect), orientation(ori) {
        if (ori == Orientation::HORIZONTAL)
	  {
            entranceA = ofVec2f(rect.x - 10, rect.y - 50);
            entranceB = ofVec2f(rect.x - 10, rect.y + rect.height + 50);
            exitA = ofVec2f(rect.x + rect.width + 10, rect.y - 50);
            exitB = ofVec2f(rect.x + rect.width + 10, rect.y + rect.height + 50);
	  }
        else
	  {
            entranceA = ofVec2f(rect.x - 50, rect.y - 10);
            entranceB = ofVec2f(rect.x + rect.width + 50, rect.y - 10);

            exitA = ofVec2f(rect.x - 50, rect.y + rect.height + 10);
            exitB = ofVec2f(rect.x + rect.width + 50, rect.y + rect.height + 10);
        }
    }
    
 Portal(Orientation ori, int x, int y, int width, int height)
      : Portal(ori, ofRectangle(x, y, width, height))
	  {

	  }
    
    void update(std::vector<Teleportable*> &objects);
        
    void draw();
    void linkTo(Portal* p);
    ofRectangle rect;
    int id;
    
private:
    Portal* connectedPortal = nullptr;
    ofVec2f entranceA, entranceB;
    ofVec2f exitA, exitB;
    
    Orientation orientation;

    bool activated = false;
    
};
