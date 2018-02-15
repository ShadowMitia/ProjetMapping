//
//  WorldsBox2d.cpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 16/07/2017.
//
//

#include "WorldsBox2d.h"
#include "utils.h"
#include <cstdlib>
#include <iostream>


std::vector<Portal*> generatePortals(std::vector<std::vector<std::string>> const& parameters, WorldsBox2d* world,Face *input){
  std::vector<Portal*> portals;

  for (std::size_t i = 0; i < parameters.size(); ++i)
    {
      if (parameters[i][4].empty() && parameters[i][5].empty())
	{
	  continue;
	}

      float x = std::atof(parameters[i][4].c_str());
      float y = std::atof(parameters[i][5].c_str());
      float w = std::atof(parameters[i][6].c_str());
      float h = std::atof(parameters[i][7].c_str());

      std::vector<std::tuple<std::string, ConditionOutput>> conditions = {
	{"left", ConditionOutput::VerticalLeft},
	{"right", ConditionOutput::VerticalRight},
	{"top", ConditionOutput::HorizontalTop},
	{"down", ConditionOutput::HorizontalDown},
	{"cornertopleft", ConditionOutput::CornerTopLeft},
	{"cornertopright", ConditionOutput::CornerTopRight},
	{"cornerdownleft", ConditionOutput::CornerDownLeft},
	{"cornerdownright", ConditionOutput::CornerDownRight},
      };

      bool found = false;
      ConditionOutput co = ConditionOutput::VerticalLeft;
      for (auto condition : conditions)
	{
	  if (std::get<0>(condition) == ofToLower(parameters[i][3]))
	    {
	      co = std::get<1>(condition);
	      found = true;
	      break;
	    }
	}

      if (!found)
	{
	  std::cout << "Invalid condition output: " << parameters[i][3] << " for id: " << i << '\n';
	}

      std::vector<std::tuple<std::string, Deplacement>> deplacements = {
	{"platform", Deplacement::PLATFORM},
	{"top", Deplacement::TOP},
	{"down", Deplacement::DOWN},
	{"left", Deplacement::LEFT},
	{"right", Deplacement::RIGHT},
      };

      Deplacement d = Deplacement::PLATFORM;

      found = false;
      for (auto condition : deplacements)
	{
	  if (std::get<0>(condition) == ofToLower(parameters[i][10]))
	    {
	      d = std::get<1>(condition);
	      found = true;
	      break;
	    }
	}

      if (!found)
	{
	  std::cout << "Invalid deplacement: " << parameters[i][10] << " for id: " << i << '\n';
	}

    int idFace = std::atoi(parameters[i][11].c_str());
        //cout << "salut  "<< idFace << endl;
      portals.push_back(new Portal(ofRectangle(x, y, w, h), world, d, co, &input[idFace]));
    }

  for (std::size_t i = 0; i < portals.size(); ++i)
      {
	int index1 = std::atoi(parameters[i][8].c_str());
	int index2 = std::atoi(parameters[i][9].c_str());
	Portal* indexPortal1 = (index1 == -1) ? nullptr : portals[index1];
	Portal* indexPortal2 = (index2 == -1) ? nullptr : portals[index2];
	portals[i]->linke(indexPortal1, indexPortal2);
      }

  return portals;
}

void WorldsBox2d::setup(){
    
    world.init();
    world.setGravity(0, VarConst::gravity);
    world.setFPS(60.0);
    warterfalls = new Waterfalls(&world);
    
}
void WorldsBox2d::draw(){
    
    
    
    for (auto &portal : porportal)
    {
        portal->draw();
    }
    
    for (auto &platform : platforms)
    {
        ofSetHexColor(0xFF0000);
        //platform->ground.draw();
    }
    for (auto &avatar : avatars) {
        avatar->draw();
        //cout << avatar->polygon.getPosition() << endl;
    }
    for (auto &clone : clones) {
        clone->draw();
    }
    
    for (auto &ladder : ladders) {
        ladder->draw();
    }
    for (auto &block : blocks){
        block->draw();
    }
    
    for (auto &mroom : Mushrooms){
        mroom->draw();
    }
    //ladders[0]->draw();
    //warterfalls->draw();
    world.draw();
    
}
void WorldsBox2d::createAvatar(AvatarDef* _avatarDef){
    Avatar * avatar = new Avatar(_avatarDef);
    avatar->setPosition(_avatarDef->positionInit);
    avatars.push_back(avatar);
}

void WorldsBox2d::createPickUp(ObjPickupDef *_objPickupDef){
    ObjPickup * pkup = new ObjPickup(_objPickupDef);
    pkup->setPosition(_objPickupDef->positionInit);
    pickups.push_back(pkup);
    
}
void WorldsBox2d::update(){

    world.update();
    

    // delect clone
    // ne pas touché
    for (int i = 0; i< clones.size(); ++i) {
        if (clones[i]->statut>1) {
            // téléportation
            delete clones[i];
            clones.erase(clones.begin()+i);
            --i;
        }
        else{
	  clones[i]->update();
	} // update clone
    }

    
    for (int i = 0; i < avatars.size(); ++i){
        avatars[i]->update();
    }
    
    //warterfalls->update();
}
void WorldsBox2d::createPlatform(ofPolyline polyline){
    Platform* edge = new Platform;
    edge->create(world.getWorld(), polyline);
    platforms.push_back(edge);
}
void WorldsBox2d::createLadder(ofPolyline polyline){
    Ladder* edge = new Ladder();
    edge->create(world.getWorld(), polyline);
    ladders.push_back(edge);
}
void WorldsBox2d::createPortal(Face *input){
    porportal = generatePortals(readCSV(ofToDataPath("portals.csv")), this,input);
}
void WorldsBox2d::creataBlock(ObjBlockDef * _objBlockDef){
    ObjBlock * block = new ObjBlock( _objBlockDef);
    block->setPosition(_objBlockDef->positionInit);
    blocks.push_back(block);
}
void WorldsBox2d::createMushroom(ObjMushroomDef *_objMushroomDef){
    ObjMushroom *mroom = new ObjMushroom(_objMushroomDef);
    mroom->setPosition(_objMushroomDef->positionInit);
    Mushrooms.push_back(mroom);
}
