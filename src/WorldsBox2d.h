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
#include "Light2D.h"
#include "PhysicalizedElement/Platform.h"
#include "LightSystem2D.h"
#include "PhysicalizedElement/ObjetBlock.h"
#include "Constant.h"
#include "Waterfalls.h"


constexpr int const MAX_WIIMOTES = 4;

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
    std::vector< Avatar > avatars;
    std::vector< Portal * > portals;
    std::vector< Platform * > platforms;
    std::vector< ObjetBlock > blocks;
    Waterfalls*               warterfalls;
    
    
    std::vector<Teleportable*> teleportables;

    ofx::LightSystem2D * lightSystem2D;
    
    void setup(ofx::LightSystem2D * _lightSystem2D);
    void createCircle(float _x,float _y);
    void draw();
    void update();
    void createBoundsModif(float x, float y, float w, float h);
    void createAvatar(int x, int y);
    void createPlatform(ofPolyline _polyline);
    void createPortal();
    

    //Wiimotes wiimotes;


    //ofx::LightSystem2D lightSystem;
private:
    

};
