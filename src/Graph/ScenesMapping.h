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
#include "utils.h"

//#include "Sprite.h"


/*  Layer
 Layer 0 -> background
 Layer 1 -> Ombres platforms & objets
 Layer 2 -> Platforms & objets
 Layer 3 -> Avatar & Light
 Layer 4 -> Mushroom (top)
 Layer 5 -> Ombres on Mushroom
 Layer 6 -> Objets
 Layer 7 -> Avatar & Light
 Layer 8 -> Mask
 */


class Scene1Def{
public:
    WorldsBox2d* worldsBox2d;
    string background_name;
    string plaforms_name;
    vector<SpriteObj*>* _spritesSolide;
    vector<SpriteObj*>* _spritesLight;
    
};

class Scene1 : public ofx::piMapper::FboSource, FaceFunction
{
public:
    int lightSize;
    LightRender lightRender;
    ofImage background, plaforms;
    vector<SpriteObj*>*  _spritesSolide;
    vector<SpriteObj*>*  _spritesLight;

    
    WorldsBox2d* worldsBox2d;
    ofFbo mask;
    void update();
    void draw();
    void renderObjects();
    void renderPlatform();
    
    
    ofFbo fboFaceShadow;
    ofFbo layer[nbLayer];
    ofFbo layerPlatform;
    
    //Scene1(vector<SpriteObj*>* _sprites, string path){
    Scene1(Scene1Def def);
    
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