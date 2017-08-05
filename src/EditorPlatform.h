//
//  EditerPlatform.hpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 02/08/2017.
//
//

#pragma once
#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "Platform.h"
#include "Portal.h"

class EditorPlatform{
    
public:
    
    ofPolyline              polyline, polylineFinal;
    ofPath                  path;
    ofxXmlSettings          XmlSetting;
    ofxXmlSettings          XmlPlapformWord;
    ofxXmlSettings          XmlPortal;
    int                     idPolyline;
    float                   scalePoly,rotatPoly;
    ofPoint                 translate;
    void importFile();
    void selectPolyline();
    void draw();
    void update();
    void keyPressed(int key);
    ofPolyline getPoly(){ return polylineFinal; };
    void mouseMoved(int _x, int _y){
        translate = ofPoint(_x,_y);
    }
    
    void platformWordExport(vector<Platform*> _platforms);
    vector<ofPolyline> platformWordImport();
    vector<Portal*>    portalImport( ofxBox2d * _world );
};