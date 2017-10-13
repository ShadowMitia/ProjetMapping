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

  for (unsigned int i = 0; i < 1; i++)
    {
      createAvatar(1300, 700);
      //createAvatar(1200, 700);
    }

  for (auto &avatar : avatars)
    {
      teleportables.push_back(avatar);
    }

  ofPolyline pickupForm;
  pickupForm.addVertex(0, 0);
  pickupForm.addVertex(10, 0);
  pickupForm.addVertex(10, 10);
  pickupForm.addVertex(0, 10);
  pickupForm.close();

  PickUp* p = new PickUp(world.getWorld(), pickupForm);
  p->setPosition(1400, 700);

  pickups.push_back(p);

  for (auto &pickup : pickups)
    {
      teleportables.push_back(pickup);
    }


  ofPolyline blockForm;
  blockForm.addVertex(0, 0);
  blockForm.addVertex(10, 0);
  blockForm.addVertex(10, 10);
  blockForm.addVertex(0, 10);
  blockForm.close();


  ObjectBlock* block = new ObjectBlock(world.getWorld(), blockForm);
  block->setPosition(1300, 700);
  blocks.push_back(block);

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


  for (auto &platform : platforms)
    {
      ofSetHexColor(0xFF0000);
      platform->ground.draw();
    }

  for (unsigned int i = 0; i < circles.size(); i++) {
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

void WorldsBox2d::update(){

  // supprimes les pickups collectés et les enleves de box2d et de la liste des pickups

  //pickups.erase(std::remove_if(pickups.begin(), pickups.end(), [&](auto& p){ std::remove(teleportables.begin(), teleportables.end(), p); bool res = p->isCollected(); if (res) world.getWorld()->DestroyBody(p->pickUp.body); return res; }), pickups.end());

  world.update();
    

  for (auto &block : blocks)
    {
      block->update();
    }

  for (auto& pickup : pickups)
    {
      pickup->update();
    }

  for (int j = 0; j < avatars.size(); j++)
    {
      avatars[j]->presUpdate();
        
      for (int i = 0; i < ladders.size(); i++) {
	if (ladders[i]->inside(avatars[j])) {
	  avatars[j]->modeDeplace = Deplacement::LADDER;
	}
	else
	  {
	    avatars[j]->modeDeplace = Deplacement::PLATFORM;
	  }
            
      }
      avatars[j]->update();
    }

  for (int i = 0; i< perspectivePortals.size(); i++) {
    perspectivePortals[i]->update(teleportables);
  }

  for (int i = 0; i< portals.size(); i++) {
    portals[i]->update(teleportables);
  }


  //warterfalls->update();
}

void WorldsBox2d::createPlatform(ofPolyline _polyline){
    
  Platform *edge = new Platform;
  edge->create(world.getWorld(), _polyline);
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

void WorldsBox2d::createBox(ofPolyline polyline)
{
  ObjectBlock* block = new ObjectBlock(world.getWorld(), polyline);
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

// attention code deguelas 
void WorldsBox2d::importPortal(){
  constexpr const int sizeH = 160;
  constexpr const int sizeW = 3;

  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Left, ofRectangle(1560, 600, sizeW, sizeH)));
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Right, ofRectangle(1800, 600, sizeW, sizeH)));
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, ofRectangle(1360, 650, sizeW, sizeH)));
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Right, ofRectangle(1560, 650, sizeW, sizeH)));
  perspectivePortals.push_back(new PerspectivePortal(Orientation::Vertical, PortalDirection::Left, ofRectangle(1500, 600, sizeW, sizeH)));

  linkPortals(portals[0], portals[1]);
  linkPortals(portals[2], portals[3]);
  linkPortals(portals[4], portals[0]);


  /*
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
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, 3280, 80, sizeW, sizeH / 2));// portal:18
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Left, 80, 80, sizeW, sizeH));// portal:19
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Right, 399, 80, sizeW, sizeH / 2));// portal:20
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Left, 560, 80, sizeW, sizeH / 2));// portal:21
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Right, 719, 80, sizeW, sizeH));// portal:22
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Left, 800, 80, sizeW, sizeH / 2));// portal:23
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Left, 880, 80, sizeW, sizeH / 2));// portal:24
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Right, 1119, 80, sizeW, sizeH / 2));// portal:25
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Right, 799, 159, sizeW, sizeH / 2));// portal:26
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Right, 879, 159, sizeW, sizeH / 2));// portal:27
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Right, 959, 159, sizeW, sizeH / 2));// portal:28
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Right, 1039, 159, sizeW, sizeH / 2));// portal:29
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Left, 1200, 80, sizeW, sizeH));// portal:30
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Right, 1679, 80, sizeW, sizeH));// portal:31
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Left, 2160, 80, sizeW, sizeH));// portal:32
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Right, 2479, 80, sizeW, sizeH));// portal:33
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Left, 2560, 80, sizeW, sizeH));// portal:34
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Right, 2719, 80, sizeW, sizeH));// portal:35
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Left, 2800, 80, sizeW, sizeH));// portal:36
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Right, 2959, 80, sizeW, sizeH));// portal:37
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Left, 3040, 80, sizeW, sizeH));// portal:38
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Right, 3199, 80, sizeW, sizeH));// portal:39
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Left, 3280, 80, sizeW, sizeH / 2));// portal:40
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Right, 3359, 80, sizeW, sizeH / 2));// portal:41
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Right, 3280, 159, sizeW, sizeH / 2));// portal:42
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
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Right, 239, 320, sizeW, sizeH));// portal:72
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Right, 3439, 640, sizeW, sizeH / 2));// portal:73
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Right, 399, 320, sizeW, sizeH));// portal:74
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Left, 400, 320, sizeW, sizeH));// portal:75
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Right, 719, 320, sizeW, sizeH));// portal:76
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Left, 720, 320, sizeW, sizeH));// portal:77
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Right, 879, 320, sizeW, sizeH));// portal:78
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Left, 880, 320, sizeW, sizeH));// portal:79
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Left, 1040, 320, sizeW, sizeH));// portal:80
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Right, 1359, 320, sizeW, sizeH / 2));// portal:81
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Right, 1359, 400, sizeW, sizeH / 2));// portal:82
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Right, 1439, 400, sizeW, sizeH / 2));// portal:83
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Right, 1519, 320, sizeW, sizeH / 2));// portal:84
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Right, 1440, 399, sizeW, sizeH / 2));// portal:85
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Left, 1440, 400, sizeW, sizeH / 2));// portal:86
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, 1440, 400, sizeW, sizeH / 2));// portal:87
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Right, 1519, 400, sizeW, sizeH / 2));// portal:88
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Left, 1520, 320, sizeW, sizeH / 2));// portal:89
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Right, 1520, 399, sizeW, sizeH / 2));// portal:90
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Left, 1520, 400, sizeW, sizeH / 2));// portal:91
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, 1520, 400, sizeW, sizeH / 2));// portal:92
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Right, 1599, 400, sizeW, sizeH / 2));// portal:93
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Left, 2000, 320, sizeW, sizeH / 2));// portal:94
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Left, 2000, 400, sizeW, sizeH / 2));// portal:95
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
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Right, 880, 479, sizeW, sizeH / 2));// portal:107
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Right, 1040, 479, sizeW, sizeH));// portal:108
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Right, 1360, 479, sizeW, sizeH / 2));// portal:109
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Right, 1440, 479, sizeW, sizeH / 2));// portal:110
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Right, 1520, 479, sizeW, sizeH / 2));// portal:111
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Right, 1600, 479, sizeW, sizeH / 2));// portal:112
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Right, 2560, 479, sizeW, sizeH));// portal:113
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Right, 2800, 479, sizeW, sizeH / 2));// portal:114
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
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Right, 239, 560, sizeW, sizeH / 2));// portal:133
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Right, 239, 640, sizeW, sizeH / 2));// portal:134
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Left, 240, 560, sizeW, sizeH));// portal:135
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Right, 399, 560, sizeW, sizeH / 2));// portal:136
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Right, 319, 639, sizeW, sizeH / 2));// portal:137
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Right, 319, 640, sizeW, sizeH / 2));// portal:138
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Left, 320, 640, sizeW, sizeH / 2));// portal:139
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, 320, 640, sizeW, sizeH / 2));// portal:140
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Left, 399, 640, sizeW, sizeH / 2));// portal:141
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Left, 400, 560, sizeW, sizeH / 2));// portal:142
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Right, 400, 639, sizeW, sizeH / 2));// portal:143
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Left, 400, 640, sizeW, sizeH / 2));// portal:144
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, 400, 640, sizeW, sizeH / 2));// portal:145
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Right, 479, 640, sizeW, sizeH / 2));// portal:146
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Left, 480, 640, sizeW, sizeH / 2));// portal:147
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Right, 559, 560, sizeW, sizeH));// portal:148
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Left, 560, 560, sizeW, sizeH / 2));// portal:149
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Right, 879, 560, sizeW, sizeH));// portal:150
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Left, 880, 560, sizeW, sizeH));// portal:151
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Left, 1040, 560, sizeW, sizeH));// portal:152
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Right, 1359, 560, sizeW, sizeH));// portal:153
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Right, 1519, 560, sizeW, sizeH));// portal:154
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Left, 1520, 560, sizeW, sizeH));// portal:155
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Left, 1840, 560, sizeW, sizeH));// portal:156
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Right, 1999, 560, sizeW, sizeH));// portal:157
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Right, 2319, 560, sizeW, sizeH));// portal:158
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Left, 2560, 560, sizeW, sizeH));// portal:159
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Right, 2639, 560, sizeW, sizeH / 2));// portal:160
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Right, 2560, 719, sizeW, sizeH));// portal:161
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Left, 2800, 560, sizeW, sizeH));// portal:162
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Right, 2640, 639, sizeW, sizeH / 2));// portal:163
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Right, 2719, 560, sizeW, sizeH / 2));// portal:164
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Right, 2719, 640, sizeW, sizeH / 2));// portal:165
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Right, 2959, 560, sizeW, sizeH));// portal:166
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Right, 2800, 719, sizeW, sizeH));// portal:167
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Left, 3360, 560, sizeW, sizeH / 2));// portal:168
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, 3280, 640, sizeW, sizeH / 2));// portal:169
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Left, 3280, 640, sizeW, sizeH / 2));// portal:170
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Right, 3439, 560, sizeW, sizeH / 2));// portal:171
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Left, 1600, 400, sizeW, sizeH / 2));// portal:172
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
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Right, 2880, 479, sizeW, sizeH / 2));// portal:190
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, 320, 560, sizeW, sizeH / 2));// portal:191
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, 480, 560, sizeW, sizeH / 2));// portal:192
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, 1920, 560, sizeW, sizeH / 2));// portal:193
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, 2640, 560, sizeW, sizeH / 2));// portal:194
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Left, 3040, 640, sizeW, sizeH / 2));// portal:195
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Left, 560, 560, sizeW, sizeH / 2));// portal:196
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Right, 1280, 479, sizeW, sizeH / 2));// portal:197   inutil
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Right, 1679, 160, sizeW, sizeH / 2));// portal:198   inutil
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Left, 960, 320, sizeW, sizeH / 2));// portal:199
  portals.push_back(new WorldPortal(Orientation::Vertical, PortalDirection::Right, 2319, 320, sizeW, sizeH));// portal:200
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Right, 960, 479, sizeW, sizeH / 2));// portal:201
  portals.push_back(new WorldPortal(Orientation::Horizontal, PortalDirection::Right, 3360, 719, sizeW, sizeH / 2));// portal:202

  //angle; perspective  portals[],nullptr

  linkPortals(portals[0], portals[15]);
  linkPortals(portals[1], portals[34]);
  linkPortals(portals[2], portals[47]);
  linkPortals(portals[3], portals[35]);
  linkPortals(portals[4], portals[18]);
  linkPortals(portals[5], portals[40]);
  linkPortals(portals[6], portals[42]);
  linkPortals(portals[7], portals[41]);
  linkPortals(portals[8], portals[166]);
  //portals[9]->linkTo(portals[131], portals[104]);
  linkPortals(portals[10], portals[162]);
  linkPortals(portals[11], portals[105]);
  linkPortals(portals[12], portals[181]);
  linkPortals(portals[13], portals[182]);
  linkPortals(portals[14], portals[183]);
  linkPortals(portals[15], portals[0]);
  //portals[16]->linkTo(portals[58], portals[177]);
  //portals[17]->linkTo(portals[55], portals[167]);
  //portals[18]->linkTo(portals[4], portals[190]);
  //linkPortals(portals[19], portals[22]);
  //portals[20]->linkTo(nullptr, nullptr);
  //portals[21]->linkTo(nullptr, portals[25]);
  linkPortals(portals[22], portals[19]);
  linkPortals(portals[23], portals[25]);
  linkPortals(portals[24], portals[20]);
  linkPortals(portals[25], portals[23]);
  //portals[26]->linkTo(nullptr, portals[190]);
  //portals[27]->linkTo(nullptr, portals[160]);
  //portals[28]->linkTo(nullptr, portals[163]);
  //portals[29]->linkTo(nullptr, portals[52]);
  linkPortals(portals[30], portals[33]);
  //portals[31]->linkTo(nullptr, portals[135]);
  //portals[32]->linkTo(nullptr, portals[157]);
  //portals[33]->linkTo(nullptr, portals[30]);
  //portals[34]->linkTo(portals[1], portals[37]);
  //portals[35]->linkTo(portals[3], portals[49]);
  //portals[36]->linkTo(portals[59], portals[99]);
  linkPortals(portals[37], portals[44]);
  linkPortals(portals[38], portals[56]);
  linkPortals(portals[39], portals[68]);
  //portals[40]->linkTo(portals[5], portals[160]);
  //portals[41]->linkTo(portals[7], portals[52]);
  //portals[42]->linkTo(portals[6], portals[163]);
  linkPortals(portals[43], portals[177]);
  linkPortals(portals[44], portals[37]);
  linkPortals(portals[45], portals[65]);
  linkPortals(portals[46], portals[49]);
  linkPortals(portals[47], portals[2]);
  //portals[48]->linkTo(portals[64], portals[51]);
  linkPortals(portals[49], portals[46]);
  linkPortals(portals[50], portals[67]);
  linkPortals(portals[51], portals[90]);
  linkPortals(portals[52], portals[85]);
  //portals[53]->linkTo(portals[87], portals[169]);
    //portals[54]->linkTo(portals[92], portals[168]);
  linkPortals(portals[55], portals[17]);
  linkPortals(portals[56], portals[38]);
  linkPortals(portals[57], portals[43]);
  linkPortals(portals[58], portals[16]);
  //portals[59]->linkTo(portals[36], portals[44]);
  linkPortals(portals[60], portals[130]);
  linkPortals(portals[61], portals[159]);
  linkPortals(portals[62], portals[161]);
  linkPortals(portals[63], portals[165]);
  linkPortals(portals[64], portals[48]);
  linkPortals(portals[65], portals[45]);
  linkPortals(portals[66], portals[100]);
  //portals[67]->linkTo(portals[50], portals[46]);
  linkPortals(portals[68], portals[39]);
  linkPortals(portals[69], portals[121]);
  linkPortals(portals[70], portals[192]);
  linkPortals(portals[71], portals[200]);
  //portals[72]->linkTo(nullptr, portals[75]);
  linkPortals(portals[73], portals[128]);
  //portals[74]->linkTo(nullptr, nullptr);
  //portals[75]->linkTo(nullptr, nullptr);
  //portals[76]->linkTo(nullptr, portals[79]);
  //portals[77]->linkTo(nullptr, portals[74]);
  //portals[78]->linkTo(nullptr, nullptr);
  //portals[79]->linkTo(nullptr, nullptr);
  //portals[80]->linkTo(nullptr, portals[78]);
  //portals[81]->linkTo(nullptr, portals[84]);
  //portals[82]->linkTo(nullptr, portals[86]);
  //portals[83]->linkTo(nullptr, nullptr);
  //portals[84]->linkTo(nullptr, nullptr);
  linkPortals(portals[85], portals[52]);
  //portals[86]->linkTo(nullptr, nullptr);
  //portals[87]->linkTo(portals[53], portals[90]);
  //portals[88]->linkTo(nullptr, portals[172]);
  //portals[89]->linkTo(nullptr, nullptr);
  linkPortals(portals[90], portals[51]);
  //portals[91]->linkTo(nullptr, portals[83]);
  //portals[92]->linkTo(portals[54], portals[85]);
  //portals[93]->linkTo(nullptr, nullptr);
  //portals[94]->linkTo(nullptr, portals[84]);
  //portals[95]->linkTo(nullptr, portals[93]);
  linkPortals(portals[96], portals[122]);
  linkPortals(portals[97], portals[124]);
  linkPortals(portals[98], portals[119]);
  linkPortals(portals[99], portals[106]);
  linkPortals(portals[100], portals[66]);
  linkPortals(portals[101], portals[92]);
  linkPortals(portals[102], portals[87]);
  linkPortals(portals[103], portals[85]);
  linkPortals(portals[104], portals[167]);
  linkPortals(portals[105], portals[11]);
  linkPortals(portals[106], portals[99]);
  linkPortals(portals[107], portals[114]);
  linkPortals(portals[108], portals[120]);
  linkPortals(portals[109], portals[170]);
  linkPortals(portals[110], portals[169]);
  linkPortals(portals[111], portals[168]);
  linkPortals(portals[112], portals[173]);
  linkPortals(portals[113], portals[123]);
  linkPortals(portals[114], portals[201]);
  linkPortals(portals[115], portals[143]);
  //portals[116]->linkTo(portals[175], portals[179]);
  //portals[117]->linkTo(portals[195], portals[105]);
  //portals[118]->linkTo(portals[188], portals[199]);
  //portals[119]->linkTo(portals[98], portals[106]);
  linkPortals(portals[120], portals[61]);
  linkPortals(portals[121], portals[69]);
  linkPortals(portals[122], portals[96]);
  linkPortals(portals[123], portals[113]);
  linkPortals(portals[124], portals[97]);
  linkPortals(portals[125], portals[180]);
  //portals[126]->linkTo(portals[174], portals[110]);
  //portals[127]->linkTo(portals[202], portals[112]);
  //portals[128]->linkTo(portals[73], portals[109]);
  linkPortals(portals[129], portals[178]);
  //portals[130]->linkTo(portals[199], portals[70]);
  linkPortals(portals[131], portals[9]);
  linkPortals(portals[132], portals[158]);
  //portals[133]->linkTo(nullptr, portals[142]);
  //portals[134]->linkTo(nullptr, portals[139]);
  //portals[135]->linkTo(nullptr, portals[31]);
  // portals[136]->linkTo(nullptr, nullptr);
  linkPortals(portals[137], portals[103]);
  //portals[138]->linkTo(nullptr, nullptr);
  //portals[139]->linkTo(nullptr, nullptr);
  //portals[140]->linkTo(portals[102], portals[143]);
  //portals[141]->linkTo(nullptr, portals[147]);
  //portals[142]->linkTo(nullptr, nullptr);
  linkPortals(portals[143], portals[115]);
  //portals[144]->linkTo(nullptr, portals[138]);
  //portals[145]->linkTo(portals[101], portals[137]);
  //portals[146]->linkTo(nullptr, nullptr);
  //portals[147]->linkTo(nullptr, nullptr);
  //portals[148]->linkTo(nullptr, portals[151]);
  //portals[149]->linkTo(nullptr, portals[136]);
  //portals[150]->linkTo(nullptr, nullptr);
  //portals[151]->linkTo(nullptr, nullptr);
  //portals[152]->linkTo(nullptr, portals[150]);
  //portals[153]->linkTo(nullptr, portals[155]);
  //portals[154]->linkTo(nullptr, nullptr);
  //portals[155]->linkTo(nullptr, nullptr);
  //portals[156]->linkTo(nullptr, portals[154]);
  //portals[157]->linkTo(nullptr, nullptr);
  linkPortals(portals[158], portals[132]);
  linkPortals(portals[159], portals[120]);
  //portals[160]->linkTo(nullptr, nullptr);
  linkPortals(portals[161], portals[62]);
  linkPortals(portals[162], portals[10]);
  //portals[163]->linkTo(nullptr, nullptr);
  //portals[164]->linkTo(portals[186], portals[52]);
  //portals[165]->linkTo(portals[63], portals[170]);
  linkPortals(portals[166], portals[8]);
  linkPortals(portals[167], portals[104]);
  linkPortals(portals[168], portals[111]);
  linkPortals(portals[169], portals[110]);
  linkPortals(portals[170], portals[109]);
  linkPortals(portals[171], portals[193]);
  //portals[172]->linkTo(nullptr, nullptr);
  linkPortals(portals[173], portals[112]);
  linkPortals(portals[174], portals[126]);
  linkPortals(portals[175], portals[116]);
  linkPortals(portals[176], portals[117]);
  linkPortals(portals[177], portals[179]);
  linkPortals(portals[178], portals[129]);
  linkPortals(portals[179], portals[177]);
  linkPortals(portals[180], portals[125]);
  linkPortals(portals[181], portals[12]);
  linkPortals(portals[182], portals[13]);
  linkPortals(portals[183], portals[14]);
  linkPortals(portals[184], portals[189]);
  //portals[185]->linkTo(portals[187], portals[173]);
  linkPortals(portals[186], portals[164]);
  linkPortals(portals[187], portals[185]);
  //linkPortals(portals[188], portals[118]);
  linkPortals(portals[189], portals[184]);
  linkPortals(portals[190], portals[107]);
  //portals[191]->linkTo(portals[195], portals[189]);
  //portals[192]->linkTo(portals[188], portals[201]);
  //portals[193]->linkTo(portals[171], portals[111]);
  //portals[194]->linkTo(portals[199], portals[188]);
  //portals[195]->linkTo(portals[191], portals[103]);
  //portals[196]->linkTo(nullptr, portals[146]);
  //portals[197]->linkTo(nullptr, nullptr);
  //portals[198]->linkTo(nullptr, nullptr);
  linkPortals(portals[199], portals[194]);
  linkPortals(portals[200], portals[71]);
  linkPortals(portals[201], portals[114]);
  linkPortals(portals[202], portals[127]);

  */



  /*
    portals[0]->linkTo(portals[15], nullptr);
    portals[1]->linkTo(portals[34], nullptr);
    portals[2]->linkTo(portals[47], nullptr);
    portals[3]->linkTo(portals[35], nullptr);
    portals[4]->linkTo(portals[18], nullptr);
    portals[5]->linkTo(portals[40], nullptr);
    portals[6]->linkTo(portals[42], nullptr);
    portals[7]->linkTo(portals[41], nullptr);
    portals[8]->linkTo(portals[166], nullptr);
    portals[9]->linkTo(portals[131], portals[104]);
    portals[10]->linkTo(portals[162], nullptr);
    portals[11]->linkTo(portals[105], nullptr);
    portals[12]->linkTo(portals[181], nullptr);
    portals[13]->linkTo(portals[182], nullptr);
    portals[14]->linkTo(portals[183], nullptr);
    portals[15]->linkTo(portals[0], nullptr);
    portals[16]->linkTo(portals[58], portals[177]);
    portals[17]->linkTo(portals[55], portals[167]);
    portals[18]->linkTo(portals[4], portals[190]);
    portals[19]->linkTo(portals[22], nullptr);
    portals[20]->linkTo(nullptr, nullptr);
    portals[21]->linkTo(nullptr, portals[25]);
    portals[22]->linkTo(portals[19], nullptr);
    portals[23]->linkTo(portals[25], nullptr);
    portals[24]->linkTo(portals[20], nullptr);
    portals[25]->linkTo(portals[23], nullptr);
    portals[26]->linkTo(nullptr, portals[190]);
    portals[27]->linkTo(nullptr, portals[160]);
    portals[28]->linkTo(nullptr, portals[163]);
    portals[29]->linkTo(nullptr, portals[52]);
    portals[30]->linkTo(portals[33], nullptr);
    portals[31]->linkTo(nullptr, portals[135]);
    portals[32]->linkTo(nullptr, portals[157]);
    portals[33]->linkTo(nullptr, portals[30]);
    portals[34]->linkTo(portals[1], portals[37]);
    portals[35]->linkTo(portals[3], portals[49]);
    portals[36]->linkTo(portals[59], portals[99]);
    portals[37]->linkTo(portals[44], nullptr);
    portals[38]->linkTo(portals[56], nullptr);
    portals[39]->linkTo(portals[68], nullptr);
    portals[40]->linkTo(portals[5], portals[160]);
    portals[41]->linkTo(portals[7], portals[52]);
    portals[42]->linkTo(portals[6], portals[163]);
    portals[43]->linkTo(portals[177], nullptr);
    portals[44]->linkTo(portals[37], nullptr);
    portals[45]->linkTo(portals[65], nullptr);
    portals[46]->linkTo(portals[49], nullptr);
    portals[47]->linkTo(portals[2], nullptr);
    portals[48]->linkTo(portals[64], portals[51]);
    portals[49]->linkTo(portals[46], nullptr);
    portals[50]->linkTo(portals[67], nullptr);
    portals[51]->linkTo(portals[90], nullptr);
    portals[52]->linkTo(portals[85], nullptr);
    portals[53]->linkTo(portals[87], portals[169]);
    portals[54]->linkTo(portals[92], portals[168]);
    portals[55]->linkTo(portals[17], nullptr);
    portals[56]->linkTo(portals[38], nullptr);
    portals[57]->linkTo(portals[43], nullptr);
    portals[58]->linkTo(portals[16], nullptr);
    portals[59]->linkTo(portals[36], portals[44]);
    portals[60]->linkTo(portals[130], nullptr);
    portals[61]->linkTo(portals[159], nullptr);
    portals[62]->linkTo(portals[161], nullptr);
    portals[63]->linkTo(portals[165], nullptr);
    portals[64]->linkTo(portals[48], nullptr);
    portals[65]->linkTo(portals[45], nullptr);
    portals[66]->linkTo(portals[100], nullptr);
    portals[67]->linkTo(portals[50], portals[46]);
    portals[68]->linkTo(portals[39], nullptr);
    portals[69]->linkTo(portals[121], nullptr);
    portals[70]->linkTo(portals[192], nullptr);
    portals[71]->linkTo(portals[200], nullptr);
    portals[72]->linkTo(nullptr, portals[75]);
    portals[73]->linkTo(portals[128], nullptr);
    portals[74]->linkTo(nullptr, nullptr);
    portals[75]->linkTo(nullptr, nullptr);
    portals[76]->linkTo(nullptr, portals[79]);
    portals[77]->linkTo(nullptr, portals[74]);
    portals[78]->linkTo(nullptr, nullptr);
    portals[79]->linkTo(nullptr, nullptr);
    portals[80]->linkTo(nullptr, portals[78]);
    portals[81]->linkTo(nullptr, portals[84]);
    portals[82]->linkTo(nullptr, portals[86]);
    portals[83]->linkTo(nullptr, nullptr);
    portals[84]->linkTo(nullptr, nullptr);
    portals[85]->linkTo(portals[52], nullptr);
    portals[86]->linkTo(nullptr, nullptr);
    portals[87]->linkTo(portals[53], portals[90]);
    portals[88]->linkTo(nullptr, portals[172]);
    portals[89]->linkTo(nullptr, nullptr);
    portals[90]->linkTo(portals[51], nullptr);
    portals[91]->linkTo(nullptr, portals[83]);
    portals[92]->linkTo(portals[54], portals[85]);
    portals[93]->linkTo(nullptr, nullptr);
    portals[94]->linkTo(nullptr, portals[84]);
    portals[95]->linkTo(nullptr, portals[93]);
    portals[96]->linkTo(portals[122], nullptr);
    portals[97]->linkTo(portals[124], nullptr);
    portals[98]->linkTo(portals[119], nullptr);
    portals[99]->linkTo(portals[106], nullptr);
    portals[100]->linkTo(portals[66], nullptr);
    portals[101]->linkTo(portals[92], nullptr);
    portals[102]->linkTo(portals[87], nullptr);
    portals[103]->linkTo(portals[85], nullptr);
    portals[104]->linkTo(portals[167], nullptr);
    portals[105]->linkTo(portals[11], nullptr);
    portals[106]->linkTo(portals[99], nullptr);
    portals[107]->linkTo(portals[114], nullptr);
    portals[108]->linkTo(portals[120], nullptr);
    portals[109]->linkTo(portals[170], nullptr);
    portals[110]->linkTo(portals[169], nullptr);
    portals[111]->linkTo(portals[168], nullptr);
    portals[112]->linkTo(portals[173], nullptr);
    portals[113]->linkTo(portals[123], nullptr);
    portals[114]->linkTo(portals[201], nullptr);
    portals[115]->linkTo(portals[143], nullptr);
    portals[116]->linkTo(portals[175], portals[179]);
    portals[117]->linkTo(portals[195], portals[105]);
    portals[118]->linkTo(portals[188], portals[199]);
    portals[119]->linkTo(portals[98], portals[106]);
    portals[120]->linkTo(portals[61], nullptr);
    portals[121]->linkTo(portals[69], nullptr);
    portals[122]->linkTo(portals[96], nullptr);
    portals[123]->linkTo(portals[113], nullptr);
    portals[124]->linkTo(portals[97], nullptr);
    portals[125]->linkTo(portals[180], nullptr);
    portals[126]->linkTo(portals[174], portals[110]);
    portals[127]->linkTo(portals[202], portals[112]);
    portals[128]->linkTo(portals[73], portals[109]);
    portals[129]->linkTo(portals[178], nullptr);
    portals[130]->linkTo(portals[199], portals[70]);
    portals[131]->linkTo(portals[9], nullptr);
    portals[132]->linkTo(portals[158], nullptr);
    portals[133]->linkTo(nullptr, portals[142]);
    portals[134]->linkTo(nullptr, portals[139]);
    portals[135]->linkTo(nullptr, portals[31]);
    portals[136]->linkTo(nullptr, nullptr);
    portals[137]->linkTo(portals[103], nullptr);
    portals[138]->linkTo(nullptr, nullptr);
    portals[139]->linkTo(nullptr, nullptr);
    portals[140]->linkTo(portals[102], portals[143]);
    portals[141]->linkTo(nullptr, portals[147]);
    portals[142]->linkTo(nullptr, nullptr);
    portals[143]->linkTo(portals[115], nullptr);
    portals[144]->linkTo(nullptr, portals[138]);
    portals[145]->linkTo(portals[101], portals[137]);
    portals[146]->linkTo(nullptr, nullptr);
    portals[147]->linkTo(nullptr, nullptr);
    portals[148]->linkTo(nullptr, portals[151]);
    portals[149]->linkTo(nullptr, portals[136]);
    portals[150]->linkTo(nullptr, nullptr);
    portals[151]->linkTo(nullptr, nullptr);
    portals[152]->linkTo(nullptr, portals[150]);
    portals[153]->linkTo(nullptr, portals[155]);
    portals[154]->linkTo(nullptr, nullptr);
    portals[155]->linkTo(nullptr, nullptr);
    portals[156]->linkTo(nullptr, portals[154]);
    portals[157]->linkTo(nullptr, nullptr);
    portals[158]->linkTo(portals[132], nullptr);
    portals[159]->linkTo(portals[120], nullptr);
    portals[160]->linkTo(nullptr, nullptr);
    portals[161]->linkTo(portals[62], nullptr);
    portals[162]->linkTo(portals[10], nullptr);
    portals[163]->linkTo(nullptr, nullptr);
    portals[164]->linkTo(portals[186], portals[52]);
    portals[165]->linkTo(portals[63], portals[170]);
    portals[166]->linkTo(portals[8], nullptr);
    portals[167]->linkTo(portals[104], nullptr);
    portals[168]->linkTo(portals[111], nullptr);
    portals[169]->linkTo(portals[110], nullptr);
    portals[170]->linkTo(portals[109], nullptr);
    portals[171]->linkTo(portals[193], nullptr);
    portals[172]->linkTo(nullptr, nullptr);
    portals[173]->linkTo(portals[112], nullptr);
    portals[174]->linkTo(portals[126], nullptr);
    portals[175]->linkTo(portals[116], nullptr);
    portals[176]->linkTo(portals[117], nullptr);
    portals[177]->linkTo(portals[179], nullptr);
    portals[178]->linkTo(portals[129], nullptr);
    portals[179]->linkTo(portals[177], nullptr);
    portals[180]->linkTo(portals[125], nullptr);
    portals[181]->linkTo(portals[12], nullptr);
    portals[182]->linkTo(portals[13], nullptr);
    portals[183]->linkTo(portals[14], nullptr);
    portals[184]->linkTo(portals[189], nullptr);
    portals[185]->linkTo(portals[187], portals[173]);
    portals[186]->linkTo(portals[164], nullptr);
    portals[187]->linkTo(portals[185], nullptr);
    portals[188]->linkTo(portals[118], portals[115]);
    portals[189]->linkTo(portals[184], nullptr);
    portals[190]->linkTo(portals[107], nullptr);
    portals[191]->linkTo(portals[195], portals[189]);
    portals[192]->linkTo(portals[188], portals[201]);
    portals[193]->linkTo(portals[171], portals[111]);
    portals[194]->linkTo(portals[199], portals[188]);
    portals[195]->linkTo(portals[191], portals[103]);
    portals[196]->linkTo(nullptr, portals[146]);
    portals[197]->linkTo(nullptr, nullptr);
    portals[198]->linkTo(nullptr, nullptr);
    portals[199]->linkTo(portals[194], nullptr);
    portals[200]->linkTo(portals[71], nullptr);
    portals[201]->linkTo(portals[114], nullptr);
    portals[202]->linkTo(portals[127], nullptr);
  */

}
