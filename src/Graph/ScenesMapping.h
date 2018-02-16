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


/*Layer
 Layer 0 -> background
 Layer 1 -> platforms & objets
 Layer 2 -> Ombres platforms & objets
 Layer 3 -> Avatar & Light
 Layer 4 -> Mushroom (top)
 Layer 5 -> Objets
 Layer 6 -> Ombres on Mushroom
 Layer 7 -> Avatar & Light
 Layer 8 -> Mask
 
*/

class Scene1 : public ofx::piMapper::FboSource
{
public:
    int lightSize;
    LightRender lightRender;
    ofImage background, plaforms;
    vector<SpriteObj*>* sprites;
    
    WorldsBox2d* worldsBox2d;
    ofFbo mask;
    void update();
    void draw();
    void renderObjects();
    void renderPlatform();
    
    ofFbo fboFaceShadow;
    
    ofFbo layer[nbLayer];
    ofFbo fboFace;
    ofMatrix3x3 matrix[3];
    void fillMatrix(SpriteObj* _sprite);
    void faceToLayer(int layer, int mode);
    void layerToFace(int layer);
    ofShader ShaderLayerToFace;
    ofShader ShaderFaceToLayer;
    
    //Scene1(vector<SpriteObj*>* _sprites, string path){
    Scene1(WorldsBox2d* _worldsBox2d, string background_name, vector<SpriteObj*>* _sprites, string plaforms_name){
        name = "Scene One FBO Source";
        sprites=_sprites;
        background.load(background_name);
        plaforms.load(plaforms_name);
        allocate(background.getWidth(), background.getHeight());
        worldsBox2d =_worldsBox2d;
        
        fboFace.allocate(160*3, 160*3);
        fboFaceShadow.allocate(160*3, 160*3);
        for (int i=0; i<nbLayer; ++i) {
            layer[i].allocate(background.getWidth(), background.getHeight());
        }
        if(!ShaderLayerToFace.load("passTransform.vert", "layerToFace.frag")) {
            printf("transform.frag\n");
        }
        //fboSortie.allocate(VarConst::WidthWorld2D, VarConst::HeightWorld2D);
        if(!ShaderFaceToLayer.load("passTransform.vert", "faceToLayer.frag")) {
            printf("transformInv.frag\n");
        }

        
        
        lightSize = 256;
        ofDisableArbTex();  // <-- Very Important
        lightRender.setup(lightSize,lightSize);
        lightRender.setRenderFunction(this, &Scene1::renderPlatform);
        
        lightRender.setRenderFunction(this, &Scene1::renderObjects);
        
        //lightRender.addLight(lightSize/2, lightSize/2);
        
        mask.allocate(background.getWidth(), background.getHeight());
        
        mask.begin();
        ofClear(0);
        mask.end();

        
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