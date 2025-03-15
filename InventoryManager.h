#ifndef INVENTORYMANAGER_H
#define INVENTORYMANAGER_H

#include <string>

#include "Price.h"
class InventoryManager {
 private:
  double originalUnitSize;
  double currentUnitSize;
  // size in originalUnitSize
  double currentInventorySize = 0;
  double currentInventoryCost = 0;

 public:
  InventoryManager(double UnitSize);
  double getUnitSize() { return currentUnitSize; }
  double getInventorySize() { return currentInventorySize; }
  double getInventoryCost() { return currentInventoryCost; }
  void updateUnitSize(double probabilityIndicator);
  void buyOrder(Price price, double fraction, int mode, std::string log);
  bool isProfitable(double price, int mode);
  void sellPosition(Price price, int mode, std::string log);
};

#endif  // !INVENTORYMANAGER_H
