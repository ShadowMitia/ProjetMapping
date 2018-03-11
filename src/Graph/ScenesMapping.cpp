//
//  ScenesMapping.c
//  ProjetMapping
//
//  Created by FatDazz_mac on 04/08/2017.
//
//

enum  BLENDMODES{BlendNormal = 0, BlendDarkenf = 1};
#include "ScenesMapping.h"


void Scene1::draw()
{

    //ofClear(0);
    for (int i=0; i<nbLayer; ++i) {
        layer[i].begin();
        ofClear(0, 0, 0, 0);
        if (i==0) {
            //background.draw(0, 0);
        }
        if (i==2) {
            plaforms.draw(0, 0);
        }
        if (i==nbLayer-1) {
            //worldsBox2d->draw(); //non alex
        }
        layer[i].end();
    }

    // Affiche tout les sprites
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    // solide
    for (int i = 0; i<_spritesSolide->size(); ++i) {
        if (_spritesSolide->at(i)->isActif()) {
            fillMatrix(_spritesSolide->at(i));
            fboFace.begin();
            ofClear(0,0,0,0);
            _spritesSolide->at(i)->draw();
            fboFace.end();
            //faceToLayer(sprites->at(i)->layerId,0);
            faceToLayer(&layer[_spritesSolide->at(i)->layerId], 0);
        }

    }

    // light
    for (int i = 0; i< _spritesLight->size(); i++) {
        if (_spritesLight->at(i)->isActif()) {
            fillMatrix(_spritesLight->at(i));
            fboFace.begin();
            ofClear(0,0,0,0);
            fboFace.end();
            
            layerToFace(layer[2].getTexture());
            
            Light* light = dynamic_cast<Light *>(_spritesLight->at(i));
            lightRender.renderLights(&fboFaceShadow, light);
            fboFace.begin();
            ofClear(0,0,0,0);
            ofPushMatrix();
            ofTranslate(light->getPositionTranform().x - lightSize/2, light->getPositionTranform().y-lightSize/2);
            fboFaceShadow.draw(0, 0);
            fboFace.end();
            glEnable(GL_BLEND);
            glBlendFunc(GL_ONE, GL_ZERO);
            faceToLayer(&layer[1],1);
            ofEnableBlendMode(OF_BLENDMODE_ALPHA);
            
        }
    }
    
    
    fillMatrix(_spritesLight->at(_spritesLight->size()-1));
    ////
    fboFace.begin();
    ofClear(0,0,0,0);//// je crois qu'il y a pas besion de ça 
    fboFace.end();
    
    layerToFace(layer[2].getTexture());
    
    Light* light = dynamic_cast<Light *>(_spritesLight->at(_spritesLight->size()-1));
    lightRender.renderLights(&fboFaceShadow, light);
    
    fboFace.begin();
    ofClear(0,0,0,0);
    ofPushMatrix();
    ofTranslate(light->getPositionTranform().x - lightSize/2, light->getPositionTranform().y-lightSize/2);
    fboFaceShadow.draw(0, 0);
    fboFace.end();
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ZERO);
    faceToLayer(&layer[1],1);
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);

    
    background.draw(0, 0);
    //ofBackground(ofColor::white);
    ofSetColor(ofColor::white);
    
    for (int i=1; i<nbLayer; ++i) {
        if (i!=20) {
            layer[i].draw(0, 0);

        }
    }

    // debug mode
    ofPopMatrix();
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
void Scene2::draw()
{
    ofSetColor(ofColor::white);
    worldsBox2d->draw();
}