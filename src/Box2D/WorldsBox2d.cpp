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

#include "PhysicalizedElement/Teleportable/Avatar.h"

std::vector<Portal*> generatePortals(std::vector<std::vector<std::string>> const& parameters, WorldsBox2d* world){
  std::vector<Portal*> portals;

  for (std::size_t i = 0; i < parameters.size(); ++i)
    {
      if (parameters[i][4].empty())
	{
	  continue;
	}
      float x = std::atof(parameters[i][4].c_str());
      float y = std::atof(parameters[i][5].c_str());
      float w = std::atof(parameters[i][6].c_str());
      float h = std::atof(parameters[i][7].c_str());

      ConditionOutput co = ConditionOutput::VerticalLeft;
      if ("left" == parameters[i][3])
	{
	  co = ConditionOutput::VerticalLeft;
	}
      else if ("right" == parameters[i][3])
	{
	   co = ConditionOutput::VerticalRight;
	}
      else if ("down" == parameters[i][3])
	{
	  co = ConditionOutput::HorizontalDown;
	}
      else if ("top" == parameters[i][3])
	{
	  co = ConditionOutput::HorizontalTop;
	}
      else
	{
	  std::cout << "Invalid condition output: " << parameters[i][3] << " for id: " << i << '\n';
	}

      Deplacement d = Deplacement::PLATFORM;
      if ("PLATFORM" == parameters[i][10])
	{
	  d = Deplacement::PLATFORM;
	}
      else if ("TOP" == parameters[i][10])
	{
	  d = Deplacement::TOP;
	}
      else if ("DOWN" == parameters[i][10])
	{
	  d = Deplacement::DOWN;
	}
      else if ("LEFT" == parameters[i][10])
	{
	  d = Deplacement::LEFT;
	}
      else if ("RIGHT" == parameters[i][10])
	{
	  d = Deplacement::RIGHT;
	}
      else
	{
	  std::cout << "Invalid deplacement: " << parameters[i][10] << " for id: " << i << '\n';
	}
      portals.push_back(new Portal(ofRectangle(x, y, w, h), world, d, co));
    }

  for (std::size_t i = 0; i < parameters.size(); ++i)
      {
	if (parameters[i][4].empty())
	{
	  continue;
	}
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
    
    createAvatar( 100 , 300 );
    // 48, 208(-1), 256 et 416(-1)
    
    porportal = generatePortals(readCSV(ofToDataPath("portals.csv")), this);

    for (auto &avatar : avatars)
    {
        teleportables.push_back(avatar);
    }
    
    warterfalls = new Waterfalls(&world);
    
}
void WorldsBox2d::draw(){
    
    
    
    //porportal[0]->draw();
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
    //warterfalls->draw();
    world.draw();
    
}
void WorldsBox2d::createAvatar(int x, int y){
    Avatar * avatar = new Avatar(world.getWorld());
    avatar->setPosition(x, y);
    avatars.push_back(avatar);
}
void WorldsBox2d::update(Shift (*input)[4]){

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

    for (std::size_t j = 0; j < avatars.size(); j++)
    {
        //avatars[j]->presUpdate();
        
        avatars[j]->update(input[j]);
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
void WorldsBox2d::createPortal(){
    //Portal *plat = new Portal( Portal::Orientation::HORIZONTAL, 50, 525, 35, 75 );
    //portals.push_back(plat);
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
/// attention code deguelas ///
void WorldsBox2d::importPortal(){
    
}
