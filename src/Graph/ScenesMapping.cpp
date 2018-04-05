//
//  ScenesMapping.c
//  ProjetMapping
//
//  Created by FatDazz_mac on 04/08/2017.
//
//



enum  BLENDMODES{BlendNormal = 0, BlendDarkenf = 1};
#include "ScenesMapping.h"
#include "fctGraph.h"

void Scene1::draw()
{

    //ofClear(0);
    for (int i=0; i<nbLayer; ++i) {
        layer[i].begin();
        ofClear(0, 0, 0, 0);
        if (i==0) {
            background.draw(0, 0);
        }
        if (i==2) {
            layerPlatform.draw(0, 0);
        }
        if (i==nbLayer-1) {
            //worldsBox2d->draw(); //non alex
            //ofBackground(ofColor::black);
        }
        layer[i].end();
    }

    // Affiche tout les sprites
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    // solide
    for (int i = 0; i<_spritesSolide->size(); ++i) {
        if (_spritesSolide->at(i)->isActif()) {
            #ifdef Code_Size
            fillMatrixTo160(_spritesSolide->at(i));
            #else
            fillMatrix(_spritesSolide->at(i));
            #endif
            fboFace.begin();
            ofClear(0,0,0,0);
            _spritesSolide->at(i)->draw();
            fboFace.end();
            //faceToLayer(sprites->at(i)->layerId,0);
            faceToLayer(&layer[_spritesSolide->at(i)->layerId], 0);
        }

    }

    // light
    /*for (int i = 0; i< _spritesLight->size(); i++) {
        if (_spritesLight->at(i)->isActif()) {
            fillMatrix(_spritesLight->at(i));
            fboFace.begin();
            ofClear(0,0,0,0);
            fboFace.end();
            
            layerToFace(layer[2].getTexture());
            ofEnableBlendMode(OF_BLENDMODE_ALPHA);
            Light* light = dynamic_cast<Light *>(_spritesLight->at(i));
            lightRender.renderLights(&fboFaceShadow, light);
            fboFace.begin();
            ofClear(0,0,0,0);
            ofPushMatrix();
            ofTranslate(light->getPositionTranform().x - lightSize/2, light->getPositionTranform().y-lightSize/2);
            //fboFaceShadow.draw(0, 0);
            //_spritesLight->at(i)->draw();
            fboFace.end();
            
            glEnable(GL_BLEND);
            glBlendFunc(GL_ONE, GL_ZERO);
            faceToLayer(&layer[2],1);
            ofEnableBlendMode(OF_BLENDMODE_ALPHA);
            
            
            fboFace.begin();
            ofClear(0,0,0,0);
            ofBackground(ofColor::black);
            ofPushMatrix();
            ofTranslate(light->getPositionTranform().x , light->getPositionTranform().y);
            glEnable(GL_BLEND);
            glBlendFunc(GL_ONE, GL_ZERO);
            ofSetColor(ofColor::white);
            ofDrawCircle(0, 0, 82);
            fboFace.end();
            
            ofEnableBlendMode(OF_BLENDMODE_SUBTRACT);
            faceToLayer(&layer[nbLayer-1], 2);
            ofEnableBlendMode(OF_BLENDMODE_ALPHA);
            
            
        }
    }*/
    
    

    ofSetColor(ofColor::white);

    
    for (int i=0; i<nbLayer; ++i) {
        if (i!=20) {
            layer[i].draw(0, 0);

        }
    }



    // debug mode
    //ofPopMatrix();
    //worldsBox2d->draw();
    
    //fboFace.draw(0, 0);
    //layer[0].draw(0, 0);
    //fboFaceShadow.draw(0, 0);

}
void Scene1::renderObjects()
{
    //image.draw(0, 0);
}
void Scene1::renderPlatform()
{
    fboFace.draw(0,0);
}
void Scene1::update()
{
    
}

Scene1::Scene1(Scene1Def def){
    name = "Scene One FBO Source";
    _spritesSolide= def._spritesSolide;
    _spritesLight = def._spritesLight;
    background.load(def.background_name);
    plaforms.load(def.plaforms_name);
    #ifdef Code_Size
    background.load(def.background_name);
    plaforms.load(def.plaforms_name);
    background.resize(background.getWidth()/2, background.getHeight()/2);
    plaforms.resize(plaforms.getWidth()/2, plaforms.getHeight()/2);
    FaceFunction::setup(160.0);
    #else
    background.load(def.background_name);
    plaforms.load(def.plaforms_name);
    #endif
    
    allocate(background.getWidth(), background.getHeight());
    worldsBox2d =def.worldsBox2d;
    
    
    
    #ifdef Code_Size
    fboFaceShadow.allocate(160*3, 160*3);
    #else
    fboFaceShadow.allocate(320*3, 320*3);
    #endif
    for (int i=0; i<nbLayer; ++i) {
        layer[i].allocate(background.getWidth(), background.getHeight());
    }
    layerPlatform.allocate(background.getWidth(), background.getHeight());
    
    #ifdef Code_Size
    lightSize = 160;
    #else
    lightSize = 320;
    #endif
    ofDisableArbTex();  // <-- Very Important
    lightRender.setup(lightSize,lightSize);
    lightRender.setRenderFunction(this, &Scene1::renderPlatform);
    lightRender.setRenderFunction(this, &Scene1::renderObjects);
    mask.allocate(background.getWidth(), background.getHeight());
    mask.begin();
    ofClear(0);
    mask.end();
    
    ofTessellator t;
    vector<ofPolyline> BezierPlatform, mousePlatform;
    vector<ofPolyline>  platforms = importImage(plaforms.getTexture());
    for (int i = 0; i< platforms.size(); i++) {
        BezierPlatform.push_back(fctBezier(platforms[i], ofPoint(3,3), 2));
        Append(mousePlatform, mouse(platforms[i], ofPoint(3,3),2));

    }
    cout << " nb de plateporme : " << BezierPlatform.size()  << endl;
    ofMesh BezierPlatformMesh,mousePlatformMesh;
    t.tessellateToMesh(BezierPlatform, ofPolyWindingMode::OF_POLY_WINDING_ODD, BezierPlatformMesh);
    t.tessellateToMesh(mousePlatform, ofPolyWindingMode::OF_POLY_WINDING_ODD, mousePlatformMesh);
 
    layerPlatform.begin();
    ofClear(0, 0, 0, 0);
    ofSetColor(ofColor::brown);
    BezierPlatformMesh.draw();
    ofSetColor(ofColor::paleGreen);
    mousePlatformMesh.draw();
    layerPlatform.end();
    ofSetColor(ofColor::white);

}


void Scene2::draw()
{
    ofSetColor(ofColor::white);
    worldsBox2d->draw();
}