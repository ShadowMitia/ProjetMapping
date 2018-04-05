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
#include "ObjPickup.h"
#include "Constant.h"
#include "Ladder.h"
#include "Waterfalls.h"
#include "Clone.h"
#include "ObjBlock.h"
#include "Mushroom.h"
#include <vector>
#include "shift.h"
#include "ObjTrampoline.h"
#include "ObjSignageSign.h"
#include "ObjPlatforMove.h"


class WorldsBox2d :public ofThread{
public:
    
    ofxBox2d                 world;

    std::vector< Portal *> porportal;
    std::vector< Platform *> platforms;
    std::vector< Ladder *> ladders;
    std::vector< Avatar *> avatars;
    
    std::vector< CloneBox2d *> clones;
    
    std::vector<ObjPickup*> pickups;
    std::vector<ObjBlock *> blocks;
    std::vector<ObjMushroom *> Mushrooms;
    std::vector<ObjTrampoline*> trampolines;
    std::vector<ObjPlatforMove*> platforMoves;
    
    
    Waterfalls*               warterfalls;
    
    void setup();
    void draw();
    void update();
    
    void creataBlock( ObjBlockDef * _objBlockDef);
    void creataBlock( ObjTrampolineDef * _objBlockDef);

    void createAvatar(AvatarDef* _avatarDef);
    void createMushroom(ObjMushroomDef* _objMushroomDef);
    void createPickUp(ObjPickupDef* _objPickupDef);
    void createPlatforMove(ObjPlatforMoveDef* _objPlatforMoveDef);
    
    
    void createPlatform(ofPolyline _polyline, uint16 mask);
    void createPortal(Face *input);
    void createLadder(ofPolyline _polyline);

    
    void threadedFunction(){
        //update();
        world.update();
    };
};
