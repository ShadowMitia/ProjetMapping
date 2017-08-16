//
//  waterfalls.hpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 05/08/2017.
//
//

#pragma once
#include "ofMain.h"
#include "ofxBox2d.h"
#include "Constant.h"
#include "Teleportable.h"



class Water {
public:
    
    ofxBox2dPolygon water;
    float size;
    ofColor color;
    ofTimer time;
    
};


class Waterfalls{
public:
    Waterfalls(ofxBox2d* _box2d);
    vector < Water* > waters;
    ofRectangle       spawn,despawn;
    void update();
    ofPolyline polyWater;
private:
    ofxBox2d* box2d;
    int  timeDead;
    void spawnWater();
    void despawnWater();
};

class dataWater: public dataSprite {
public:
    dataWater(){
        setSprite(Sprite::WATER);
    }
    Water* WaterPtr;
};

