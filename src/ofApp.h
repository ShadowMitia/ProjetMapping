#pragma once

//#define USE_WIIMOTE

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxPiMapper.h"
#include "ofxBox2d.h"
#include "WorldsBox2d.h"
#include "ScenesMapping.h"
#include "PhysicalizedElement/Avatar.h"
#include "LightSystem2D.h"
#include "Constant.h"
#include "ofxCv.h"

#include "ofxGLFWJoystick.h"

//#define USE_WIIMOTE

#ifdef USE_WIIMOTE
#include "ofxWiiuse.h"
#endif

#ifdef USE_WIIMOTE
class ofApp : public ofBaseApp, public ofxWiiuseListener {
#else
class ofApp : public ofBaseApp {
#endif


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
  void exit();
  

    
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

private:
  void input();
  bool inputButton[1][6] = { false };


  bool fullscreen = false;

#ifdef USE_WIIMOTE
  ofxWiiuse wiiuse;

  void onWiiuseControlEvent(ofxWiiuseControlEventArgs& args) override;
  void onWiiuseButtonEvent(ofxWiiuseButtonEventArgs& args) override;
  void onWiiuseMotionEvent(ofxWiiuseMotionEventArgs& args) override;
  void onWiiuseIRTrackingEvent(ofxWiiuseIRTrackingEventArgs& args) override;
#endif
    
};
