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
    for (int i = 0; i<sprites->size(); ++i) {
        if (sprites->at(i)->isActif()) {
            fillMatrix(sprites->at(i));
            fboFace.begin();
            ofClear(0,0,0,0);
            sprites->at(i)->draw();
            fboFace.end();
            faceToLayer(sprites->at(i)->layer,0);
        }

    }

    
    for (int i = sprites->size(); i<sprites->size()-1; i++) {
        if (sprites->at(i)->isActif()) {
            fillMatrix(sprites->at(i));
            fboFace.begin();
            ofClear(0,0,0,0);
            fboFace.end();
            
            layerToFace(2);
            
            Light* light = dynamic_cast<Light *>(sprites->at(i));
            lightRender.renderLights(&fboFaceShadow, light);
            fboFace.begin();
            ofClear(0,0,0,0);
            ofPushMatrix();
            ofTranslate(light->getPositionTranform().x - lightSize/2, light->getPositionTranform().y-lightSize/2);
            fboFaceShadow.draw(0, 0);
            fboFace.end();
            glEnable(GL_BLEND);
            glBlendFunc(GL_ONE, GL_ZERO);
            faceToLayer(1,1);
            ofEnableBlendMode(OF_BLENDMODE_ALPHA);
        }
    }
    
    
    fillMatrix(sprites->at(sprites->size()-1));
    fboFace.begin();
    ofClear(0,0,0,0);
    fboFace.end();
    layerToFace(2);
    
    Light* light = dynamic_cast<Light *>(sprites->at(sprites->size()-1));
    lightRender.renderLights(&fboFaceShadow, light);
    
    fboFace.begin();
    ofClear(0,0,0,0);
    ofPushMatrix();
    ofTranslate(light->getPositionTranform().x - lightSize/2, light->getPositionTranform().y-lightSize/2);
    fboFaceShadow.draw(0, 0);
    fboFace.end();
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ZERO);
    faceToLayer(1,1);
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);

    
    background.draw(0, 0);
    
    ofSetColor(ofColor::white);
    
    for (int i=1; i<nbLayer; ++i) {
        layer[i].draw(0, 0);
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
void Scene1::fillMatrix(SpriteObj *_sprite)
{
    bool i = _sprite->getViewPoint();
    matrix[0].set(_sprite->face->matrix[i][0]->rect.x, _sprite->face->matrix[i][3]->rect.x, _sprite->face->matrix[i][6]->rect.x,
                  _sprite->face->matrix[i][1]->rect.x, _sprite->face->matrix[i][4]->rect.x, _sprite->face->matrix[i][7]->rect.x,
                  _sprite->face->matrix[i][2]->rect.x, _sprite->face->matrix[i][5]->rect.x, _sprite->face->matrix[i][8]->rect.x);
    matrix[1].set(_sprite->face->matrix[i][0]->rect.y, _sprite->face->matrix[i][3]->rect.y, _sprite->face->matrix[i][6]->rect.y,
                 _sprite->face->matrix[i][1]->rect.y, _sprite->face->matrix[i][4]->rect.y, _sprite->face->matrix[i][7]->rect.y,
                 _sprite->face->matrix[i][2]->rect.y, _sprite->face->matrix[i][5]->rect.y, _sprite->face->matrix[i][8]->rect.y);
    matrix[2] = _sprite->face->matrixR[i];

}
void Scene1::faceToLayer(int _layer, int mode)
{

    layer[_layer].begin();
    //ofSetColor(ofColor::white);
    ShaderFaceToLayer.begin();
    ShaderFaceToLayer.setUniform1i("mode", mode);
    ShaderFaceToLayer.setUniformTexture("u_texture", fboFace.getTexture(), 0);
    ShaderFaceToLayer.setUniformTexture("u_texture_src", layer[_layer].getTexture(), 1);
    ShaderFaceToLayer.setUniformMatrix3f("matrixX", matrix[0]);
    ShaderFaceToLayer.setUniformMatrix3f("matrixY", matrix[1]);
    ShaderFaceToLayer.setUniformMatrix3f("matrixR", matrix[2]);
    ofDrawRectangle(ofPoint(0,0), layer[_layer].getWidth(), layer[_layer].getHeight());
    ShaderFaceToLayer.end();
    layer[_layer].end();
    
}
void Scene1::layerToFace(int _layer)
{
    fboFace.begin();
    ofClear(0,0,0,0);  //Attantion c est pas remis ˆ 0
    ShaderLayerToFace.begin();
    ShaderLayerToFace.setUniformTexture("u_texture", layer[_layer].getTexture(), 0);
    ShaderLayerToFace.setUniformMatrix3f("matrixX", matrix[0]);
    ShaderLayerToFace.setUniformMatrix3f("matrixY", matrix[1]);
    ShaderLayerToFace.setUniformMatrix3f("matrixR", matrix[2]);
    ofSetColor(ofColor::white, 0);
    ofDrawRectangle(ofPoint(0,0), 3*160, 3*160);
    ShaderLayerToFace.end();
    fboFace.end();
}
void Scene2::draw()
{
    ofSetColor(ofColor::white);
    worldsBox2d->draw();
}