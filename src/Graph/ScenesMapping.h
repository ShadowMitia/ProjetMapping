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
#include "Light.h"
#include "Face.h"
//#include "Sprite.h"

class Scene1 : public ofx::piMapper::FboSource
{
public:
    int lightSize;
    LightRender lightRender;
    ofImage background;
    vector<SpriteObj*>* sprites;
    Transform transform;
    ofFbo drawMap;
    WorldsBox2d* worldsBox2d;
    ofFbo mask;
    
    void update();
    void draw();
    void renderObjects();
    void renderPlatform();
    
    //Scene1(vector<SpriteObj*>* _sprites, string path){
    Scene1(WorldsBox2d* _worldsBox2d, string path, vector<SpriteObj*>* _sprites){
        sprites=_sprites;
        background.load(path);
        name = "Scene One FBO Source";
        allocate(background.getWidth(), background.getHeight());
        worldsBox2d =_worldsBox2d;
        //sprites = _sprites;
        
        lightSize = 256;
        ofDisableArbTex();  // <-- Very Important
        lightRender.setup(lightSize,lightSize);
        lightRender.setRenderFunction(this, &Scene1::renderObjects);
        lightRender.setRenderFunction(this, &Scene1::renderPlatform);
        lightRender.addLight(lightSize/2, lightSize/2);
        
        mask.allocate(background.getWidth(), background.getHeight());
        
        mask.begin();
        ofClear(0);
        mask.end();
        
        drawMap.allocate(background.getWidth(), background.getHeight());
    }
    
    
};


class Scene2 : public ofx::piMapper::FboSource
{
public:
    WorldsBox2d *worldsBox2d;

    Scene2(WorldsBox2d* worldsBox2d)
      : worldsBox2d(worldsBox2d)
    {
        name = "Scene Two FBO Source";
        allocate(VarConst::WidthWorld2D, VarConst::HeightWorld2D);
    }

    void draw();


};
