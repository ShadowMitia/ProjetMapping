//
//  EditerPlatform.cpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 02/08/2017.
//
//

#include "EditorPlatform.h"

ofPath polyToPath(ofPolyline polyline) {
    ofPath path;
    for (int i = 0; i < polyline.getVertices().size(); i++){
        if ( i == 0 )
            path.moveTo(polyline.getVertices()[i].x,polyline.getVertices()[i].y);
        else
            path.lineTo(polyline.getVertices()[i].x,polyline.getVertices()[i].y);
    }
    path.close();
    return path;
}

void EditorPlatform::importFile(){
    ofFileDialogResult result = ofSystemLoadDialog("Load file");
    if(result.bSuccess) {
        string path = result.getPath();
        XmlSetting.load(path);
    }
    idPolyline = 0;
}

void EditorPlatform::selectPolyline(){
    XmlSetting.pushTag("polylines");
    XmlSetting.pushTag("polyline",idPolyline);
    int nb = XmlSetting.getNumTags("point");
    for (int i = 0; i < nb; i++) {
        XmlSetting.pushTag("point",i);
        ofPoint p;
        p.x = XmlSetting.getValue("X", 0);
        p.y = XmlSetting.getValue("Y", 0);
        polyline.addVertex(p);
        polyline.close();
        XmlSetting.popTag();
    }
    XmlSetting.popTag();
    XmlSetting.popTag();
}



void EditorPlatform::draw(){
    ofSetColor(ofColor::blue);
    polyline.draw();
    ofSetColor(ofColor::white);
}

void EditorPlatform::update(){
    path.clear();
    path = polyToPath(polyline);
    path.scale(scalePoly, scalePoly);
    path.rotate(rotatPoly, ofVec3f(0,0,1));
    path.translate(ofPoint(ofGetMouseX(),ofGetMouseY()));
    polylineFinal = path.getOutline()[0];
}

void EditorPlatform::keyPressed(int key){
    if (key == 's') {
        XmlSetting.pushTag("polylines");
        int polyMax = XmlSetting.getNumTags("polyline");
        idPolyline = (idPolyline + 1) % polyMax ;
        XmlSetting.pushTag("polyline",idPolyline);
        int nb = XmlSetting.getNumTags("point");
        polyline.clear();
        for (int i = 0; i < nb; i++) {
            XmlSetting.pushTag("point",i);
            ofPoint p;
            p.x = XmlSetting.getValue("X", 0);
            p.y = XmlSetting.getValue("Y", 0);
            polyline.addVertex(p);
            polyline.close();
            XmlSetting.popTag();
        }
        XmlSetting.popTag();
        XmlSetting.popTag();
        cout << idPolyline << endl;
        path = polyToPath(polyline);
    }
    if (key == '+') {scalePoly= scalePoly + 0.2;}
    if (key == '-') {scalePoly= scalePoly - 0.2;}
    if (key == 'r') {rotatPoly = rotatPoly + 20;}
    
    
}
