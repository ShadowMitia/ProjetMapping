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
#include "Sprite.h"

struct Face{
    int idFace;
    ofRectangle rect;
    Face * matrix[2][9];
    ofMatrix3x3 matrixR[2];
};

class Transform{
public:
    Transform(){
        
        fboTransform.allocate(160*3, 160*3); // changer 159
        if(!transform.load("passTransform.vert", "transform.frag")) {
            printf("transform.frag\n");
        }
        //fboSortie.allocate(VarConst::WidthWorld2D, VarConst::HeightWorld2D);
        if(!transformInv.load("passTransform.vert", "transformInv.frag")) {
            printf("transformInv.frag\n");
        }
    }
    void setFboIni(ofFbo (*_fboIni)){
        fboIni = _fboIni;
    }
    void update(SpriteObj *_sprites){
        
        ofMatrix3x3 matrixX , matrixY;
        matrixX.set(_sprites->face->matrix[0][0]->rect.x, _sprites->face->matrix[0][3]->rect.x, _sprites->face->matrix[0][6]->rect.x,
                    _sprites->face->matrix[0][1]->rect.x, _sprites->face->matrix[0][4]->rect.x, _sprites->face->matrix[0][7]->rect.x,
                    _sprites->face->matrix[0][2]->rect.x, _sprites->face->matrix[0][5]->rect.x, _sprites->face->matrix[0][8]->rect.x);
        
        
        matrixY.set(_sprites->face->matrix[0][0]->rect.y, _sprites->face->matrix[0][3]->rect.y, _sprites->face->matrix[0][6]->rect.y,
                    _sprites->face->matrix[0][1]->rect.y, _sprites->face->matrix[0][4]->rect.y, _sprites->face->matrix[0][7]->rect.y,
                    _sprites->face->matrix[0][2]->rect.y, _sprites->face->matrix[0][5]->rect.y, _sprites->face->matrix[0][8]->rect.y);
        
        
        fboTransform.begin();
        ofClear(0,0,0,0);
        _sprites->draw();
        fboTransform.end();
        
        //fboSortie.allocate(fboIni->getWidth(), fboIni->getHeight());
        //fboSortie.begin();
        fboIni[_sprites->layer].begin();
        transformInv.begin();
        transformInv.setUniformTexture("u_texture", fboTransform.getTexture(), 0);
        transformInv.setUniformMatrix3f("matrixX", matrixX);
        transformInv.setUniformMatrix3f("matrixY", matrixY);
        transformInv.setUniformMatrix3f("matrixR", _sprites->face->matrixR[0]);
        
        ofDrawRectangle(ofPoint(0,0), fboIni[0].getWidth(), fboIni[0].getHeight());
        transformInv.end();
        fboIni[_sprites->layer].end();
        //fboSortie.end();
    }
    
    ofFbo (*fboIni);
    ofShader transform;
    ofFbo fboTransform;
    ofShader transformInv;
    ofFbo fboSortie;
};
