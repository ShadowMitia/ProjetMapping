#ifndef TIMER_H
#define TIMER_H

#include "ofMain.h"

class Timer {

  uint64_t startTime = 0;
  bool isPlaying = false;

public:
  Timer() = default;

  uint64_t getStartTime() {
    return startTime;
  }

  void start() {
    isPlaying = true;
    startTime = ofGetElapsedTimeMillis();
  }

  bool isStarted() {
    return isPlaying;
  }

  uint64_t getElapsedMillis() {
    if (isPlaying){
      return ofGetElapsedTimeMillis() - startTime;
    } else {
      return 0;
    }
  }

  void stop() {
    startTime = 0;
    isPlaying = false;
  }

  void reset() {
    startTime = ofGetElapsedTimeMillis();
  }
};


#endif /* TIMER_H */
