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

std::vector<Portal*> generatePortals(std::vector<std::vector<std::string>> const& parameters, WorldsBox2d* world)
{
  std::vector<Portal*> portals(parameters.size());
  for (auto params : parameters)
    {
      float x = std::atof(params[3].c_str());
      float y = std::atof(params[4].c_str());
      float w = std::atof(params[5].c_str());
      float h = std::atof(params[6].c_str());
      ConditionOutput co = "verticalleft" == params[7] ?
	ConditionOutput::VerticalLeft : params[7] == "verticalright" ?
	ConditionOutput::VerticalRight : ConditionOutput::Horizontal;
      PortalDirection pd = params[8] == "left" ? PortalDirection::leftDirection : PortalDirection::rightDirection;

      portals.push_back(new Portal(ofRectangle(x, y, w, h), world, pd, co));

      int index1 = std::atoi(params[9].c_str());
      int index2 = std::atoi(params[10].c_str());
      //Portal* indexPortal1 = (index1 != -1) ? &portals[index1] : nullptr;
      //Portal* indexPortal2 = (index2 != -1) ? &portals[index2] : nullptr;
      Portal* portal1 = nullptr;
      Portal* portal2 = nullptr;

      portals.back()->linke(portal1, portal2);

    }

  return portals;
}


void WorldsBox2d::setup(){
    
    
    world.init();
    world.setGravity(0, VarConst::gravity);
    world.setFPS(60.0);
    
    //createBoundsModif(0, 0, 3520, 800); // modif monde ici
    
    //importPortal();
    
    createAvatar(100, 100);
    // 48, 208(-1), 256 et 416(-1)
    /*
    Portal *temp;
    temp = new Portal(ofRectangle(48, 48, 2, 159), this,PortalDirection::leftDirection,ConditionOutput::VerticalLeft);
    porportal.push_back(temp);
    temp = new Portal(ofRectangle(206, 48, 2, 159), this,PortalDirection::rightDirection,ConditionOutput::VerticalRight);
    porportal.push_back(temp);
    temp = new Portal(ofRectangle(256, 48, 2, 159), this,PortalDirection::leftDirection,ConditionOutput::VerticalLeft);
    porportal.push_back(temp);
    temp = new Portal(ofRectangle(415, 48, 2, 159), this,PortalDirection::rightDirection,ConditionOutput::VerticalRight);
    porportal.push_back(temp);
    
    temp = new Portal(ofRectangle(48, 256, 2, 159), this,PortalDirection::leftDirection,ConditionOutput::VerticalLeft);
    porportal.push_back(temp);
    temp = new Portal(ofRectangle(206, 256, 2, 159), this,PortalDirection::rightDirection,ConditionOutput::VerticalRight);
    porportal.push_back(temp);
    temp = new Portal(ofRectangle(255, 256, 2, 159), this,PortalDirection::leftDirection,ConditionOutput::VerticalLeft);
    porportal.push_back(temp);
    temp = new Portal(ofRectangle(416, 256, 2, 159), this,PortalDirection::rightDirection,ConditionOutput::VerticalRight);
    porportal.push_back(temp);
    
    
    porportal[0]->linke(porportal[3], nullptr);
    porportal[1]->linke(porportal[2], nullptr);
    porportal[2]->linke(porportal[1], nullptr);
    porportal[3]->linke(porportal[0], nullptr);
    porportal[4]->linke(porportal[7], nullptr);
    porportal[5]->linke(porportal[6], nullptr);
    porportal[6]->linke(porportal[5], nullptr);
    porportal[7]->linke(porportal[4], nullptr);
    */

    porportal = generatePortals(readCSV("portals.csv"), this);

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
        else{clones[i]->update();} // update clone
    }

    for (std::size_t j = 0; j < avatars.size(); j++)
    {
        //avatars[j]->presUpdate();
        
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
