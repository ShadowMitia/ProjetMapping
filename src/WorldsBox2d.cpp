//
//  WorldsBox2d.cpp
//  ProjetMapping
//
//  Created by FatDazz_mac on 16/07/2017.
//
//

#include "WorldsBox2d.h"
void WorldsBox2d::setup(){
  world.init();
  world.setGravity(0, VarConst::gravity);
  world.setFPS(60.0);

  //createBoundsModif(0, 0, 3520, 800); // modif monde ici

  importPortal();

  createAvatar(1300, 500);
  //createAvatar(1200, 700);

  for (auto &avatar : avatars)
    {
      teleportables.push_back(avatar);
    }

  for (auto &pickup : pickups)
    {
      teleportables.push_back(pickup);
    }

  for (auto &block : blocks)
    {
      teleportables.push_back(block);
    }

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

  for (auto &portal : perspectivePortals)
    {
      portal->draw();
    }

  for (auto &platform : platforms)
    {
      ofSetHexColor(0xFF0000);
      platform->ground.draw();
    }

  for (std::size_t i = 0; i < circles.size(); i++) {
    ofFill();
    ofSetHexColor(0xf6c738);
    circles[i].get()->draw();
  }

  for (auto &block : blocks)
    {
      ofSetHexColor(0xFFFFF);
      block->draw();
    }

  for (auto& pickup : pickups)
    {
      ofSetHexColor(0x00FF00);
      pickup->draw();
    }

  for (auto &avatar : avatars) {
    ofSetHexColor(0x00FF00);
    avatar->draw();
  }

  warterfalls->draw();
  //world.draw();

}

void WorldsBox2d::createAvatar(int x, int y){
  Avatar * avatar = new Avatar(world.getWorld());
  avatar->setPosition(x, y);
  avatars.push_back(avatar);
}

void WorldsBox2d::update()
{
  // supprimes les pickups collectés et les enleves de box2d et de la liste des pickups
  pickups.erase(std::remove_if(pickups.begin(), pickups.end(), [&](auto& p){ bool res = p->isCollected(); if (res) { std::remove(teleportables.begin(), teleportables.end(), p); world.getWorld()->DestroyBody(p->pickUp.body);} return res; }), pickups.end());

  world.update();

  for (auto &block : blocks)
    {
      block->update();
    }

  for (auto& pickup : pickups)
    {
      pickup->update();
    }


  for (std::size_t j = 0; j < avatars.size(); j++)
    {
      avatars[j]->processPerspectivePortals(perspectivePortals);
      avatars[j]->presUpdate();

      avatars[j]->modeDeplace = Deplacement::PLATFORM;
      for (std::size_t i = 0; i < ladders.size(); i++) {
	if (ladders[i]->inside(avatars[j]))
	  {
	    avatars[j]->modeDeplace = Deplacement::LADDER;
	  }
	// else
	//   {
	//
	//   }
      }
      avatars[j]->update();
    }

  for (auto& pportal : perspectivePortals)
    {
      pportal->update(teleportables);
    }

  for (auto& portal : portals)
    {
      portal->update(teleportables);
    }

  //warterfalls->update();
}

void WorldsBox2d::createPlatform(ofPolyline polyline)
{
  Platform* edge = new Platform;
  edge->create(world.getWorld(), polyline);
  platforms.push_back(edge);
}

void WorldsBox2d::createLadder(ofPolyline polyline)
{
  Ladder* edge = new Ladder(polyline);
  ladders.push_back(edge);
}

void WorldsBox2d::createPortal(){
  //Portal *plat = new Portal( Portal::Orientation::HORIZONTAL, 50, 525, 35, 75 );
  //portals.push_back(plat);
}

void WorldsBox2d::createBox(ofPolyline polyline)
{
  ObjectBlock* block = new ObjectBlock(world.getWorld(), polyline);
  blocks.push_back(block);
}

void WorldsBox2d::createPickup(ofPolyline polyline)
{
  PickUp* pickup = new PickUp(world.getWorld(), polyline);
  pickups.push_back(pickup);
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

// attention code deguelas 
void WorldsBox2d::importPortal(){
  constexpr const int sizeH = 160;
  constexpr const int sizeW = 3;

  /*
    portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Left, ofRectangle(1560, 600, sizeW, sizeH)));
    portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Right, ofRectangle(1800, 600, sizeW, sizeH)));
    portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, ofRectangle(1360, 650, sizeW, sizeH)));
    portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Right, ofRectangle(1560, 650, sizeW, sizeH)));
    portals.push_back(new PerspectivePortal(Orientation::Vertical, PortalDirection::Left, ofRectangle(1500, 600, sizeW, sizeH)));
    perspectivePortals.push_back(static_cast<PerspectivePortal*>(portals.back()));

    portals[0]->linkTo(portals[1]);
    portals[1]->linkTo(portals[0]);
    portals[2]->linkTo(portals[3]);
    portals[3]->linkTo(portals[2]);

    portals[4]->linkTo(portals[0]);
  */

  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, 80, 80, sizeW, sizeH));// portal:0
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, 240, 80, sizeW, sizeH));// portal:1
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, 400, 80, sizeW, sizeH));// portal:2
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, 560, 80, sizeW, sizeH));// portal:3
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, 800, 80, sizeW, sizeH / 2));// portal:4
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, 880, 80, sizeW, sizeH / 2));// portal:5
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, 960, 80, sizeW, sizeH / 2));// portal:6
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, 1040, 80, sizeW, sizeH / 2));// portal:7
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, 1200, 80, sizeW, sizeH));// portal:8
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, 1360, 80, sizeW, sizeH));// portal:9
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, 1520, 80, sizeW, sizeH));// portal:10
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, 1680, 80, sizeW, sizeH / 2));// portal:11
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, 2000, 80, sizeW, sizeH));// portal:12
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, 2160, 80, sizeW, sizeH));// portal:13
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, 2320, 80, sizeW, sizeH));// portal:14
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, 2560, 80, sizeW, sizeH));// portal:15
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, 2800, 80, sizeW, sizeH));// portal:16
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, 3040, 80, sizeW, sizeH));// portal:17
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, 3280, 80, sizeW, sizeH / 4));// portal:18
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Left, 80, 80, sizeW, sizeH));// portal:19
  portals.push_back(new EmptyPortal(Orientation::Vertical, PortalDirection::Right, 359, 80, sizeW, sizeH / 2));// portal:20
  portals.push_back(new PerspectivePortal(Orientation::Vertical, PortalDirection::Left, 560, 80, sizeW, sizeH / 2));// portal:21
  perspectivePortals.push_back(static_cast<PerspectivePortal*>(portals.back()));
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Right, 719, 80, sizeW, sizeH));// portal:22
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Left, 800, 80, sizeW, sizeH / 2));// portal:23
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Left, 880, 80, sizeW, sizeH / 2));// portal:24
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Right, 1119, 80, sizeW, sizeH / 2));// portal:25
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, 3320, 80, sizeW, sizeH / 4));// portal:26
  portals.push_back(new PerspectivePortal(Orientation::Horizontal, PortalDirection::Right, 879, 159, sizeW, sizeH / 4));// portal:27
  perspectivePortals.push_back(static_cast<PerspectivePortal*>(portals.back()));
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Right, 3280, 199, sizeW, sizeH / 4));// portal:28
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Left, 3280, 120, sizeW, sizeH / 4));// portal:29
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Left, 1200, 80, sizeW, sizeH));// portal:30
  portals.push_back(new PerspectivePortal(Orientation::Vertical, PortalDirection::Right, 1679, 80, sizeW, sizeH));// portal:31
  perspectivePortals.push_back(static_cast<PerspectivePortal*>(portals.back()));
  portals.push_back(new PerspectivePortal(Orientation::Vertical, PortalDirection::Left, 2160, 80, sizeW, sizeH));// portal:32
  perspectivePortals.push_back(static_cast<PerspectivePortal*>(portals.back()));
  portals.push_back(new PerspectivePortal(Orientation::Vertical, PortalDirection::Right, 2479, 80, sizeW, sizeH));// portal:33
  perspectivePortals.push_back(static_cast<PerspectivePortal*>(portals.back()));
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Left, 2560, 80, sizeW, sizeH));// portal:34
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Right, 2719, 80, sizeW, sizeH));// portal:35
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Left, 2800, 80, sizeW, sizeH));// portal:36
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Right, 2959, 80, sizeW, sizeH));// portal:37
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Left, 3040, 80, sizeW, sizeH));// portal:38
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Right, 3199, 80, sizeW, sizeH));// portal:39
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Left, 3280, 80, sizeW, sizeH / 4));// portal:40
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Right, 3359, 80, sizeW, sizeH / 4));// portal:41
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Right, 3280, 159, sizeW, sizeH / 4));// portal:42
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Right, 80, 239, sizeW, sizeH));// portal:43
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Right, 240, 239, sizeW, sizeH));// portal:44
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Right, 400, 239, sizeW, sizeH));// portal:45
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Right, 560, 239, sizeW, sizeH));// portal:46
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Right, 2560, 239, sizeW, sizeH));// portal:47
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Right, 2800, 239, sizeW, sizeH / 2));// portal:48
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Left, 3040, 240, sizeW, sizeH));// portal:49
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Right, 3199, 240, sizeW, sizeH));// portal:50
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, 3280, 240, sizeW, sizeH / 2));// portal:51
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Left, 3280, 240, sizeW, sizeH / 2));// portal:52
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Right, 3280, 319, sizeW, sizeH / 2));// portal:53
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Right, 3360, 240, sizeW, sizeH / 2));// portal:54
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, 80, 320, sizeW, sizeH));// portal:55
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, 240, 320, sizeW, sizeH));// portal:56
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, 400, 320, sizeW, sizeH));// portal:57
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, 560, 320, sizeW, sizeH));// portal:58
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, 720, 320, sizeW, sizeH));// portal:59
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, 880, 320, sizeW, sizeH / 2));// portal:60
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, 1040, 320, sizeW, sizeH));// portal:61
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, 1200, 320, sizeW, sizeH));// portal:62
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, 1360, 320, sizeW, sizeH / 2));// portal:63
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, 1520, 320, sizeW, sizeH / 2));// portal:64
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, 1680, 320, sizeW, sizeH));// portal:65
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, 1840, 320, sizeW, sizeH));// portal:66
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, 2000, 320, sizeW, sizeH));// portal:67
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, 2160, 320, sizeW, sizeH));// portal:68
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, 2560, 320, sizeW, sizeH));// portal:69
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, 2800, 320, sizeW, sizeH / 2));// portal:70
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Left, 80, 320, sizeW, sizeH));// portal:71
  portals.push_back(new PerspectivePortal(Orientation::Vertical, PortalDirection::Right, 239, 320, sizeW, sizeH));// portal:72
  perspectivePortals.push_back(static_cast<PerspectivePortal*>(portals.back()));
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Right, 3439, 640, sizeW, sizeH / 2));// portal:73
  portals.push_back(new EmptyPortal(Orientation::Vertical, PortalDirection::Right, 399, 320, sizeW, sizeH));// portal:74
  portals.push_back(new EmptyPortal(Orientation::Vertical, PortalDirection::Left, 400, 320, sizeW, sizeH));// portal:75
  portals.push_back(new PerspectivePortal(Orientation::Vertical, PortalDirection::Right, 719, 320, sizeW, sizeH));// portal:76
  perspectivePortals.push_back(static_cast<PerspectivePortal*>(portals.back()));
  portals.push_back(new PerspectivePortal(Orientation::Vertical, PortalDirection::Left, 720, 320, sizeW, sizeH));// portal:77
  perspectivePortals.push_back(static_cast<PerspectivePortal*>(portals.back()));
  portals.push_back(new EmptyPortal(Orientation::Vertical, PortalDirection::Right, 879, 320, sizeW, sizeH));// portal:78
  portals.push_back(new EmptyPortal(Orientation::Vertical, PortalDirection::Left, 880, 320, sizeW, sizeH));// portal:79
  portals.push_back(new PerspectivePortal(Orientation::Vertical, PortalDirection::Left, 1040, 320, sizeW, sizeH));// portal:80
  perspectivePortals.push_back(static_cast<PerspectivePortal*>(portals.back()));
  portals.push_back(new PerspectivePortal(Orientation::Vertical, PortalDirection::Right, 1359, 320, sizeW, sizeH / 2));// portal:81
  perspectivePortals.push_back(static_cast<PerspectivePortal*>(portals.back()));
  portals.push_back(new PerspectivePortal(Orientation::Vertical, PortalDirection::Right, 1359, 400, sizeW, sizeH / 2));// portal:82
  perspectivePortals.push_back(static_cast<PerspectivePortal*>(portals.back()));
  portals.push_back(new EmptyPortal(Orientation::Vertical, PortalDirection::Right, 1439, 400, sizeW, sizeH / 2));// portal:83
  portals.push_back(new EmptyPortal(Orientation::Vertical, PortalDirection::Right, 1519, 320, sizeW, sizeH / 2));// portal:84
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Right, 1440, 399, sizeW, sizeH / 2));// portal:85
  portals.push_back(new EmptyPortal(Orientation::Vertical, PortalDirection::Left, 1440, 400, sizeW, sizeH / 2));// portal:86
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, 1440, 400, sizeW, sizeH / 2));// portal:87
  portals.push_back(new PerspectivePortal(Orientation::Vertical, PortalDirection::Right, 1519, 400, sizeW, sizeH / 2));// portal:88
  perspectivePortals.push_back(static_cast<PerspectivePortal*>(portals.back()));
  portals.push_back(new EmptyPortal(Orientation::Vertical, PortalDirection::Left, 1520, 320, sizeW, sizeH / 2));// portal:89
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Right, 1520, 399, sizeW, sizeH / 2));// portal:90
  portals.push_back(new PerspectivePortal(Orientation::Vertical, PortalDirection::Left, 1520, 400, sizeW, sizeH / 2));// portal:91
  perspectivePortals.push_back(static_cast<PerspectivePortal*>(portals.back()));
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, 1520, 400, sizeW, sizeH / 2));// portal:92
  portals.push_back(new EmptyPortal(Orientation::Vertical, PortalDirection::Right, 1599, 400, sizeW, sizeH / 2));// portal:93
  portals.push_back(new PerspectivePortal(Orientation::Vertical, PortalDirection::Left, 2000, 320, sizeW, sizeH / 2));// portal:94
  perspectivePortals.push_back(static_cast<PerspectivePortal*>(portals.back()));
  portals.push_back(new PerspectivePortal(Orientation::Vertical, PortalDirection::Left, 2000, 400, sizeW, sizeH / 2));// portal:95
  perspectivePortals.push_back(static_cast<PerspectivePortal*>(portals.back()));
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Left, 2560, 320, sizeW, sizeH));// portal:96
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Left, 2719, 320, sizeW, sizeH));// portal:97
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Left, 2800, 320, sizeW, sizeH));// portal:98
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Right, 2959, 320, sizeW, sizeH));// portal:99
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Right, 3040, 399, sizeW, sizeH));// portal:100
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Left, 3280, 400, sizeW, sizeH / 2));// portal:101
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, 3280, 400, sizeW, sizeH / 2));// portal:102
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Right, 3359, 400, sizeW, sizeH / 2));// portal:103
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Right, 80, 479, sizeW, sizeH));// portal:104
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Right, 240, 479, sizeW, sizeH / 2));// portal:105
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Right, 720, 479, sizeW, sizeH));// portal:106
  portals.push_back(new EmptyPortal(Orientation::Horizontal, PortalDirection::Left, 359, 160, sizeW, sizeH / 4));// portal:107
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Right, 1040, 479, sizeW, sizeH));// portal:108
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Right, 1360, 479, sizeW, sizeH / 2));// portal:109
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Right, 1440, 479, sizeW, sizeH / 2));// portal:110
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Right, 1520, 479, sizeW, sizeH / 2));// portal:111
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Right, 1600, 479, sizeW, sizeH / 2));// portal:112
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Right, 2560, 479, sizeW, sizeH));// portal:113
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Right, 2800, 479, sizeW, sizeH ));// portal:114
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Right, 3280, 479, sizeW, sizeH / 2));// portal:115
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, 80, 560, sizeW, sizeH));// portal:116
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, 240, 560, sizeW, sizeH / 2));// portal:117
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, 400, 560, sizeW, sizeH / 2));// portal:118
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, 560, 560, sizeW, sizeH));// portal:119
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, 720, 560, sizeW, sizeH));// portal:120
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, 880, 560, sizeW, sizeH));// portal:121
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, 1040, 560, sizeW, sizeH));// portal:122
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, 1200, 560, sizeW, sizeH));// portal:123
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, 1360, 560, sizeW, sizeH));// portal:124
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, 1520, 560, sizeW, sizeH));// portal:125
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, 1680, 560, sizeW, sizeH / 2));// portal:126
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, 1760, 560, sizeW, sizeH / 2));// portal:127
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, 1840, 560, sizeW, sizeH / 2));// portal:128
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, 2160, 560, sizeW, sizeH));// portal:129
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, 2560, 560, sizeW, sizeH / 2));// portal:130
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, 2800, 560, sizeW, sizeH));// portal:131
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Left, 80, 560, sizeW, sizeH));// portal:132
  portals.push_back(new PerspectivePortal(Orientation::Vertical, PortalDirection::Right, 239, 560, sizeW, sizeH / 2));// portal:133
  perspectivePortals.push_back(static_cast<PerspectivePortal*>(portals.back()));
  portals.push_back(new PerspectivePortal(Orientation::Vertical, PortalDirection::Right, 239, 640, sizeW, sizeH / 2));// portal:134
  perspectivePortals.push_back(static_cast<PerspectivePortal*>(portals.back()));
  portals.push_back(new PerspectivePortal(Orientation::Vertical, PortalDirection::Left, 240, 560, sizeW, sizeH));// portal:135
  perspectivePortals.push_back(static_cast<PerspectivePortal*>(portals.back()));
  portals.push_back(new EmptyPortal(Orientation::Vertical, PortalDirection::Right, 399, 560, sizeW, sizeH / 2));// portal:136
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Right, 319, 639, sizeW, sizeH / 2));// portal:137
  portals.push_back(new EmptyPortal(Orientation::Vertical, PortalDirection::Right, 319, 640, sizeW, sizeH / 2));// portal:138
  portals.push_back(new EmptyPortal(Orientation::Vertical, PortalDirection::Left, 320, 640, sizeW, sizeH / 2));// portal:139
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, 320, 640, sizeW, sizeH / 2));// portal:140
  portals.push_back(new PerspectivePortal(Orientation::Vertical, PortalDirection::Left, 399, 640, sizeW, sizeH / 2));// portal:141
  perspectivePortals.push_back(static_cast<PerspectivePortal*>(portals.back()));
  portals.push_back(new EmptyPortal(Orientation::Vertical, PortalDirection::Left, 400, 560, sizeW, sizeH / 2));// portal:142
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Right, 400, 639, sizeW, sizeH / 2));// portal:143
  portals.push_back(new PerspectivePortal(Orientation::Vertical, PortalDirection::Left, 400, 640, sizeW, sizeH / 2));// portal:144
  perspectivePortals.push_back(static_cast<PerspectivePortal*>(portals.back()));
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, 400, 640, sizeW, sizeH / 2));// portal:145
  portals.push_back(new EmptyPortal(Orientation::Vertical, PortalDirection::Right, 479, 640, sizeW, sizeH / 2));// portal:146
  portals.push_back(new EmptyPortal(Orientation::Vertical, PortalDirection::Left, 480, 640, sizeW, sizeH / 2));// portal:147
  portals.push_back(new PerspectivePortal(Orientation::Vertical, PortalDirection::Right, 559, 560, sizeW, sizeH));// portal:148
  perspectivePortals.push_back(static_cast<PerspectivePortal*>(portals.back()));
  portals.push_back(new PerspectivePortal(Orientation::Vertical, PortalDirection::Left, 560, 560, sizeW, sizeH / 2));// portal:149
  perspectivePortals.push_back(static_cast<PerspectivePortal*>(portals.back()));
  portals.push_back(new EmptyPortal(Orientation::Vertical, PortalDirection::Right, 879, 560, sizeW, sizeH));// portal:150
  portals.push_back(new EmptyPortal(Orientation::Vertical, PortalDirection::Left, 880, 560, sizeW, sizeH));// portal:151
  portals.push_back(new PerspectivePortal(Orientation::Vertical, PortalDirection::Left, 1040, 560, sizeW, sizeH));// portal:152
  perspectivePortals.push_back(static_cast<PerspectivePortal*>(portals.back()));
  portals.push_back(new PerspectivePortal(Orientation::Vertical, PortalDirection::Right, 1359, 560, sizeW, sizeH));// portal:153
  perspectivePortals.push_back(static_cast<PerspectivePortal*>(portals.back()));
  portals.push_back(new EmptyPortal(Orientation::Vertical, PortalDirection::Right, 1519, 560, sizeW, sizeH));// portal:154
  portals.push_back(new EmptyPortal(Orientation::Vertical, PortalDirection::Left, 1520, 560, sizeW, sizeH));// portal:155
  portals.push_back(new PerspectivePortal(Orientation::Vertical, PortalDirection::Left, 1840, 560, sizeW, sizeH));// portal:156
  perspectivePortals.push_back(static_cast<PerspectivePortal*>(portals.back()));
  portals.push_back(new EmptyPortal(Orientation::Vertical, PortalDirection::Right, 1999, 560, sizeW, sizeH));// portal:157
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Right, 2319, 560, sizeW, sizeH));// portal:158
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Left, 2560, 560, sizeW, sizeH));// portal:159
  portals.push_back(new EmptyPortal(Orientation::Vertical, PortalDirection::Right, 2679, 560, sizeW, sizeH / 4));// portal:160
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Right, 2560, 719, sizeW, sizeH));// portal:161
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Left, 2800, 560, sizeW, sizeH));// portal:162
  portals.push_back(new EmptyPortal(Orientation::Horizontal, PortalDirection::Right, 2680, 639, sizeW, sizeH / 4));// portal:163
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Right, 2719, 560, sizeW, sizeH / 2));// portal:164
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Right, 2719, 640, sizeW, sizeH / 2));// portal:165
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Right, 2959, 560, sizeW, sizeH));// portal:166
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Right, 2800, 719, sizeW, sizeH));// portal:167
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Left, 3360, 560, sizeW, sizeH / 2));// portal:168
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, 3280, 640, sizeW, sizeH / 2));// portal:169
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Left, 3280, 640, sizeW, sizeH / 2));// portal:170
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Right, 3439, 560, sizeW, sizeH / 2));// portal:171
  portals.push_back(new EmptyPortal(Orientation::Vertical, PortalDirection::Left, 1600, 400, sizeW, sizeH / 2));// portal:172
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, 3360, 560, sizeW, sizeH / 2));// portal:173
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Right, 3280, 719, sizeW, sizeH / 2));// portal:174
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, 3040, 560, sizeW, sizeH));// portal:175
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Left, 3040, 560, sizeW, sizeH / 2));// portal:176
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Right, 3040, 719, sizeW, sizeH));// portal:177
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Right, 3199, 560, sizeW, sizeH));// portal:178
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Right, 560, 479, sizeW, sizeH));// portal:179
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Right, 1200, 479, sizeW, sizeH));// portal:180
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Right, 1840, 479, sizeW, sizeH));// portal:181
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Right, 2000, 479, sizeW, sizeH));// portal:182
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Right, 2160, 479, sizeW, sizeH));// portal:183
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, 1760, 80, sizeW, sizeH / 2));// portal:184
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Right, 2880, 239, sizeW, sizeH / 2));// portal:185
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, 1440, 320, sizeW, sizeH / 2));// portal:186
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, 1600, 320, sizeW, sizeH / 2));// portal:187
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, 2880, 320, sizeW, sizeH / 2));// portal:188
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Right, 320, 479, sizeW, sizeH / 2));// portal:189
  portals.push_back(new EmptyPortal(Orientation::Vertical, PortalDirection::Right, 2919, 440, sizeW, sizeH / 4));// portal:190
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, 320, 560, sizeW, sizeH / 2));// portal:191
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, 480, 560, sizeW, sizeH / 2));// portal:192
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, 1920, 560, sizeW, sizeH / 2));// portal:193
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, 2640, 560, sizeW, sizeH / 2));// portal:194
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Left, 3040, 640, sizeW, sizeH / 2));// portal:195
  portals.push_back(new PerspectivePortal(Orientation::Vertical, PortalDirection::Left, 560, 560, sizeW, sizeH / 2));// portal:196
  perspectivePortals.push_back(static_cast<PerspectivePortal*>(portals.back()));
  portals.push_back(new EmptyPortal(Orientation::Vertical, PortalDirection::Right, 1079, 80, sizeW, sizeH / 2));// portal:197
  portals.push_back(new EmptyPortal(Orientation::Horizontal, PortalDirection::Right, 2800, 199, sizeW, sizeH / 4));// portal:198
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, 960, 320, sizeW, sizeH / 2));// portal:199
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Right, 2319, 320, sizeW, sizeH));// portal:200
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Right, 880, 479, sizeW, sizeH ));// portal:201
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Right, 3360, 719, sizeW, sizeH / 2));// portal:202
  portals.push_back(new EmptyPortal(Orientation::Vertical, PortalDirection::Left, 2840, 199, sizeW, sizeH / 4));// portal:203
  portals.push_back(new EmptyPortal(Orientation::Vertical, PortalDirection::Left, 3320, 240, sizeW, sizeH / 4));// portal:204
  portals.push_back(new EmptyPortal(Orientation::Horizontal, PortalDirection::Left, 3280, 280, sizeW, sizeH / 4));// portal:205
  portals.push_back(new EmptyPortal(Orientation::Horizontal, PortalDirection::Right, 2920, 439, sizeW, sizeH / 4));// portal:206
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Right, 839, 80, sizeW, sizeH / 4));// portal:207
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Right, 919, 80, sizeW, sizeH / 4));// portal:208
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Right, 999, 80, sizeW, sizeH / 4));// portal:209
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Right, 1079, 80, sizeW, sizeH / 4));// portal:210
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Right, 3399, 80, sizeW, sizeH / 4));// portal:211
  portals.push_back(new PerspectivePortal(Orientation::Horizontal, PortalDirection::Left, 1360, 80, sizeW, sizeH));// portal:212
  perspectivePortals.push_back(static_cast<PerspectivePortal*>(portals.back()));
  portals.push_back(new PerspectivePortal(Orientation::Horizontal, PortalDirection::Left, 2800, 80, sizeW, sizeH));// portal:213
  perspectivePortals.push_back(static_cast<PerspectivePortal*>(portals.back()));
  portals.push_back(new PerspectivePortal(Orientation::Horizontal, PortalDirection::Left, 3040, 80, sizeW, sizeH));// portal:214
  perspectivePortals.push_back(static_cast<PerspectivePortal*>(portals.back()));
  portals.push_back(new PerspectivePortal(Orientation::Horizontal, PortalDirection::Left, 3280, 80, sizeW, sizeH / 4));// portal:215
  perspectivePortals.push_back(static_cast<PerspectivePortal*>(portals.back()));
  portals.push_back(new PerspectivePortal(Orientation::Horizontal, PortalDirection::Left, 3320, 80, sizeW, sizeH / 4));// portal:216
  perspectivePortals.push_back(static_cast<PerspectivePortal*>(portals.back()));
  portals.push_back(new PerspectivePortal(Orientation::Horizontal, PortalDirection::Right, 3280, 199, sizeW, sizeH / 4));// portal:217
  perspectivePortals.push_back(static_cast<PerspectivePortal*>(portals.back()));
  portals.push_back(new PerspectivePortal(Orientation::Vertical, PortalDirection::Left, 3280, 120, sizeW, sizeH / 4));// portal:218
  perspectivePortals.push_back(static_cast<PerspectivePortal*>(portals.back()));
  portals.push_back(new PerspectivePortal(Orientation::Vertical, PortalDirection::Left, 2560, 80, sizeW, sizeH));// portal:219
  perspectivePortals.push_back(static_cast<PerspectivePortal*>(portals.back()));
  portals.push_back(new PerspectivePortal(Orientation::Vertical, PortalDirection::Right, 2719, 80, sizeW, sizeH));// portal:220
  perspectivePortals.push_back(static_cast<PerspectivePortal*>(portals.back()));
  portals.push_back(new PerspectivePortal(Orientation::Vertical, PortalDirection::Left, 2800, 80, sizeW, sizeH));// portal:221
  perspectivePortals.push_back(static_cast<PerspectivePortal*>(portals.back()));
  portals.push_back(new PerspectivePortal(Orientation::Vertical, PortalDirection::Left, 3280, 80, sizeW, sizeH / 4));// portal:222
  perspectivePortals.push_back(static_cast<PerspectivePortal*>(portals.back()));
  portals.push_back(new PerspectivePortal(Orientation::Vertical, PortalDirection::Right, 3359, 80, sizeW, sizeH / 4));// portal:223
  perspectivePortals.push_back(static_cast<PerspectivePortal*>(portals.back()));
  portals.push_back(new PerspectivePortal(Orientation::Horizontal, PortalDirection::Right, 3280, 159, sizeW, sizeH / 4));// portal:224
  perspectivePortals.push_back(static_cast<PerspectivePortal*>(portals.back()));
  portals.push_back(new PerspectivePortal(Orientation::Horizontal, PortalDirection::Right, 2800, 239, sizeW, sizeH / 2));// portal:225
  perspectivePortals.push_back(static_cast<PerspectivePortal*>(portals.back()));
  portals.push_back(new PerspectivePortal(Orientation::Horizontal, PortalDirection::Right, 3280, 319, sizeW, sizeH / 2));// portal:226
  perspectivePortals.push_back(static_cast<PerspectivePortal*>(portals.back()));
  portals.push_back(new PerspectivePortal(Orientation::Vertical, PortalDirection::Right, 3360, 240, sizeW, sizeH / 2));// portal:227
  perspectivePortals.push_back(static_cast<PerspectivePortal*>(portals.back()));
  portals.push_back(new PerspectivePortal(Orientation::Horizontal, PortalDirection::Left, 720, 320, sizeW, sizeH));// portal:228
  perspectivePortals.push_back(static_cast<PerspectivePortal*>(portals.back()));
  portals.push_back(new PerspectivePortal(Orientation::Horizontal, PortalDirection::Left, 2000, 320, sizeW, sizeH));// portal:229
  perspectivePortals.push_back(static_cast<PerspectivePortal*>(portals.back()));
  portals.push_back(new PerspectivePortal(Orientation::Horizontal, PortalDirection::Left, 1440, 400, sizeW, sizeH / 2));// portal:230
  perspectivePortals.push_back(static_cast<PerspectivePortal*>(portals.back()));
  portals.push_back(new PerspectivePortal(Orientation::Horizontal, PortalDirection::Left, 1520, 400, sizeW, sizeH / 2));// portal:231
  perspectivePortals.push_back(static_cast<PerspectivePortal*>(portals.back()));
  portals.push_back(new PerspectivePortal(Orientation::Horizontal, PortalDirection::Left, 80, 560, sizeW, sizeH));// portal:232
  perspectivePortals.push_back(static_cast<PerspectivePortal*>(portals.back()));
  portals.push_back(new PerspectivePortal(Orientation::Horizontal, PortalDirection::Left, 240, 560, sizeW, sizeH / 2));// portal:233
  perspectivePortals.push_back(static_cast<PerspectivePortal*>(portals.back()));
  portals.push_back(new PerspectivePortal(Orientation::Horizontal, PortalDirection::Left, 400, 560, sizeW, sizeH / 2));// portal:234
  perspectivePortals.push_back(static_cast<PerspectivePortal*>(portals.back()));
  portals.push_back(new PerspectivePortal(Orientation::Horizontal, PortalDirection::Left, 560, 560, sizeW, sizeH));// portal:235
  perspectivePortals.push_back(static_cast<PerspectivePortal*>(portals.back()));
  portals.push_back(new PerspectivePortal(Orientation::Horizontal, PortalDirection::Left, 1680, 560, sizeW, sizeH / 2));// portal:236
  perspectivePortals.push_back(static_cast<PerspectivePortal*>(portals.back()));
  portals.push_back(new PerspectivePortal(Orientation::Horizontal, PortalDirection::Left, 1760, 560, sizeW, sizeH / 2));// portal:237
  perspectivePortals.push_back(static_cast<PerspectivePortal*>(portals.back()));
  portals.push_back(new PerspectivePortal(Orientation::Horizontal, PortalDirection::Left, 1840, 560, sizeW, sizeH / 2));// portal:238
  perspectivePortals.push_back(static_cast<PerspectivePortal*>(portals.back()));
  portals.push_back(new PerspectivePortal(Orientation::Horizontal, PortalDirection::Left, 2560, 560, sizeW, sizeH / 2));// portal:239
  perspectivePortals.push_back(static_cast<PerspectivePortal*>(portals.back()));
  portals.push_back(new PerspectivePortal(Orientation::Horizontal, PortalDirection::Left, 320, 640, sizeW, sizeH / 2));// portal:240
  perspectivePortals.push_back(static_cast<PerspectivePortal*>(portals.back()));
  portals.push_back(new PerspectivePortal(Orientation::Horizontal, PortalDirection::Left, 400, 640, sizeW, sizeH / 2));// portal:241
  perspectivePortals.push_back(static_cast<PerspectivePortal*>(portals.back()));
  portals.push_back(new PerspectivePortal(Orientation::Vertical, PortalDirection::Right, 2719, 560, sizeW, sizeH / 2));// portal:242
  perspectivePortals.push_back(static_cast<PerspectivePortal*>(portals.back()));
  portals.push_back(new PerspectivePortal(Orientation::Vertical, PortalDirection::Right, 2719, 640, sizeW, sizeH / 2));// portal:243
  perspectivePortals.push_back(static_cast<PerspectivePortal*>(portals.back()));
  portals.push_back(new PerspectivePortal(Orientation::Horizontal, PortalDirection::Left, 1440, 320, sizeW, sizeH / 2));// portal:244
  perspectivePortals.push_back(static_cast<PerspectivePortal*>(portals.back()));
  portals.push_back(new PerspectivePortal(Orientation::Horizontal, PortalDirection::Left, 2880, 320, sizeW, sizeH / 2));// portal:245
  perspectivePortals.push_back(static_cast<PerspectivePortal*>(portals.back()));
  portals.push_back(new PerspectivePortal(Orientation::Horizontal, PortalDirection::Left, 320, 560, sizeW, sizeH / 2));// portal:246
  perspectivePortals.push_back(static_cast<PerspectivePortal*>(portals.back()));
  portals.push_back(new PerspectivePortal(Orientation::Horizontal, PortalDirection::Left, 480, 560, sizeW, sizeH / 2));// portal:247
  perspectivePortals.push_back(static_cast<PerspectivePortal*>(portals.back()));
  portals.push_back(new PerspectivePortal(Orientation::Horizontal, PortalDirection::Left, 1920, 560, sizeW, sizeH / 2));// portal:248
  perspectivePortals.push_back(static_cast<PerspectivePortal*>(portals.back()));
  portals.push_back(new PerspectivePortal(Orientation::Horizontal, PortalDirection::Left, 2640, 560, sizeW, sizeH / 2));// portal:249
  perspectivePortals.push_back(static_cast<PerspectivePortal*>(portals.back()));
  portals.push_back(new PerspectivePortal(Orientation::Vertical, PortalDirection::Left, 3040, 640, sizeW, sizeH / 2));// portal:250
  perspectivePortals.push_back(static_cast<PerspectivePortal*>(portals.back()));
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Right, 3399, 80, sizeW, sizeH / 4));// portal:251

  //angle; perspective  portals[],nullptr

  portals[0]->linkTo(portals[15]);
  portals[1]->linkTo(portals[34]);
  portals[2]->linkTo(portals[47]);
  portals[3]->linkTo(portals[35]);
  portals[4]->linkTo(portals[26]);
  portals[5]->linkTo(portals[40]);
  portals[6]->linkTo(portals[42]);
  portals[7]->linkTo(portals[28]);
  portals[8]->linkTo(portals[166]);
  portals[9]->linkTo(portals[131]);
  portals[212]->linkTo(portals[104]);
  portals[10]->linkTo(portals[162]);
  portals[11]->linkTo(portals[105]);
  portals[12]->linkTo(portals[181]);
  portals[13]->linkTo(portals[182]);
  portals[14]->linkTo(portals[183]);
  portals[15]->linkTo(portals[0]);
  portals[16]->linkTo(portals[58]);
  portals[213]->linkTo(portals[177]);
  portals[17]->linkTo(portals[55]);
  portals[214]->linkTo(portals[167]);
  portals[18]->linkTo(portals[207]);
  portals[215]->linkTo( portals[206]);
  portals[19]->linkTo(portals[22]);
  portals[21]->linkTo(portals[25]);
  portals[22]->linkTo(portals[19]);
  portals[23]->linkTo(portals[25]);
  portals[24]->linkTo(portals[20]);
  portals[25]->linkTo(portals[23]);
  portals[26]->linkTo(portals[4]);
  portals[216]->linkTo(portals[198]);
  portals[27]->linkTo(portals[107]);
  portals[28]->linkTo(portals[7]);
  portals[217]->linkTo(portals[204]);
  portals[29]->linkTo(portals[208]);
  portals[218]->linkTo(portals[160]);
  portals[30]->linkTo(portals[33]);
  portals[31]->linkTo(portals[135]);
  portals[32]->linkTo(portals[157]);
  portals[33]->linkTo(portals[30]);
  portals[34]->linkTo(portals[1]);
  portals[219]->linkTo(portals[37]);
  portals[35]->linkTo(portals[3]);
  portals[220]->linkTo(portals[49]);
  portals[36]->linkTo(portals[59]);
  portals[221]->linkTo(portals[99]);
  portals[37]->linkTo(portals[44]);
  portals[38]->linkTo(portals[56]);
  portals[39]->linkTo(portals[68]);
  portals[40]->linkTo(portals[5]);
  portals[222]->linkTo(portals[190]);
  portals[41]->linkTo(portals[210]);
  portals[223]->linkTo(portals[203]);
  portals[42]->linkTo(portals[6]);
  portals[224]->linkTo(portals[163]);
  portals[43]->linkTo(portals[177]);
  portals[44]->linkTo(portals[37]);
  portals[45]->linkTo(portals[65]);
  portals[46]->linkTo(portals[49]);
  portals[47]->linkTo(portals[2]);
  portals[48]->linkTo(portals[64]);
  portals[225]->linkTo(portals[51]);
  portals[49]->linkTo(portals[46]);
  portals[50]->linkTo(portals[67]);
  portals[51]->linkTo(portals[90]);
  portals[52]->linkTo(portals[85]);
  portals[53]->linkTo(portals[87]);
  portals[226]->linkTo( portals[169]);
  portals[54]->linkTo(portals[92]);
  portals[227]->linkTo(portals[168]);
  portals[55]->linkTo(portals[17]);
  portals[56]->linkTo(portals[38]);
  portals[57]->linkTo(portals[43]);
  portals[58]->linkTo(portals[16]);
  portals[59]->linkTo(portals[36]);
  portals[228]->linkTo(portals[44]);
  portals[60]->linkTo(portals[130]);
  portals[61]->linkTo(portals[159]);
  portals[62]->linkTo(portals[161]);
  portals[63]->linkTo(portals[165]);
  portals[64]->linkTo(portals[48]);
  portals[65]->linkTo(portals[45]);
  portals[66]->linkTo(portals[100]);
  portals[67]->linkTo(portals[50]);
  portals[229]->linkTo(portals[46]);
  portals[68]->linkTo(portals[39]);
  portals[69]->linkTo(portals[121]);
  portals[70]->linkTo(portals[192]);
  portals[71]->linkTo(portals[200]);
  portals[72]->linkTo(portals[75]);
  portals[73]->linkTo(portals[128]);
  portals[76]->linkTo(portals[79]);
  portals[77]->linkTo(portals[74]);
  portals[80]->linkTo(portals[78]);
  portals[81]->linkTo(portals[84]);
  portals[82]->linkTo(portals[86]);
  portals[85]->linkTo(portals[52]);
  portals[87]->linkTo(portals[53]);
  portals[87]->linkTo(portals[90]);
  portals[88]->linkTo(portals[172]);
  portals[90]->linkTo(portals[51]);
  portals[91]->linkTo(portals[83]);
  portals[92]->linkTo(portals[54]);
  portals[92]->linkTo(portals[85]);
  portals[94]->linkTo(portals[84]);
  portals[95]->linkTo(portals[93]);
  portals[96]->linkTo(portals[122]);
  portals[97]->linkTo(portals[124]);
  portals[98]->linkTo(portals[119]);
  portals[99]->linkTo(portals[106]);
  portals[100]->linkTo(portals[66]);
  portals[101]->linkTo(portals[92]);
  portals[102]->linkTo(portals[87]);
  portals[103]->linkTo(portals[85]);
  portals[104]->linkTo(portals[167]);
  portals[105]->linkTo(portals[11]);
  portals[106]->linkTo(portals[99]);
  portals[108]->linkTo(portals[120]);
  portals[109]->linkTo(portals[170]);
  portals[110]->linkTo(portals[169]);
  portals[111]->linkTo(portals[168]);
  portals[112]->linkTo(portals[173]);
  portals[113]->linkTo(portals[123]);
  portals[114]->linkTo(portals[201]);
  portals[115]->linkTo(portals[143]);
  portals[116]->linkTo(portals[175]);
  portals[232]->linkTo(portals[179]);
  portals[117]->linkTo(portals[195]);
  portals[233]->linkTo(portals[105]);
  portals[118]->linkTo(portals[188]);
  portals[234]->linkTo(portals[199]);
  portals[119]->linkTo(portals[98]);
  portals[235]->linkTo(portals[106]);
  portals[120]->linkTo(portals[61]);
  portals[121]->linkTo(portals[69]);
  portals[122]->linkTo(portals[96]);
  portals[123]->linkTo(portals[113]);
  portals[124]->linkTo(portals[97]);
  portals[125]->linkTo(portals[180]);
  portals[126]->linkTo(portals[174]);
  portals[236]->linkTo(portals[110]);
  portals[127]->linkTo(portals[202]);
  portals[237]->linkTo(portals[112]);
  portals[128]->linkTo(portals[73]);
  portals[238]->linkTo( portals[109]);
  portals[129]->linkTo(portals[178]);
  portals[130]->linkTo(portals[199]);
  portals[239]->linkTo( portals[70]);
  portals[131]->linkTo(portals[9]);
  portals[132]->linkTo(portals[158]);
  portals[133]->linkTo(portals[142]);
  portals[134]->linkTo(portals[139]);
  portals[135]->linkTo(portals[31]);
  portals[137]->linkTo(portals[103]);
  portals[140]->linkTo(portals[102]);
  portals[240]->linkTo(portals[143]);
  portals[141]->linkTo(portals[147]);
  portals[143]->linkTo(portals[115]);
  portals[144]->linkTo(portals[138]);
  portals[145]->linkTo(portals[101]);
  portals[241]->linkTo(portals[137]);
  portals[148]->linkTo(portals[151]);
  portals[149]->linkTo(portals[136]);
  portals[152]->linkTo(portals[150]);
  portals[153]->linkTo(portals[155]);
  portals[156]->linkTo(portals[154]);
  portals[158]->linkTo(portals[132]);
  portals[159]->linkTo(portals[120]);
  portals[161]->linkTo(portals[62]);
  portals[162]->linkTo(portals[10]);
  portals[164]->linkTo(portals[186]);
  portals[242]->linkTo(portals[52]);
  portals[165]->linkTo(portals[63]);
  portals[243]->linkTo(portals[170]);
  portals[166]->linkTo(portals[8]);
  portals[167]->linkTo(portals[104]);
  portals[168]->linkTo(portals[111]);
  portals[169]->linkTo(portals[110]);
  portals[170]->linkTo(portals[109]);
  portals[171]->linkTo(portals[193]);
  portals[173]->linkTo(portals[112]);
  portals[174]->linkTo(portals[126]);
  portals[175]->linkTo(portals[116]);
  portals[176]->linkTo(portals[117]);
  portals[177]->linkTo(portals[179]);
  portals[178]->linkTo(portals[129]);
  portals[179]->linkTo(portals[177] );
  portals[180]->linkTo(portals[125]);
  portals[181]->linkTo(portals[12]);
  portals[182]->linkTo(portals[13]);
  portals[183]->linkTo(portals[14]);
  portals[184]->linkTo(portals[189]);
  portals[185]->linkTo(portals[187]);
  portals[244]->linkTo(portals[173]);
  portals[186]->linkTo(portals[164]);
  portals[187]->linkTo(portals[185]);
  portals[188]->linkTo(portals[118]);
  portals[245]->linkTo(portals[115]);
  portals[189]->linkTo(portals[184]);
  portals[191]->linkTo(portals[195]);
  portals[192]->linkTo(portals[188]);
  portals[193]->linkTo(portals[171]);
  portals[194]->linkTo(portals[199]);
  portals[195]->linkTo(portals[191]);
  portals[246]->linkTo(portals[189]);
  portals[247]->linkTo(portals[201]);
  portals[248]->linkTo(portals[111]);
  portals[249]->linkTo(portals[188]);
  portals[250]->linkTo(portals[103]);
  portals[196]->linkTo(portals[146]);
  portals[199]->linkTo(portals[194]);
  portals[200]->linkTo(portals[71]);
  portals[201]->linkTo(portals[114]);
  portals[202]->linkTo(portals[127]);
  portals[207]->linkTo(portals[26]);
  portals[208]->linkTo(portals[29]);
  portals[209]->linkTo(portals[211]);
  portals[210]->linkTo(portals[41]);
  portals[211]->linkTo(portals[209]);
  portals[251]->linkTo(portals[205]);
}
