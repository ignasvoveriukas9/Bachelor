#include "EventDetector.h"

EventDetector::EventDetector(double deltaUp, double deltaDown)
    : deltaUp(deltaUp), deltaDown(deltaDown) {}

void EventDetector::init(double price) {
  mode = 1;
  extreme = price;
  referance = price;
  initalized = true;
}

void EventDetector::initProb(double price) {
  modeProb = 1;
  extremeProb = price;
  referanceProb = price;
  initalizedProb = true;
}

void EventDetector::updateDelta(double deltaUp, double deltaDown) {
  this->deltaUp = deltaUp;
  this->deltaDown = deltaDown;
}

int EventDetector::detectEvent(double price) {
  if (!initalized) {
    init(price);
  }

  if (mode == 1) {
    if (price > extreme) {
      extreme = price;
      if (((price - referance) / referance) > deltaUp) {
        referance = extreme;
        // Up Overshoot
        return 2;
      }
    } else if (((price - extreme) / extreme) < -deltaDown) {
      extreme = price;
      referance = price;
      mode = -1;
      // Directional Change Down
      return 1;
    }
  } else if (mode == -1) {
    if (price < extreme) {
      extreme = price;
      if (((price - referance) / referance) < -deltaDown) {
        referance = extreme;
        // Down Overshoot
        return -2;
      }
    } else if (((price - extreme) / extreme) > deltaUp) {
      extreme = price;
      referance = price;
      mode = 1;
      // Directional Change Up
      return -1;
    }
  }
  // No Event
  return 0;
}

int EventDetector::detectProbabilityIndicatorEvent(double price) {
  if (!initalizedProb) {
    initProb(price);
  }

  if (modeProb == 1) {
    if (price > extremeProb) {
      extremeProb = price;
      if (((price - referanceProb) / referanceProb) > (deltaUp * 2.525729)) {
        referanceProb = extremeProb;
        // Up Overshoot
        return 2;
      }
    } else if (((price - extremeProb) / extremeProb) < -deltaDown) {
      extremeProb = price;
      referanceProb = price;
      modeProb = -1;
      // Directional Change Down
      return 1;
    }
  } else if (modeProb == -1) {
    if (price < extremeProb) {
      extremeProb = price;
      if (((price - referanceProb) / referanceProb) < (-deltaDown * 2.525729)) {
        referanceProb = extremeProb;
        // Down Overshoot
        return -2;
      }
    } else if (((price - extremeProb) / extremeProb) > deltaUp) {
      extremeProb = price;
      referanceProb = price;
      modeProb = 1;
      // Directional Change Up
      return -1;
    }
  }
  // No Event
  return 0;
}
