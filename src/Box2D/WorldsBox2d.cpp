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
    
    
    
    //createBoundsModif(0, 0, 3520, 800); // modif monde ici
    
    //importPortal();

    // 48, 208(-1), 256 et 416(-1)
    //creataBlock(170, 300);

    
/*
     ofRectangle rec = ofRectangle(0, 0, 5, 5);
     rec.setFromCenter(0, 0, 5, 5);
     Portal *temp;
     temp = new Portal(ofRectangle(48 - 2, 48 - 2, 3, 159 + 7), this,Deplacement::PLATFORM,ConditionOutput::VerticalLeft);
     porportal.push_back(temp);
     temp = new Portal(ofRectangle(207 + 1, 48 - 2, 3, 159 + 7), this,Deplacement::PLATFORM,ConditionOutput::VerticalRight);
     porportal.push_back(temp);
     temp = new Portal(ofRectangle(256 - 2, 48 - 2, 3, 159 + 7), this,Deplacement::PLATFORM,ConditionOutput::VerticalLeft);
     porportal.push_back(temp);
     temp = new Portal(ofRectangle(415 + 1 , 48 - 2, 3, 159 + 7), this,Deplacement::PLATFORM,ConditionOutput::VerticalRight);
     porportal.push_back(temp);
     
     temp = new Portal(ofRectangle(48 - 2, 256 - 2, 3, 159 + 7), this,Deplacement::PLATFORM,ConditionOutput::VerticalLeft);
     porportal.push_back(temp);
     temp = new Portal(ofRectangle(207 + 1, 256 - 2, 3, 159 + 7), this,Deplacement::PLATFORM,ConditionOutput::VerticalRight);
     porportal.push_back(temp);
     temp = new Portal(ofRectangle(256 - 2, 256 - 2, 3, 159 + 7), this,Deplacement::PLATFORM,ConditionOutput::VerticalLeft);
     porportal.push_back(temp);
     temp = new Portal(ofRectangle(415 + 1, 256 - 2, 3, 159 + 7), this,Deplacement::PLATFORM,ConditionOutput::VerticalRight);
     porportal.push_back(temp);
     
     temp = new Portal(ofRectangle(48 - 2, 208 + 2, 159 + 7, 3), this,Deplacement::PLATFORM,ConditionOutput::HorizontalDown);
     porportal.push_back(temp);
     temp = new Portal(ofRectangle(256 - 2, 208 + 2, 159 + 7, 3), this,Deplacement::PLATFORM,ConditionOutput::HorizontalDown);
     porportal.push_back(temp);
     
     temp = new Portal(ofRectangle(48 - 2, 256 - 2, 159 + 7, 3), this,Deplacement::PLATFORM,ConditionOutput::HorizontalTop);
     porportal.push_back(temp);
     temp = new Portal(ofRectangle(256 - 2, 256 - 2, 159 + 7, 3), this,Deplacement::PLATFORM,ConditionOutput::HorizontalTop);
     porportal.push_back(temp);
    
    temp = new Portal(ofRectangle(207 + 1, 256 - 2, 3, 3), this,Deplacement::PLATFORM,ConditionOutput::CornerTopRight);
    porportal.push_back(temp);
    temp = new Portal(ofRectangle(256 - 2, 208 + 1, 3, 3), this,Deplacement::PLATFORM,ConditionOutput::CornerDownLeft);
    porportal.push_back(temp);
    
    
     porportal[0]->linke(porportal[3], nullptr);
     porportal[1]->linke(porportal[2], nullptr);
     porportal[2]->linke(porportal[1], nullptr);
     porportal[3]->linke(porportal[0], nullptr);
     porportal[4]->linke(porportal[7], nullptr);
     porportal[5]->linke(porportal[6], porportal[0]);
     porportal[6]->linke(porportal[5], porportal[3]);
     porportal[7]->linke(porportal[4], nullptr);
     
     porportal[8]->linke(porportal[10], nullptr);
     porportal[9]->linke(porportal[11], porportal[11]);
     porportal[10]->linke(porportal[8], nullptr);
     porportal[11]->linke(porportal[9], nullptr);
    
    porportal[12]->linke(porportal[13], nullptr);
    //porportal[12]->linke(nullptr, nullptr);
    porportal[13]->linke(porportal[12], nullptr);
*/
    
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
    //ladders[0]->draw();
    //warterfalls->draw();
    world.draw();
    
}
void WorldsBox2d::createAvatar(AvatarDef* _avatarDef){
    Avatar * avatar = new Avatar(_avatarDef);
    avatar->setPosition(_avatarDef->positionInit.x, _avatarDef->positionInit.y);
    avatars.push_back(avatar);
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

    for (std::size_t j = 0; j < avatars.size(); j++){
    avatars[j]->presUpdate();

    avatars[j]->update();
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
void WorldsBox2d::createBoundsModif(float x, float y, float w, float h) {
    ofPolyline temp;
    temp.addVertex(ofPoint(x,y));
    temp.addVertex(ofPoint(w,y));
    temp.addVertex(ofPoint(w,h));
    temp.addVertex(ofPoint(x,h));
    temp.addVertex(ofPoint(x,y));
    createPlatform(temp);
}


void WorldsBox2d::creataBlock(int x, int y){
    ObjBlock * block = new ObjBlock(world.getWorld());
    block->setPosition(x, y);
    blocks.push_back(block);
}
