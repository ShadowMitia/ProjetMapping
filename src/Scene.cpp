//
//  Scene.cpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 23/07/2017.
//
//

#include "Scene.h"

void scene::setup(int _w, int _h){
    FboScene.allocate(_w, _h);
}
void scene::update(){
    FboScene.clear();
    FboScene.begin();
    
}
