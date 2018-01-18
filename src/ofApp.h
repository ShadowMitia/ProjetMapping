#pragma once

//#define USE_WIIMOTE

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxPiMapper.h"
#include "ofxBox2d.h"
#include "WorldsBox2d.h"
#include "ScenesMapping.h"
#include "Avatar.h"
#include "Constant.h"
#include "ofxCv.h"
#include "ImportData.h"
#include "ofxGLFWJoystick.h"
#include "shift.h"
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
        
        bool intput[4][6];
        void setup() override;
        void update() override;
        void draw() override;
        
        void keyPressed(int key) override;
        void keyReleased(int key) override;
        void mouseMoved(int x, int y ) override;
        void mouseDragged(int x, int y, int button) override;
        void mousePressed(int x, int y, int button) override;
        void mouseReleased(int x, int y, int button) override;
        void mouseEntered(int x, int y) override;
        void mouseExited(int x, int y) override;
        void windowResized(int w, int h) override;
        void dragEvent(ofDragInfo dragInfo) override;
        void gotMessage(ofMessage msg) override;
        void exit() override;
        
        
        
        //template<class Temp>
        void contactStart(ofxBox2dContactArgs &e);
        void contactEnd(ofxBox2dContactArgs &e);
#ifdef CUSTOM_BOX2D_TIM
        void PreSolve(ofxBox2dPreContactArgs &e);
        void PostSolve(ofxBox2dPostContactArgs &e);
#endif // CUSTOM_BOX2D_TIM
        
        ofxPiMapper mapping;
        WorldsBox2d* worlds; // les mondes Box2d
        
        Scene1* scene1;
        Scene2* scene2;
        
    private:
        void input();
        Shift inputButton[4];
        bool fullscreen = false;
        
#ifdef USE_WIIMOTE
        ofxWiiuse wiiuse;
        void onWiiuseControlEvent(ofxWiiuseControlEventArgs& args) override;
        void onWiiuseButtonEvent(ofxWiiuseButtonEventArgs& args) override;
        void onWiiuseMotionEvent(ofxWiiuseMotionEventArgs& args) override;
        void onWiiuseIRTrackingEvent(ofxWiiuseIRTrackingEventArgs& args) override;
#endif
        
    };
