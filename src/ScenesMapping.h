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
#include "PhysicalizedElement/Avatar.h"
#include "Light.h"


class Scene1 : public ofx::piMapper::FboSource
{
public:
    int lightSize;
    LightRender lightRender;
    WorldsBox2d *       worldsBox2d;
    ofImage image;
    ofImage imagePlatform;

    Scene1(WorldsBox2d* _worldsBox2d, string path){
        image.load(path);
        name = "Scene One FBO Source";
        allocate(image.getWidth(), image.getHeight());
        worldsBox2d =_worldsBox2d;

        lightSize = 256;
        ofDisableArbTex();  // <-- Very Important
        lightRender.setup(lightSize,lightSize);
        lightRender.setRenderFunction(this, &Scene1::renderObjects);
        lightRender.setRenderFunction(this, &Scene1::renderPlatform);
        lightRender.addLight(lightSize/2, lightSize/2);

	mask.allocate(image.getWidth(), image.getHeight());

	mask.begin();
	ofClear(0);
	mask.end();
    }

  ofFbo mask;


    void update();
    void draw();
    void renderObjects();
    void renderPlatform();

  void faceBorders()
  {

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
