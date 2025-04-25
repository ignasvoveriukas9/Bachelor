#ifndef AGENT_H
#define AGENT_H

#include <string>
#include <vector>

#include "ADXCalculator.h"
#include "CoastlineTrader.h"
#include "EventDetector.h"
#include "InventoryManager.h"
#include "Price.h"
#include "ProbabilityIndicator.h"

class Agent {
 private:
  EventDetector eventDetector;
  CoastlineTrader coastlineTrader;
  ProbabilityIndicator probabilityIndicator;
  InventoryManager inventoryManager;
  ADXCalculator adx;
  // 1 for long, -1 for short
  int mode;
  double deltaOriginal;
  double fraction = 1;
  std::string sellLog;
  std::string buyLog;

  int tickCount = 1;

  void adjustThresholds();

 public:
  Agent(int mode, double delta, double unitSize, double stopLossLimit,
        std::string sellLog, std::string buyLog);
  // returns current ADX;
  void run(Price price, double globalFraction);
};

#endif  // !AGENT_H
