#ifndef INVENTORYMANAGER_H
#define INVENTORYMANAGER_H

#include <string>

#include "Price.h"
class InventoryManager {
 public:
  double originalUnitSize;
  double currentUnitSize;
  // size in originalUnitSize
  double currentInventorySize = 0;
  double currentInventoryCost = 0;
  double stopLossLimit;
  double stopValue = 0;
  double unrealizedLoss(Price price, int mode);

 public:
  InventoryManager(double unitSize, double stopLossLimit);
  double getUnitSize() { return currentUnitSize; }
  double getInventorySize() { return currentInventorySize; }
  double getInventoryCost() { return currentInventoryCost; }
  double getOriginalUnitSize() { return originalUnitSize; }
  void updateUnitSize(double probabilityIndicator);
  // returns updated cashAvailable
  double buyOrder(Price price, double fraction, int mode, std::string log,
                  double cashAvailable);
  bool isProfitable(double price, int mode);
  // returns updated cashAvailable
  double sellPosition(Price price, int mode, std::string log,
                      double cashAvailable);
  bool stopLoss(Price price, int mode);
  bool trailingStop(Price price, int mode);
  // returns updated cashAvailable
  double dynamicPositionReductionLinear(Price price, int mode, double startLoss,
                                        double step, double reduction,
                                        std::string log, double cashAvailable);
  // returns updated cashAvailable
  double dynamicPositionReductionExponential(Price price, int mode,
                                             double startLoss, double k,
                                             std::string log, double cutoff,
                                             double cashAvailable);
  double dynamicStopLoss(Price price, int mode, double probabilityIndicator,
                         double minLoss, double maxLoss, std::string log,
                         double cashAvailable);
};

#endif  // !INVENTORYMANAGER_H
