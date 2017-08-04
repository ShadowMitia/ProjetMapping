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
    ofFileDialogResult result = ofSystemLoadDialog("Load file : Platform");
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
    ofSetColor(ofColor::white);
    path.draw();
    ofSetColor(ofColor::white);
}

void EditorPlatform::update(){
    path.clear();
    path = polyToPath(polyline);
    path.scale(scalePoly, scalePoly);
    path.rotate(rotatPoly, ofVec3f(0,0,1));
    path.translate(translate);
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
            XmlSetting.popTag();
        }
        XmlSetting.popTag();
        XmlSetting.popTag();
        cout << idPolyline << endl;
        polyline.addVertex(polyline[0]);
        path = polyToPath(polyline);
    }
    if (key == '+') {scalePoly= scalePoly + 0.2;cout << translate << endl;}
    if (key == '-') {scalePoly= scalePoly - 0.2;}
    if (key == 'r') {rotatPoly = rotatPoly + 20;}
    if (key == 'i') {importFile();}
}

void EditorPlatform::platformWordExport(vector<Platform*> _platforms){
    XmlPlapformWord.clear();
    XmlPlapformWord.addTag("WordPlatform");
    XmlPlapformWord.pushTag("WordPlatform");
    for (int i = 0; i < _platforms.size(); i++) {
        XmlPlapformWord.addTag("Platform");
        XmlPlapformWord.pushTag("Platform",i);
        for (int j = 0; j  < _platforms[i]->ground.size(); j++) {
            XmlPlapformWord.addTag("point");
            XmlPlapformWord.pushTag("point",j);
            XmlPlapformWord.addValue("X", _platforms[i]->ground[j].x);
            XmlPlapformWord.addValue("Y", _platforms[i]->ground[j].y);
            XmlPlapformWord.popTag();
        }
        XmlPlapformWord.popTag();
    }
    XmlPlapformWord.popTag();
    XmlPlapformWord.save("WordPlatform.xml");
}

vector<ofPolyline> EditorPlatform::platformWordImport(){
    XmlPlapformWord.clear();
    ofFileDialogResult result = ofSystemLoadDialog("Load file : WordPlatform");
    if(result.bSuccess) {
        string path = result.getPath();
        XmlPlapformWord.load(path);
    }
    
    XmlPlapformWord.pushTag("WordPlatform");
    int nbPlatform = XmlPlapformWord.getNumTags("Platform");
    vector<ofPolyline> _Platform(nbPlatform);
    
    for (int i = 0; i < nbPlatform; i++) {
        XmlPlapformWord.pushTag("Platform",i);
        ofPolyline line;
        int nbPoint = XmlPlapformWord.getNumTags("point");
        for (int j = 0; j < nbPoint; j++) {
            XmlPlapformWord.pushTag("point",j);
            ofPoint p;
            p.x = XmlPlapformWord.getValue("X", 0);
            p.y = XmlPlapformWord.getValue("Y", 0);
            line.addVertex(p);
            XmlPlapformWord.popTag();
        }
        _Platform[i] = line;
        XmlPlapformWord.popTag();
        
    }
    XmlPlapformWord.popTag();
    
    return _Platform;
    
}



