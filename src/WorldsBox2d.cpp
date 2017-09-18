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

    importPortal();
    
    for (unsigned int i = 0; i < 1; i++)
      {
	createAvatar(300, 40);
      }
    //wiimotes.startThread();
    //createAvatar(100, 100);

	for (auto &avatar : avatars)
	{
		teleportables.push_back(avatar);
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
    
    /*
  for (auto &block : blocks)
    {
      ofSetHexColor(0xFFFFF);
      block.draw();
    }*/

    for (auto &avatar : avatars) {
    ofSetHexColor(0x00FF00);
    avatar->draw();
  }

    warterfalls->draw();
    //world.draw();

}
void WorldsBox2d::createAvatar(int x, int y){
    Avatar * avatar = new Avatar(&world, lightSystem2D);
    avatar->polygon.setData(new typeBox2d);
    typeBox2d *sd  = (typeBox2d*) avatar->polygon.getData();
    sd->type = typeBox2d::Type::AVATAR;
    avatar->setPosition(x, y);
    avatars.push_back(avatar);
}
void WorldsBox2d::update(){
    world.update();
    
    for (int i = 0; i< portals.size(); i++) {
        portals[i]->update(teleportables);
    }
    
    for (int j = 0; j < avatars.size(); j++)
    {
        avatars[j]->presUpdate();
        
        for (int i = 0; i< ladders.size(); i++) {
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
   /*
  for (auto &block : blocks)
    {
      block.update();
    }*/

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
void WorldsBox2d::createBoundsModif(float x, float y, float w, float h) {
    ofPolyline temp;
    temp.addVertex(ofPoint(x,y));
    temp.addVertex(ofPoint(w,y));
    temp.addVertex(ofPoint(w,h));
    temp.addVertex(ofPoint(x,h));
    temp.addVertex(ofPoint(x,y));
    createPlatform(temp);
}
void WorldsBox2d::importPortal(){
    int sizeH = 160;
    int sizeW = 2;

    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::LEFT, 80, 80, sizeW, sizeH));// portal:0
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::LEFT, 240, 80, sizeW, sizeH));// portal:1
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::LEFT, 400, 80, sizeW, sizeH));// portal:2
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::LEFT, 560, 80, sizeW, sizeH));// portal:3
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::LEFT, 800, 80, sizeW, sizeH/2));// portal:4
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::LEFT, 880, 80, sizeW, sizeH/2));// portal:5
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::LEFT, 960, 80, sizeW, sizeH/2));// portal:6
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::LEFT, 1040, 80, sizeW, sizeH/2));// portal:7
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::LEFT, 1200, 80, sizeW, sizeH));// portal:8
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::LEFT, 1360, 80, sizeW, sizeH));// portal:9
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::LEFT, 1520, 80, sizeW, sizeH));// portal:10
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::LEFT, 1680, 80, sizeW, sizeH/2));// portal:11
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::LEFT, 2000, 80, sizeW, sizeH));// portal:12
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::LEFT, 2160, 80, sizeW, sizeH));// portal:13
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::LEFT, 2320, 80, sizeW, sizeH));// portal:14
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::LEFT, 2560, 80, sizeW, sizeH));// portal:15
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::LEFT, 2800, 80, sizeW, sizeH));// portal:16
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::LEFT, 3040, 80, sizeW, sizeH));// portal:17
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::LEFT, 3280, 80, sizeW, sizeH/2));// portal:18
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::LEFT, 80, 80, sizeW, sizeH));// portal:19
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::RIGHT, 399, 80, sizeW, sizeH/2));// portal:20
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::LEFT, 560, 80, sizeW, sizeH/2));// portal:21
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::RIGHT, 719, 80, sizeW, sizeH));// portal:22
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::LEFT, 800, 80, sizeW, sizeH/2));// portal:23
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::LEFT, 880, 80, sizeW, sizeH/2));// portal:24
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::RIGHT, 1119, 80, sizeW, sizeH/2));// portal:25
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::RIGHT, 799, 159, sizeW, sizeH/2));// portal:26
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::RIGHT, 879, 159, sizeW, sizeH/2));// portal:27
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::RIGHT, 959, 159, sizeW, sizeH/2));// portal:28
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::RIGHT, 1039, 159, sizeW, sizeH/2));// portal:29
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::LEFT, 1200, 80, sizeW, sizeH));// portal:30
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::RIGHT, 1679, 80, sizeW, sizeH/2));// portal:31
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::LEFT, 1260, 80, sizeW, sizeH));// portal:32
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::RIGHT, 2479, 80, sizeW, sizeH));// portal:33
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::LEFT, 2560, 80, sizeW, sizeH));// portal:34
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::RIGHT, 2719, 80, sizeW, sizeH));// portal:35
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::LEFT, 2800, 80, sizeW, sizeH));// portal:36
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::RIGHT, 2959, 80, sizeW, sizeH));// portal:37
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::LEFT, 3040, 80, sizeW, sizeH));// portal:38
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::RIGHT, 3199, 80, sizeW, sizeH));// portal:39
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::LEFT, 3280, 80, sizeW, sizeH/2));// portal:40
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::RIGHT, 3359, 80, sizeW, sizeH/2));// portal:41
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::RIGHT, 3280, 159, sizeW, sizeH/2));// portal:42
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::RIGHT, 80, 239, sizeW, sizeH));// portal:43
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::RIGHT, 240, 239, sizeW, sizeH));// portal:44
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::RIGHT, 400, 239, sizeW, sizeH));// portal:45
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::RIGHT, 560, 239, sizeW, sizeH));// portal:46
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::RIGHT, 2560, 239, sizeW, sizeH));// portal:47
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::RIGHT, 2800, 239, sizeW, sizeH/2));// portal:48
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::LEFT, 3040, 240, sizeW, sizeH));// portal:49
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::RIGHT, 3199, 240, sizeW, sizeH));// portal:50
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::LEFT, 3280, 240, sizeW, sizeH/2));// portal:51
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::LEFT, 3280, 240, sizeW, sizeH/2));// portal:52
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::RIGHT, 3280, 319, sizeW, sizeH/2));// portal:53
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::RIGHT, 3360, 240, sizeW, sizeH/2));// portal:54
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::LEFT, 80, 320, sizeW, sizeH));// portal:55
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::LEFT, 240, 320, sizeW, sizeH));// portal:56
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::LEFT, 400, 320, sizeW, sizeH));// portal:57
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::LEFT, 560, 320, sizeW, sizeH));// portal:58
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::LEFT, 720, 320, sizeW, sizeH));// portal:59
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::LEFT, 880, 320, sizeW, sizeH/2));// portal:60
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::LEFT, 1040, 320, sizeW, sizeH));// portal:61
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::LEFT, 1200, 320, sizeW, sizeH));// portal:62
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::LEFT, 1360, 320, sizeW, sizeH/2));// portal:63
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::LEFT, 1520, 320, sizeW, sizeH/2));// portal:64
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::LEFT, 1680, 320, sizeW, sizeH));// portal:65
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::LEFT, 1840, 320, sizeW, sizeH));// portal:66
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::LEFT, 2000, 320, sizeW, sizeH));// portal:67
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::LEFT, 2160, 320, sizeW, sizeH));// portal:68
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::LEFT, 2560, 320, sizeW, sizeH));// portal:69
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::LEFT, 2800, 320, sizeW, sizeH/2));// portal:70
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::LEFT, 80, 320, sizeW, sizeH));// portal:71
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::RIGHT, 239, 320, sizeW, sizeH));// portal:72
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::LEFT, 240, 320, sizeW, sizeH));// portal:73
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::RIGHT, 399, 320, sizeW, sizeH));// portal:74
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::LEFT, 400, 320, sizeW, sizeH));// portal:75
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::RIGHT, 719, 320, sizeW, sizeH));// portal:76
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::LEFT, 720, 320, sizeW, sizeH));// portal:77
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::RIGHT, 879, 320, sizeW, sizeH));// portal:78
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::LEFT, 900, 320, sizeW, sizeH));// portal:79
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::LEFT, 1040, 320, sizeW, sizeH));// portal:80
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::RIGHT, 1359, 320, sizeW, sizeH/2));// portal:81
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::RIGHT, 1359, 400, sizeW, sizeH/2));// portal:82
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::RIGHT, 1439, 479, sizeW, sizeH/2));// portal:83
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::RIGHT, 1519, 320, sizeW, sizeH/2));// portal:84
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::RIGHT, 1440, 399, sizeW, sizeH/2));// portal:85
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::LEFT, 1440, 400, sizeW, sizeH/2));// portal:86
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::LEFT, 1440, 400, sizeW, sizeH/2));// portal:87
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::RIGHT, 1519, 400, sizeW, sizeH/2));// portal:88
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::LEFT, 1520, 320, sizeW, sizeH/2));// portal:89
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::RIGHT, 1520, 399, sizeW, sizeH/2));// portal:90
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::LEFT, 1520, 400, sizeW, sizeH/2));// portal:91
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::LEFT, 1520, 400, sizeW, sizeH/2));// portal:92
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::RIGHT, 1599, 400, sizeW, sizeH/2));// portal:93
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::LEFT, 2000, 320, sizeW, sizeH/2));// portal:94
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::LEFT, 2000, 400, sizeW, sizeH/2));// portal:95
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::LEFT, 2560, 320, sizeW, sizeH));// portal:96
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::LEFT, 2719, 320, sizeW, sizeH));// portal:97
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::LEFT, 2800, 320, sizeW, sizeH));// portal:98
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::RIGHT, 2959, 320, sizeW, sizeH/2));// portal:99
    
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::RIGHT, 3040, 399, sizeW, sizeH));// portal:100
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::LEFT, 3280, 400, sizeW, sizeH/2));// portal:101
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::LEFT, 3280, 400, sizeW, sizeH/2));// portal:102
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::RIGHT, 3359, 400, sizeW, sizeH/2));// portal:103
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::RIGHT, 80, 479, sizeW, sizeH));// portal:104
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::RIGHT, 240, 479, sizeW, sizeH/2));// portal:105
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::RIGHT, 720, 479, sizeW, sizeH));// portal:106
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::RIGHT, 880, 479, sizeW, sizeH));// portal:107
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::RIGHT, 1040, 479, sizeW, sizeH));// portal:108
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::RIGHT, 1360, 479, sizeW, sizeH/2));// portal:109
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::RIGHT, 1440, 479, sizeW, sizeH/2));// portal:110
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::RIGHT, 1520, 479, sizeW, sizeH/2));// portal:111
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::RIGHT, 1600, 479, sizeW, sizeH/2));// portal:112
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::RIGHT, 2560, 479, sizeW, sizeH));// portal:113
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::RIGHT, 2800, 479, sizeW, sizeH/2));// portal:114
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::RIGHT, 3280, 479, sizeW, sizeH/2));// portal:115
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::LEFT, 80, 560, sizeW, sizeH));// portal:116
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::LEFT, 240, 560, sizeW, sizeH/2));// portal:117
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::LEFT, 400, 560, sizeW, sizeH/2));// portal:118
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::LEFT, 460, 560, sizeW, sizeH));// portal:119
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::LEFT, 720, 560, sizeW, sizeH));// portal:120
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::LEFT, 880, 560, sizeW, sizeH));// portal:121
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::LEFT, 1040, 560, sizeW, sizeH));// portal:122
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::LEFT, 1200, 560, sizeW, sizeH));// portal:123
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::LEFT, 1360, 560, sizeW, sizeH));// portal:124
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::LEFT, 1520, 560, sizeW, sizeH));// portal:125
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::LEFT, 1680, 560, sizeW, sizeH/2));// portal:126
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::LEFT, 1760, 560, sizeW, sizeH/2));// portal:127
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::LEFT, 1840, 560, sizeW, sizeH/2));// portal:128
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::LEFT, 2160, 560, sizeW, sizeH));// portal:129
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::LEFT, 2560, 560, sizeW, sizeH/2));// portal:130
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::LEFT, 2800, 560, sizeW, sizeH));// portal:131
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::LEFT, 80, 560, sizeW, sizeH));// portal:132
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::RIGHT, 159, 560, sizeW, sizeH/2));// portal:133
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::RIGHT, 159, 640, sizeW, sizeH/2));// portal:134
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::LEFT, 160, 560, sizeW, sizeH/2));// portal:135
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::RIGHT, 399, 560, sizeW, sizeH/2));// portal:136
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::RIGHT, 319, 639, sizeW, sizeH/2));// portal:137
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::RIGHT, 419, 640, sizeW, sizeH/2));// portal:138
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::LEFT, 420, 640, sizeW, sizeH/2));// portal:139
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::LEFT, 420, 640, sizeW, sizeH/2));// portal:140
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::LEFT, 399, 640, sizeW, sizeH/2));// portal:141
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::LEFT, 400, 560, sizeW, sizeH/2));// portal:142
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::RIGHT, 400, 560, sizeW, sizeH/2));// portal:143
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::LEFT, 400, 640, sizeW, sizeH/2));// portal:144
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::LEFT, 400, 640, sizeW, sizeH/2));// portal:145
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::RIGHT, 479, 640, sizeW, sizeH/2));// portal:146
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::LEFT, 480, 640, sizeW, sizeH/2));// portal:147
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::RIGHT, 559, 560, sizeW, sizeH/2));// portal:148
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::LEFT, 560, 560, sizeW, sizeH));// portal:149
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::RIGHT, 879, 560, sizeW, sizeH));// portal:150
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::LEFT, 880, 560, sizeW, sizeH));// portal:151
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::LEFT, 1040, 560, sizeW, sizeH));// portal:152
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::LEFT, 1359, 560, sizeW, sizeH));// portal:153
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::RIGHT, 1519, 560, sizeW, sizeH));// portal:154
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::LEFT, 1520, 560, sizeW, sizeH));// portal:155
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::LEFT, 1840, 560, sizeW, sizeH));// portal:156
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::RIGHT, 1999, 560, sizeW, sizeH));// portal:157
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::RIGHT, 2319, 560, sizeW, sizeH));// portal:158
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::LEFT, 2560, 560, sizeW, sizeH));// portal:159
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::RIGHT, 2639, 560, sizeW, sizeH/2));// portal:160
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::RIGHT, 2560, 719, sizeW, sizeH));// portal:161
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::LEFT, 2800, 560, sizeW, sizeH));// portal:162
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::RIGHT, 2640, 639, sizeW, sizeH/2));// portal:163
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::RIGHT, 2719, 560, sizeW, sizeH/2));// portal:164
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::RIGHT, 2719, 640, sizeW, sizeH/2));// portal:165
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::RIGHT, 2959, 560, sizeW, sizeH));// portal:166
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::RIGHT, 2800, 719, sizeW, sizeH));// portal:167
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::LEFT, 3360, 560, sizeW, sizeH/2));// portal:168
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::LEFT, 3280, 640, sizeW, sizeH/2));// portal:169
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::LEFT, 3280, 640, sizeW, sizeH/2));// portal:170
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::RIGHT, 3439, 560, sizeW, sizeH));// portal:171
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::LEFT, 1600, 400, sizeW, sizeH/2));// portal:172
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::LEFT, 3360, 560, sizeW, sizeH/2));// portal:173
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::RIGHT, 3280, 719, sizeW, sizeH));// portal:174
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::LEFT, 3040, 560, sizeW, sizeH));// portal:175
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::LEFT, 3040, 560, sizeW, sizeH/2));// portal:176
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::RIGHT, 3040, 719, sizeW, sizeH));// portal:177
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::RIGHT, 3199, 560, sizeW, sizeH));// portal:178
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::RIGHT, 560, 479, sizeW, sizeH));// portal:179
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::RIGHT, 1200, 479, sizeW, sizeH));// portal:180
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::RIGHT, 1840, 479, sizeW, sizeH));// portal:181
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::RIGHT, 2000, 479, sizeW, sizeH));// portal:182
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::RIGHT, 2160, 479, sizeW, sizeH));// portal:183
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::LEFT, 1760, 80, sizeW, sizeH/2));// portal:184
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::RIGHT, 2880, 239, sizeW, sizeH/2));// portal:185
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::LEFT, 1440, 320, sizeW, sizeH/2));// portal:186
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::LEFT, 1600, 320, sizeW, sizeH/2));// portal:187
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::LEFT, 2880, 320, sizeW, sizeH/2));// portal:188
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::RIGHT, 320, 479, sizeW, sizeH/2));// portal:189
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::RIGHT, 2880, 479, sizeW, sizeH/2));// portal:190
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::LEFT, 320, 560, sizeW, sizeH/2));// portal:191
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::LEFT, 480, 560, sizeW, sizeH/2));// portal:192
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::LEFT, 1920, 560, sizeW, sizeH/2));// portal:193
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::LEFT, 2640, 560, sizeW, sizeH/2));// portal:194
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::LEFT, 3040, 640, sizeW, sizeH/2));// portal:195
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::RIGHT, 559, 640, sizeW, sizeH/2));// portal:196
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::LEFT, 240, 640, sizeW, sizeH/2));// portal:197
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::RIGHT, 1679, 160, sizeW, sizeH/2));// portal:198
    portals.push_back(new Portal(Portal::Orientation::HORIZONTAL,Portal::Direction::LEFT, 960, 320, sizeW, sizeH/2));// portal:199
    portals.push_back(new Portal(Portal::Orientation::VERTICAL,Portal::Direction::RIGHT, 2319, 320, sizeW, sizeH));// portal:200
    /*
    //angle; perspective  portals[],NULL
    
    portals[0]->linkTo(portals[15],NULL);
    portals[1]->linkTo(portals[34],NULL);
    portals[2]->linkTo(portals[47],NULL);
    portals[3]->linkTo(portals[35],NULL);
    portals[4]->linkTo(portals[18],NULL);
    portals[5]->linkTo(portals[40],NULL);
    portals[6]->linkTo(portals[42],NULL);
    portals[7]->linkTo(portals[41],NULL);
    portals[8]->linkTo(portals[166],NULL);
    portals[9]->linkTo(portals[131],portals[104]);
    portals[10]->linkTo(portals[162],NULL);
    portals[11]->linkTo(portals[105],NULL);
    portals[12]->linkTo(portals[181],NULL);
    //portals[13]->linkTo(portals[182],portals[]); //
    portals[14]->linkTo(portals[183],NULL);
    portals[15]->linkTo(portals[0],NULL);
    portals[16]->linkTo(portals[58],portals[177]);
    portals[17]->linkTo(portals[55],portals[167]);
    portals[18]->linkTo(portals[4],portals[190]);
    portals[19]->linkTo(portals[22],NULL);
    portals[20]->linkTo(NULL,NULL);
    portals[21]->linkTo(NULL,portals[25]);
    portals[22]->linkTo(portals[19],NULL);
    portals[23]->linkTo(portals[25],NULL);
    portals[24]->linkTo(portals[20],NULL);
    portals[25]->linkTo(portals[23],NULL);
    portals[26]->linkTo(NULL,portals[190]);
    portals[27]->linkTo(NULL,portals[160]);
    portals[28]->linkTo(NULL,portals[163]);
    portals[29]->linkTo(NULL,portals[52]);
    portals[30]->linkTo(portals[33],NULL);
    portals[31]->linkTo(NULL,portals[135]);
    portals[32]->linkTo(NULL,portals[157]);
    portals[33]->linkTo(NULL,portals[30]);
    portals[34]->linkTo(portals[1],portals[37]);
    portals[35]->linkTo(portals[3],portals[49]);
    portals[36]->linkTo(portals[59],portals[99]);
    portals[37]->linkTo(portals[44],NULL);
    portals[38]->linkTo(portals[56],NULL);
    portals[39]->linkTo(portals[68],NULL);
    portals[40]->linkTo(portals[5],portals[160]);
    portals[41]->linkTo(portals[7],portals[52]);
    portals[42]->linkTo(portals[6],portals[163]);
    portals[43]->linkTo(portals[177],NULL);
    portals[44]->linkTo(portals[37],NULL);
    portals[45]->linkTo(portals[65],NULL);
    portals[46]->linkTo(portals[49],NULL);
    portals[47]->linkTo(portals[2],NULL);
    portals[48]->linkTo(portals[64],portals[51]);
    portals[49]->linkTo(portals[46],NULL);
    portals[50]->linkTo(portals[67],NULL);
    portals[51]->linkTo(portals[90],NULL);
    portals[52]->linkTo(portals[85],NULL);
    portals[53]->linkTo(portals[87],portals[169]);
    portals[54]->linkTo(portals[92],portals[168]);
    portals[55]->linkTo(portals[17],NULL);
    portals[56]->linkTo(portals[38],NULL);
    portals[57]->linkTo(portals[43],NULL);
    portals[58]->linkTo(portals[16],NULL);
    portals[59]->linkTo(portals[36],portals[44]);
    portals[60]->linkTo(portals[130],NULL);
    portals[61]->linkTo(portals[159],NULL);
    portals[62]->linkTo(portals[161],NULL);
    portals[63]->linkTo(portals[165],NULL);
    portals[64]->linkTo(portals[48],NULL);
    portals[65]->linkTo(portals[45],NULL);
    portals[66]->linkTo(portals[100],NULL);
    portals[67]->linkTo(portals[50],portals[46]);
    portals[68]->linkTo(portals[39],NULL);
    portals[69]->linkTo(portals[121],NULL);
    portals[70]->linkTo(portals[192],NULL);
    portals[71]->linkTo(portals[200],NULL);*/
}
