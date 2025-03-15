#ifndef EVENTDETECTOR_H
#define EVENTDETECTOR_H

#include <sys/types.h>

#include <random>
class EventDetector {
 private:
  int mode, modeProb;
  double extreme, extremeProb;
  double referance, referanceProb;
  bool initalized = false;
  bool initalizedProb = false;
  double deltaUp, deltaDown;

  void init(double price);
  void initProb(double price);

 public:
  EventDetector(double deltaUp, double deltaDown);
  int detectEvent(double price);
  int detectProbabilityIndicatorEvent(double price);
  void updateDelta(double deltaUp, double deltaDown);
};

#endif
