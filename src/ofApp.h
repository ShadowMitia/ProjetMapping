#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxPiMapper.h"
#include "ofxBox2d.h"
#include "EditorPlatform.h"
#include "WorldsBox2d.h"
#include "ScenesMapping.h"
#include "PhysicalizedElement/Avatar.h"
#include "LightSystem2D.h"
#include "Constant.h"



class ofApp : public ofBaseApp{


 public:
  
  void setup();
  void update();
  void draw();

  void keyPressed(int key);
  void keyReleased(int key);
  void mouseMoved(int x, int y );
  void mouseDragged(int x, int y, int button);
  void mousePressed(int x, int y, int button);
  void mouseReleased(int x, int y, int button);
  void mouseEntered(int x, int y);
  void mouseExited(int x, int y);
  void windowResized(int w, int h);
  void dragEvent(ofDragInfo dragInfo);
  void gotMessage(ofMessage msg);
    
    //template<class Temp>
    void contactStart(ofxBox2dContactArgs &e);
    void contactEnd(ofxBox2dContactArgs &e);
#ifdef CUSTOM_BOX2D_TIM
	void PreSolve(ofxBox2dPreContactArgs &e);
	void PostSolve(ofxBox2dPostContactArgs &e);
#endif // CUSTOM_BOX2D_TIM

  ofxPiMapper mapping;
  WorldsBox2d* worlds; // les mondes Box2d

  ofx::LightSystem2D* lightSystem;


  
  Scene1* scene1;
  Scene2* scene2;
  EditorPlatform editorPlatform;
    

    
};
