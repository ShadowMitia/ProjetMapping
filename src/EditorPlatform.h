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
    
    ofPolyline              polyline;
    ofxXmlSettings          XmlSetting;
    int                     idPolyline;
    
    void importFile();
    void selectPolyline();
    void draw();
    
};