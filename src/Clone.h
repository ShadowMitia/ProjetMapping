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
#include "Portal.h"


class CloneBox2d: public PhysicalizedElement {
public:
    
    CloneBox2d(Teleportable * _objSource);
    ~CloneBox2d();
    
    void update();
    

private:
    
    ofxBox2dPolygon polygon;
    PhysicalizedElement * objSource;
    //Portal * portalSource;
    //Portal * portalDestination;
    
};