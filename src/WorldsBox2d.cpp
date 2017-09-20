//
//  WorldsBox2d.cpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 16/07/2017.
//
//

#include "WorldsBox2d.h"
void WorldsBox2d::setup(ofx::LightSystem2D * _lightSystem2D){
        
  lightSystem2D = _lightSystem2D;
    
    world.init();
    world.setGravity(0, VarConst::gravity);
    world.setFPS(60.0);
    //world.createGround(0,0,1000, 600);

    //createBoundsModif(0, 0, 3520, 800); // modif monde ici

    
    
	/*int sizeH = 30;
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::LEFT, 334, 110, 30, sizeH));
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::RIGHT, 1000, 110, 30, sizeH));
	portals.push_back(new Portal(Portal::Orientation::HORIZONTAL, Portal::Direction::RIGHT, 700, 120, 30, sizeH));
    portals[0]->linkTo(portals[1], portals[2]);
	portals[1]->linkTo(portals[0], nullptr);
	portals[2]->linkTo(nullptr, portals[0]);

   // portals[2]->linkTo(portals[0]);
    
	 portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::LEFT, 2319, 320, 30, 160));
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::RIGHT, 80, 320, 30, 160));
    portals[2]->linkTo(portals[3]);
    portals[3]->linkTo(portals[2]);
    
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::RIGHT, 80, 80, 30, 160));
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::LEFT, 719, 80, 30, 160));
    portals[4]->linkTo(portals[5]);
    portals[5]->linkTo(portals[4]);
    
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::RIGHT, 1200, 80, 30, 160));
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::LEFT, 2479, 80, 30, 160));
    portals[6]->linkTo(portals[7]);
    portals[7]->linkTo(portals[6]);
    
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::RIGHT, 800, 80, 30, 80));
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::LEFT, 1119, 80, 30, 80));
    portals[8]->linkTo(portals[9]);
    portals[9]->linkTo(portals[8]);*/
    
    for (unsigned int i = 0; i < 1; i++)
      {
	createAvatar(300, 40);
      }
    //wiimotes.startThread();
    //createAvatar(100, 100);

	for (auto &avatar : avatars)
	{
		teleportables.push_back(&avatar);
	}

    //blocks.emplace_back(world, 600, 500, 100, 100);
    /*
	for (auto &block : blocks)
	{
		teleportables.push_back(&block);
	}
    */
    warterfalls = new Waterfalls(&world);



}
void WorldsBox2d::createCircle(float _x,float _y){
    float r = ofRandom(4, 20);
    circles.push_back(std::make_shared<ofxBox2dCircle>());
    circles.back().get()->setPhysics(0.0, 0.53, 0.1);
    circles.back().get()->setup(world.getWorld(), _x, _y, r);
}
void WorldsBox2d::draw(){
    
  for (auto &portal : portals) 
  {
		portal->draw();
  }

  for (auto &platform : platforms) 
  {
    ofSetHexColor(0xFF0000);
    if (platform->shape->bVisible) 
	{
      platform->ground.draw();
    }
  }

  for (int i = 0; i < circles.size(); i++) {
    ofFill();
    ofSetHexColor(0xf6c738);
    circles[i].get()->draw();
  }
    
    
  for (auto &block : blocks)
    {
      ofSetHexColor(0xFFFFF);
      block->draw();
    }

    for (auto &avatar : avatars) {
    ofSetHexColor(0x00FF00);
    avatar.draw();
  }

    warterfalls->draw();
    //world.draw();

}
void WorldsBox2d::createAvatar(int x, int y){
  static int id = 0;
  avatars.emplace_back(id, &world, lightSystem2D);
    avatars.back().polygon.setData(new typeBox2d);
    typeBox2d *sd  = (typeBox2d*) avatars.back().polygon.getData();
    sd->type = typeBox2d::Type::AVATAR;
    avatars.back().setPosition(x, y);
}

void WorldsBox2d::update(){
    world.update();
    
    for (int i = 0; i< portals.size(); i++) {
        portals[i]->update(teleportables);
    }
    
    for (int j = 0; j < avatars.size(); j++)
    {
      //avatars[j].checkJoystickInputs();
        avatars[j].presUpdate();
        
        for (int i = 0; i< ladders.size(); i++) {
            if (ladders[i]->inside(&avatars[j])) {
                avatars[j].modeDeplace = Deplacement::LADDER;
            }
            else
            {
                avatars[j].modeDeplace = Deplacement::PLATFORM;
            }
            
        }
      avatars[j].update();
    }
   
  for (auto &block : blocks)
    {
      block->update();
    }

    //warterfalls->update();
}
void WorldsBox2d::createPlatform(ofPolyline _polyline){
    
    Platform *edge = new Platform;
    edge->create(world.getWorld(), _polyline, lightSystem2D);
    platforms.push_back(edge);

}
void WorldsBox2d::createLadder(ofPolyline _polyline){
    
    Ladder *edge = new Ladder(_polyline);
    ladders.push_back(edge);
    
}
void WorldsBox2d::createPortal(){
    //Portal *plat = new Portal( Portal::Orientation::HORIZONTAL, 50, 525, 35, 75 );
    //portals.push_back(plat);
}

void WorldsBox2d::createBox(ofPolyline _polyline)
{
  ObjectBlock* block = new ObjectBlock(world.getWorld(), _polyline);
  blocks.push_back(block);
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
