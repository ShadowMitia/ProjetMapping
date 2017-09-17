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

 Portal(Orientation _ori, Direction _direction, ofRectangle _rect){
         direction = _direction;
         orientation = _ori;
         rect = _rect;
        if (_ori == Orientation::VERTICAL){
            float temp = rect.getWidth();
            rect.setWidth(rect.getHeight());
            rect.setHeight(temp);
            entranceA = ofVec2f(rect.x - 2 , rect.y );
            entranceB = ofVec2f(rect.x - 2 , rect.y + rect.height );
            exitA = ofVec2f(rect.x + rect.width  + 2, rect.y);
            exitB = ofVec2f(rect.x + rect.width + 2, rect.y + rect.height);
	  }
        else{
            entranceA = ofVec2f(rect.x , rect.y - 2);
            entranceB = ofVec2f(rect.x + rect.width , rect.y - 2);

            exitA = ofVec2f(rect.x , rect.y + rect.height + 2);
            exitB = ofVec2f(rect.x + rect.width , rect.y + rect.height + 2);
        }
         if (direction == Direction::LEFT) {
             std::swap(entranceA, exitA);
             std::swap(entranceB, exitB);
         }
         connectedPortal_Angle = NULL;
         connectedPortal_Perspective = NULL;
    }
    
 Portal(Orientation ori, Direction _direction, int x, int y, int width, int height)
      : Portal(ori, _direction, ofRectangle(x, y,height,width))
	  {}
    
    void update(std::vector<Teleportable*> &objects);
    void draw();
    void linkTo(Portal* p_angle, Portal* p_perspective);
	Portal* GetLinkedPortal(Teleportable* obj) const;


    ofRectangle rect;
    int id;
    
private:
    Direction direction;
    Portal* connectedPortal_Angle;
	Portal* connectedPortal_Perspective;
    ofVec2f entranceA, entranceB;
    ofVec2f exitA, exitB;
    
    Orientation orientation;

    bool activated = false;
    
};
