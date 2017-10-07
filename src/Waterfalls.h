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
#include "PhysicalizedElement/Teleportable.h"
#include "ofxLiquidFun.h"



class Waterfalls{
public:
    Waterfalls() = delete;
    Waterfalls(ofxBox2d* _box2d);
    ofxBox2dParticleSystem waters;
    ofRectangle       spawn, despawn;
    void update();
    void draw();
    ofPolyline polyWater;
private:
    ofxBox2d* box2d;
    int  timeDead;
    void spawnWater();
    void despawnWater();
};

/*
class dataWater: public dataSprite {
public:
    dataWater(){
        setSprite(Sprite::WATER);
    }
    //Water* WaterPtr;
};
*/
