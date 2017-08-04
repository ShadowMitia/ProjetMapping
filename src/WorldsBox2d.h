//
//  WorldsBox2d.hpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 16/07/2017.
//
//
#pragma once

#include "ofxBox2d.h"
#include "Avatar.h"
#include "Portal.h"
#include "Wiimotes.h"
#include "Light2D.h"

constexpr int const MAX_WIIMOTES = 4;

class WorldsBox2d {
public:

  WorldsBox2d() : wiimotes(MAX_WIIMOTES, avatars)
  {

  }

  ~WorldsBox2d()
  {
    wiimotes.stopThread();
  }

  ofxBox2d                 world;
  ofRectangle              bounds;
  std::vector< std::shared_ptr<ofxBox2dCircle>>	circles;
  std::vector< Avatar > avatars;
  std::vector< Portal > portals;
    
    
  void setup();
  void createCircle(float _x,float _y);
  void draw();
  void update();
    
  void createAvatar(int x, int y);

  Wiimotes wiimotes;


  ofx::LightSystem2D lightSystem;

};
