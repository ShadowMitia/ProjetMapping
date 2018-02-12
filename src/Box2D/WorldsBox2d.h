//
//  WorldsBox2d.hpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 16/07/2017.
//
//

#pragma once
#include "ofxBox2d.h"
#include "PhysicalizedElement/Teleportable/Avatar.h"
#include "Portal.h"
#include "PhysicalizedElement/PhysicalizedElement.h"
#include "PhysicalizedElement/Platform.h"

#include "Constant.h"
#include "Ladder.h"
#include "Waterfalls.h"
#include "Clone.h"
#include "ObjBlock.h"

#include <vector>
#include "shift.h"

class WorldsBox2d :public ofThread{
public:
    
    ofxBox2d                 world;

    std::vector< Portal *> porportal;
    std::vector< Platform *> platforms;
    std::vector< Ladder *> ladders;
    std::vector< Avatar *> avatars;
    
    std::vector< CloneBox2d *> clones;
    
    std::vector< ObjBlock *> blocks;
    
    
    Waterfalls*               warterfalls;
    
    void setup();
    void draw();
    void update();
    
    void creataBlock( ObjBlockDef * _objBlockDef);
    void createAvatar(AvatarDef* _avatarDef);
    
    void createPlatform(ofPolyline _polyline);
    void createPortal(Face *input);
    void createLadder(ofPolyline _polyline);
    
    void threadedFunction(){
        //update();
    };
};
