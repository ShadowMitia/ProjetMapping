//
//  Ladder.hpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 21/08/2017.
//
//

#pragma once
#include "ofMain.h"
#include "Constant.h"
#include "Avatar.h"


class Ladder{
public:
    Ladder(int _x, int _y, int _w, int _h );
    Ladder(ofRectangle _box);
    Ladder(ofPolyline _poly);
    ofRectangle ladderBox;

  bool inside(Avatar* _avatar);
};
