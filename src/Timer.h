#ifndef TIMER_H
#define TIMER_H

#include "ofMain.h"

class Timer {

  uint64_t startTime = 0;
  bool isRunning = false;

public:
  Timer() = default;

  uint64_t getStartTime() {
    return startTime;
  }

  void start() {
    isRunning = true;
    startTime = ofGetElapsedTimeMillis();
  }

  bool isStarted() const {
    return isRunning;
  }

  uint64_t getElapsedMillis() const {
    if (isRunning){
      return ofGetElapsedTimeMillis() - startTime;
    } else {
      return 0;
    }
  }

  void stop() {
    startTime = 0;
    isRunning = false;
  }

  void reset() {
    startTime = ofGetElapsedTimeMillis();
  }
};


#endif /* TIMER_H */
