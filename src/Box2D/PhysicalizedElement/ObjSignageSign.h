//
//  ObjSignageSign.hpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 29/03/2018.
//
//


#pragma once
#include "ofMain.h"
#include "Constant.h"
#include "PhysicalizedElement.h"

class ObjSignageSign: public PhysicalizedElement{
public:
    ObjectGame polygon;
    ObjSignageSign *linkedSign[2];
    
    void setLinkedSign( ObjSignageSign * SignageSign_1, ObjSignageSign * SignageSign_2){
    };
    
};