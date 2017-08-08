//
//  ScenesMapping.h
//  ProjetMapping
//
//  Created by FatDazz_mac on 16/07/2017.
//
//
#pragma once

#include "ofMain.h"
#include "Constant.h"
#include "ofxPiMapper.h"
#include "FboSource.h"
#include "WorldsBox2d.h"
#include "Avatar.h"
#include "LightSystem2D.h"


class Scene1 : public ofx::piMapper::FboSource
{
public:
    WorldsBox2d *worldsBox2d;
    ofx::LightSystem2D* lightSystem2D;
    vector<Avatar>  *avatars;
    
    
    Scene1(WorldsBox2d* _worldsBox2d,ofx::LightSystem2D* _lightSystem2D){
        name = "Scene One FBO Source";
        allocate(WidthWord2D, HeightWord2D);
        worldsBox2d =_worldsBox2d;
        avatars = &_worldsBox2d->avatars;
        lightSystem2D = _lightSystem2D;
    }
    void update();
    void draw();
    
    
};



class Scene2 : public ofx::piMapper::FboSource
{
public:
    WorldsBox2d *worldsBox2d;
    ofx::LightSystem2D* lightSystem2D;

    Scene2(WorldsBox2d* worldsBox2d,ofx::LightSystem2D* lightSystem2D)
      : worldsBox2d(worldsBox2d),
      lightSystem2D(lightSystem2D)
    {
        name = "Scene Two FBO Source";
        allocate(WidthWord2D, HeightWord2D);
    }

    void draw();


};
