//
//  EditerPlatform.cpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 02/08/2017.
//
//

#include "EditorPlatform.h"

void EditorPlatform::importFile(){
    XmlSetting.load("platform.xml");
    idPolyline = 0;
}

void EditorPlatform::selectPolyline(){
    XmlSetting.pushTag("polylines");
    idPolyline = (idPolyline + 1) % XmlSetting.getNumTags("position");
    XmlSetting.pushTag("position", idPolyline);
    polyline.clear();
    int pt = XmlSetting.getNumTags("point");
    for (int i =0; i<pt; i++) {
        ofPoint point;
        point.x = XmlSetting.getValue("X", i);
        point.y = XmlSetting.getValue("Y", i);
        polyline.addVertex(point);
    }
    polyline.close();
}

void EditorPlatform::draw(){
    ofSetColor(ofColor::blue);
    polyline.draw();
    ofSetColor(ofColor::white);
}
