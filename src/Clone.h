//
//  Clone.hpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 05/01/2018.
//
//

#pragma once
#include "ofMain.h"
#include "ofxBox2d.h"
#include "Teleportable.h"
#include "PhysicalizedElement.h"
//#include "Portal.h"
class Portal;

class CloneBox2d {
public:
    
    CloneBox2d(PhysicalizedElement* _objSource, Portal* _portalSource, Portal* _portalDestination);
    
    void update();
    

private:
    ofxBox2dPolygon polygon;
    Teleportable* objSource;
    Portal* portalSource = nullptr;
    Portal* portalDestination = nullptr;
    
};