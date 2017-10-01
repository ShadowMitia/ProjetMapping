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
#include "Wiimotes.h"
#include "PhysicalizedElement/Platform.h"
#include "PhysicalizedElement/ObjetBlock.h"
#include "PhysicalizedElement/PickUp.h"
#include "Constant.h"
#include "Ladder.h"
#include "Waterfalls.h"



template<class T>
class data : public T , public dataSprite{};

class typeBox2d{
public:
    enum class Type { AVATAR, PLATFORM, FOOT };
    Type type;
};


class WorldsBox2d {
public:
    
    ofxBox2d                 world;
    ofRectangle              bounds;
    vector<shared_ptr<ofxBox2dCircle>>	circles;
    
    std::vector< Avatar *> avatars;
    std::vector< Avatar *> clodes;
    std::vector< Portal * > portals;
    std::vector< Platform * > platforms;
    std::vector< ObjectBlock * > blocks;
    std::vector< Ladder * > ladders;
  std::vector<PickUp*>  pickups;


    Waterfalls*               warterfalls;
    
    std::vector<Teleportable*> teleportables;

    
    void setup();
    void createCircle(float _x,float _y);
    void draw();
    void update();
    void createBoundsModif(float x, float y, float w, float h);
    void createAvatar(int x, int y);
    void createPlatform(ofPolyline _polyline);
    void createPortal();
    void createLadder(ofPolyline _polyline);
  void createBox(ofPolyline _polyline);

private:

    void importPortal();
};
