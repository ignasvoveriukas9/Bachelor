#ifndef AGENT_H
#define AGENT_H

#include <string>

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
  // 1 for long, -1 for short
  int mode;
  double deltaOriginal;
  double fraction = 1;
  std::string sellLog;
  std::string buyLog;

  void adjustThresholds();

 public:
  Agent(int mode, double delta, double unitSize, std::string sellLog,
        std::string buyLog);
  void run(Price price);
};

#endif  // !AGENT_H
