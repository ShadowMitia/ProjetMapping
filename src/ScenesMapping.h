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
    ofx::LightSystem2D * lightSystem2D;
    vector<Avatar>  *avatars;
    
    
    Scene1(WorldsBox2d* _worldsBox2d,ofx::LightSystem2D * _lightSystem2D)
    {
        name = "Scene One FBO Source";
        allocate(WidthWord2D, HeightWord2D);
        worldsBox2d =_worldsBox2d;
        lightSystem2D =_lightSystem2D;
        avatars = &_worldsBox2d->avatars;
    }
    void update();
    void draw();
    
    
};



class Scene2 : public ofx::piMapper::FboSource
{
public:
    Scene2()
    {
        name = "Scene Two FBO Source";
        allocate(100, 100);
    }
    
    void draw()
    {
        ofClear(0);
        ofBackground(0, 255, 0, 255);
        
        ofSetColor(255);
        ofDrawBitmapString("2", 50, 50);
    }
};

