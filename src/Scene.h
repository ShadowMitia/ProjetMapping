//
//  Scene.hpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 23/07/2017.
//
//

#pragma once
#include "ofMain.h"
#include "WorldsBox2d.h"


class scene{
public:
    ofFbo FboScene;
    
    void setup(int _w, int _h);
    void update();
    
private:
    
};