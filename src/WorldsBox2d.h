//
//  WorldsBox2d.hpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 16/07/2017.
//
//

#pragma once
#include "ofxBox2d.h"
#include "PhysicalizedElement/Avatar.h"
#include "Portal.h"
#include "PhysicalizedElement/PhysicalizedElement.h"
#include "PhysicalizedElement/Platform.h"
//#include "PhysicalizedElement/ObjetBlock.h"
//#include "PhysicalizedElement/PickUp.h"
#include "Constant.h"
#include "Ladder.h"
#include "Waterfalls.h"
#include "Clone.h"

#include <vector>


class WorldsBox2d :public ofThread{
public:
    
  ofxBox2d                 world;
  ofRectangle              bounds;
    
    std::vector< Avatar *> avatars;
    std::vector<Portal *> porportal;
    std::vector< Platform * > platforms;
    std::vector< Ladder * > ladders;
    std::vector< CloneBox2d *> clones;

  Waterfalls*               warterfalls;
  std::vector<Teleportable*> teleportables;
    
  void setup();
  void draw();
  void update();
  void createBoundsModif(float x, float y, float w, float h);
  void createAvatar(int x, int y);
  void createPlatform(ofPolyline _polyline);
  void createPortal();
  void createLadder(ofPolyline _polyline);
  void createBox(ofPolyline _polyline);
  void createPickup(ofPolyline polyline);

  ofRectangle noGravityWell;

private:
 void importPortal();
};
