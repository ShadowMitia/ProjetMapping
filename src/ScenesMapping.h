//
//  ScenesMapping.h
//  ProjetMapping
//
//  Created by FatDazz_mac on 16/07/2017.
//
//
#pragma once

#include "ofMain.h"
#include "ofxPiMapper.h"
#include "FboSource.h"
#include "WorldsBox2d.h"

class Scene1 : public ofx::piMapper::FboSource
{
public:
    WorldsBox2d *worldsBox2d;
    
    Scene1(WorldsBox2d* _worldsBox2d)
    {
        name = "Scene One FBO Source";
        allocate(1000, 600);
        worldsBox2d =_worldsBox2d;
        
    }
    
    void draw()
    {
        ofClear(0);
        ofBackground(200, 0, 0, 255);
        //ofDrawBitmapString("1", 50, 50);
        ofSetColor(ofColor::white);
        ofSetLineWidth(1);
        for (int i=0; i<=1000; i+=200) {
            ofDrawLine(i, 0, i, 600);
        }
        for (int i=0; i<=600; i+=200) {
            ofDrawLine(0, i, 1000, i);
        }
        worldsBox2d->drawCircles();
        //worldsBox2d->avatar->draw();
    
    }
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

class Scene3 : public ofx::piMapper::FboSource
{
public:
    Scene3()
    {
        name = "Scene Three FBO Source";
        allocate(100, 100);
    }
    
    void draw()
    {
        ofClear(0);
        ofBackground(0, 0, 255, 255);
        
        ofSetColor(255);
        ofDrawBitmapString("3", 50, 50);
    }
};

class Scene4 : public ofx::piMapper::FboSource
{
public:
    Scene4()
    {
        name = "Scene Four FBO Source";
        allocate(100, 100);
    }
    
    void draw()
    {
        ofClear(0);
        ofBackground(255, 0, 255, 255);
        
        ofSetColor(255);
        ofDrawBitmapString("4", 50, 50);
    }
};

class Scene5 : public ofx::piMapper::FboSource
{
public:
    Scene5()
    {
        name = "Scene Five FBO Source";
        allocate(100, 100);
    }
    
    void draw()
    {
        ofClear(0);
        ofBackground(255, 255, 0, 255);
        
        ofSetColor(255);
        ofDrawBitmapString("5", 50, 50);
    }
};


class Scene6 : public ofx::piMapper::FboSource
{
public:
    Scene6()
    {
        name = "Scene Six FBO Source";
        allocate(100, 100);
    }
    
    void draw()
    {
        ofClear(0);
        ofBackground(200, 200, 200, 255);
        
        ofSetColor(255);
        ofDrawBitmapString("6", 50, 50);
    }
};
