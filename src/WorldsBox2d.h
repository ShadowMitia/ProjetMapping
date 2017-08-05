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

#include "Platform.h"
#include "LightSystem2D.h"

constexpr int const MAX_WIIMOTES = 4;

class typeBox2d{
public:
    enum class Type { AVATAR, PLATFORM,FOOT};
    Type type;
};

class WorldsBox2d {
public:


  WorldsBox2d(ofx::LightSystem2D& _lightSystem2D);

  ~WorldsBox2d()
  {
    wiimotes.stopThread();
  }


    ofxBox2d                 world;
    ofRectangle              bounds;
    vector<shared_ptr<ofxBox2dCircle>>	circles;
    std::vector< Avatar > avatars;
    std::vector< Portal * > portals;
    std::vector< Platform * > platforms;
    ofx::LightSystem2D * lightSystem2D;
    
    void setup(ofx::LightSystem2D& _lightSystem2D);
    void createCircle(float _x,float _y);
    void draw();
    void update();

    void createPlatform(ofPolyline _polyline);
    void createPortal();

    
  void createAvatar(int x, int y);

  Wiimotes wiimotes;


  ofx::LightSystem2D lightSystem;

};
