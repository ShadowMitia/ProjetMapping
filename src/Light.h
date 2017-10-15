//
//  Light.h
//  ProjetMapping
//
//  Created by FatDazz_mac on 13/10/2017.
//
//


#pragma once
#include "ofMain.h"
#include "Poco/BasicEvent.h"
#include "Poco/Delegate.h"

class Light {
public:
    Light() {
        color.set(0.5f, 1.0f, 0.0f);
    }
    ofFloatColor color;
    ofPoint pos, vel;
};

class LightRender {
    
private:
    Poco::BasicEvent <void> renderEventPlatform;
    Poco::BasicEvent <void> renderEventObjet;
    ofShader occludersShader, shadowMapShader, lightShader;
public:
    
    float radius;
    vector <Light> lights;
    ofFbo occludersFBOPlaform,occludersFBOObjet, shadowMapFBOPlatform, shadowMapFBOObjet , objectsFBO, lightFBO;
    int width, height;
    
    LightRender() {
    }
    
    template <class TObj>
    void setRenderFuctionPlatform(TObj  * listener, void (TObj::*listenerMethod)()){
        renderEventPlatform += Poco::Delegate<TObj, void, false>(listener, listenerMethod);
    }
    template <class TObj>
    void setRenderFuctionObjet(TObj  * listener, void (TObj::*listenerMethod)()){
        renderEventObjet += Poco::Delegate<TObj, void, false>(listener, listenerMethod);
    }
    //--------------------------------------------------------------
    void setup(int w, int h) {
        
        ofDisableArbTex();  // <-- Very Important
        
        width = w;height=h;
        occludersFBOPlaform.allocate(width, height, GL_RGBA);
        occludersFBOObjet.allocate(width, height, GL_RGBA);
        lightFBO.allocate(width, height, GL_RGBA);
        objectsFBO.allocate(width, height, GL_RGBA);
        
        ofFbo::Settings s;
        s.width  = width;
        s.height = 1;
        s.maxFilter =GL_LINEAR;
        s.minFilter = GL_LINEAR;
        s.wrapModeHorizontal = GL_REPEAT;
        s.wrapModeVertical = GL_REPEAT;
        s.internalformat = GL_RGBA;
        s.useDepth = false;
        shadowMapFBOPlatform.allocate(s);
        shadowMapFBOObjet.allocate(s);
        
        ofFbo::Settings lightS;
        lightS.width  = width;
        lightS.height = height;
        lightS.useDepth = false;
        lightS.internalformat = GL_RGBA;
        lightFBO.allocate(lightS);
        
        if(!occludersShader.load("pass.vert", "pass.frag")) {
            printf("Error loading occludersShader\n");
        }
        if(!shadowMapShader.load("pass.vert", "shadowMap.frag")) {
            printf("Error loading shadowMapShader\n");
        }
        if(!lightShader.load("pass.vert", "light.frag")) {
            printf("Error loading lightShader\n");
        }
        
    }
    //--------------------------------------------------------------
    void addLight(float x, float y) {
        Light p;
        p.pos.set(x, y);
        p.vel.set(0, ofRandom(0.2, 1.0));
        lights.push_back(p);
    }
    void callRenderRunction() {
        try {
            renderEventPlatform.notify(this);
        }
        catch(Poco::Exception &e) {
            
        }
    }
    void callRenderRunction2() {
        try {
            renderEventObjet.notify(this);
        }
        catch(Poco::Exception &e) {
            
        }
    }
    //--------------------------------------------------------------
    void debugDraw(float x, float y, float drawWidth=500) {
        int nFbos = 2;
        float sw = drawWidth / (float)(width*nFbos);
        float sh = sw;
        
        ofPushMatrix();
        ofTranslate(x,y);
        ofScale((float)sw, (float)sh);
        ofEnableAlphaBlending();
        ofSetColor(255);
        occludersFBOPlaform.draw(0, 0);
        occludersFBOObjet.draw(0, 0);
        ofSetColor(255);
        shadowMapFBOPlatform.draw(width, 0, width, height);
        
        for(int i=0; i<lights.size(); i++) {
            ofSetColor(255, 255, 0);
            ofCircle(lights[i].pos.x, lights[i].pos.y, 5,5);
        }
        
        ofPopMatrix();
    }
    //--------------------------------------------------------------
    void renderLights() {
        
        /*
         objectsFBO.begin();
         ofClear(0, 0, 0, 0);
         callRenderRunction();
         objectsFBO.end();
         */
        
        lightFBO.begin();
        ofClear(0, 0, 0);
        
        glEnable(GL_BLEND);
        glBlendFunc(GL_ONE, GL_ONE);
        
        for(int i=0; i<lights.size(); i++) {
            Light light = lights[i];
            
            
            // -------------------------------
            // Occlusion Map
            // -------------------------------
            occludersFBOPlaform.begin();
            ofClear(0, 0, 0, 0);
            //occludersShader.begin();
            ofPushMatrix();
            ofTranslate(-light.vel.x + (width / 2), - light.vel.y + (width / 2));
            //ofTranslate((width/2)-light.pos.x, (height/2)-light.pos.y);
            callRenderRunction(); // image occuders
            ofPopMatrix();
            //occludersShader.end();
            occludersFBOPlaform.end();
            
            
            occludersFBOObjet.begin();
            ofClear(0, 0, 0, 0);
            //occludersShader.begin();
            ofPushMatrix();
            ofTranslate(-light.vel.x + (width / 2), - light.vel.x + (width / 2));
            callRenderRunction2(); // image occuders
            ofPopMatrix();
            occludersFBOObjet.end();
            
            
            // -------------------------------
            // 1d Shadow Map
            // -------------------------------
            shadowMapFBOPlatform.begin();
            shadowMapShader.begin();
            ofClear(0, 0, 0, 0);
            shadowMapShader.setUniform2f("lightLocation", lights[i].pos.x, lights[i].pos.y);
            shadowMapShader.setUniform2f("resolution", width, height);
            shadowMapShader.setUniformTexture("u_texture", occludersFBOPlaform.getTextureReference(), 0);
            occludersFBOPlaform.draw(0, 0);
            shadowMapShader.end();
            shadowMapFBOPlatform.end();
            
            
            shadowMapFBOObjet.begin();
            shadowMapShader.begin();
            ofClear(0, 0, 0, 0);
            shadowMapShader.setUniform2f("lightLocation", lights[i].pos.x, lights[i].pos.y);
            shadowMapShader.setUniform2f("resolution", width, height);
            shadowMapShader.setUniformTexture("u_texture", occludersFBOObjet.getTextureReference(), 0);
            occludersFBOObjet.draw(0, 0);
            shadowMapShader.end();
            shadowMapFBOObjet.end();
            
            // -------------------------------
            // Shadows
            // -------------------------------
            lightShader.begin();
            lightShader.setUniform2f("resolution", width, height);
            lightShader.setUniformTexture("u_texturePlaform", shadowMapFBOPlatform.getTextureReference(), 0);
            lightShader.setUniformTexture("u_textureObjet", shadowMapFBOObjet.getTextureReference(), 1);
            
            //lightShader.setUniformTexture("u_objects_tex", objectsFBO.getTextureReference(), 1);
            
            
            lightShader.setUniform2f("lightLocation", lights[i].pos.x, lights[i].pos.y);
            lightShader.setUniform3f("lightColor", lights[i].color.r, lights[i].color.g, lights[i].color.b);
            lightShader.setUniform1f("u_radius", radius);
            ofSetColor(255, 0, 255, 100);
            
            glBegin(GL_QUADS); {
                glVertex2f(0, 0);
                glVertex2f(0, height);
                glVertex2f(width, height);
                glVertex2f(width, 0);
            } glEnd();
            
            lightShader.end();
        }
        glDisable(GL_BLEND);
        
        lightFBO.end();
        
    }
    //--------------------------------------------------------------
    void draw() {
        ofSetColor(255);
        lightFBO.draw(0, 0);
    }
};
