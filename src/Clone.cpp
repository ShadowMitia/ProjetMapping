//
//  Clone.cpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 05/01/2018.
//
//

#include "Clone.h"
#include "Portal.h"
#include "Teleportable.h"


CloneBox2d::CloneBox2d(PhysicalizedElement* _objSource, Portal* _portalSource, Portal* _portalDestination){
    objSource = static_cast<Teleportable>(_objSource);

    //objSource = _objSource;
    portalSource = _portalSource;
    portalDestination = _portalDestination;
    polygon.addVertices(objSource->polygon.getVertices());
    polygon.setPosition(30, 30);
    polygon.setPhysics(0, 0, 0);
};