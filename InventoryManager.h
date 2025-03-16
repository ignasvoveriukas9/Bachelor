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

 public:
  InventoryManager(double unitSize, double stopLossLimit);
  double getUnitSize() { return currentUnitSize; }
  double getInventorySize() { return currentInventorySize; }
  double getInventoryCost() { return currentInventoryCost; }
  void updateUnitSize(double probabilityIndicator);
  void buyOrder(Price price, double fraction, int mode, std::string log);
  bool isProfitable(double price, int mode);
  void sellPosition(Price price, int mode, std::string log);
  bool stopLoss(Price price, int mode);
  bool trailingStop(Price price, int mode);
};

#endif  // !INVENTORYMANAGER_H
