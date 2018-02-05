//
//  Header.h
//  ProjetMapping
//
//  Created by FatDazz_mac on 03/02/2018.
//
//
#pragma once

#include "ofMain.h"
#include "Constant.h"

struct Face{
    ofRectangle rect;
    Face * matrix[9];
};

class Transform{
public:
    Transform(){
        
        fboTransform.allocate(159*3, 159*3); // changer 159
        if(!transform.load("passTransform.vert", "transform.frag")) {
            printf("transform.frag\n");
        }
        //fboSortie.allocate(VarConst::WidthWorld2D, VarConst::HeightWorld2D);
        if(!transformInv.load("passTransform.vert", "transformInv.frag")) {
            printf("transformInv.frag\n");
        }
    }
    void setFboIni(ofFbo* _fboIni){
        fboIni =_fboIni;
    }
    void update(Face* face, ofVec2f p, ofRectangle imag){
        
        ofMatrix3x3 matrixX , matrixY;
        matrixX.set(face->matrix[0]->rect.x, face->matrix[1]->rect.x, face->matrix[2]->rect.x,
                    face->matrix[3]->rect.x, face->matrix[4]->rect.x, face->matrix[5]->rect.x,
                    face->matrix[6]->rect.x, face->matrix[7]->rect.x, face->matrix[8]->rect.x);
        
        
        matrixY.set(face->matrix[0]->rect.y, face->matrix[1]->rect.y, face->matrix[2]->rect.y,
                    face->matrix[3]->rect.y, face->matrix[4]->rect.y, face->matrix[5]->rect.y,
                    face->matrix[6]->rect.y, face->matrix[7]->rect.y, face->matrix[8]->rect.y);
        
        

        fboTransform.begin();
        ofClear(0,0,0,0);
        transform.begin();
        transform.setUniformTexture("u_texture", fboIni->getTexture(), 0);
        transform.setUniformMatrix3f("matrixX", matrixX);
        transform.setUniformMatrix3f("matrixY", matrixY);
        ofDrawRectangle(ofPoint(0,0), 3*40, 3*40);
        transform.end();
        // placement asset
        //imag.draw(p);
        ofDrawRectangle(imag);
        fboTransform.end();
        
        fboIni->begin();
        transformInv.begin();
        transformInv.setUniformTexture("u_texture", fboTransform.getTexture(), 0);
        transformInv.setUniformMatrix3f("matrixX", matrixX);
        transformInv.setUniformMatrix3f("matrixY", matrixY);
        ofDrawRectangle(ofPoint(0,0), 160, 160);
        transformInv.end();
        fboIni->end();
    }
    
    ofFbo* fboIni;
    ofShader transform;
    ofFbo fboTransform;
    ofShader transformInv;
    
};
