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

class EditorPlatform{
    
public:
    
    ofPolyline              polyline, polylineFinal;
    ofPath                  path;
    ofxXmlSettings          XmlSetting;
    int                     idPolyline;
    float                   scalePoly,rotatPoly;
    void importFile();
    void selectPolyline();
    void draw();
    void update();
    void keyPressed(int key);
    
};