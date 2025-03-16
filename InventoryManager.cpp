#include "InventoryManager.h"

#include <cstdio>
#include <fstream>
#include <string>

#include "Price.h"

InventoryManager::InventoryManager(double unitSize, double stopLossLimit)
    : originalUnitSize(unitSize),
      currentUnitSize(unitSize),
      stopLossLimit(stopLossLimit) {}

void InventoryManager::updateUnitSize(double probabilityIndicator) {
  if (probabilityIndicator <= 0.1) {
    currentUnitSize = originalUnitSize * 0.1;
  } else if (probabilityIndicator <= 0.5) {
    currentUnitSize = originalUnitSize * 0.5;
  } else {
    currentUnitSize = originalUnitSize;
  }
}

void InventoryManager::buyOrder(Price price, double fraction, int mode,
                                std::string log) {
  currentInventorySize += currentUnitSize * fraction;
  currentInventoryCost += currentUnitSize * fraction * price.price;

  std::fstream fout;

  fout.open(log, std::ios::out | std::ios::app);
  fout << price.ticker << "," << price.time << ","
       << std::to_string(mode * currentUnitSize * fraction) << ","
       << std::to_string(price.price) << ","
       << std::to_string(mode * currentUnitSize * fraction * price.price) << ","
       << std::to_string(currentInventorySize) << ","
       << std::to_string(currentInventoryCost) << ","
       << std::to_string(currentInventorySize * price.price) << "\r\n";

  fout.close();
}

bool InventoryManager::isProfitable(double price, int mode) {
  if ((double)mode * currentInventoryCost <
      (double)mode * currentInventorySize * originalUnitSize * price) {
    return true;
  }
  return false;
}

void InventoryManager::sellPosition(Price price, int mode, std::string log) {
  double sellCost = currentInventorySize * originalUnitSize * price.price;
  double profit = (double)mode * sellCost - (double)mode * currentInventoryCost;

  printf("sell position of size: %f, for %f, for profit %f\r\n",
         mode * currentInventorySize, sellCost, profit);

  std::fstream fout;

  fout.open(log, std::ios::out | std::ios::app);
  fout << price.ticker << "," << price.time << ","
       << std::to_string(mode * currentInventorySize) << ","
       << std::to_string(currentInventoryCost) << ","
       << std::to_string(sellCost) << "," << std::to_string(profit) << ","
       << std::to_string(profit / currentInventoryCost * 100) << "\r\n";

  fout.close();

  currentInventorySize = 0;
  currentInventoryCost = 0;
  stopValue = 0;
}

bool InventoryManager::stopLoss(Price price, int mode) {
  if (currentInventorySize == 0 || currentInventoryCost == 0) {
    return false;
  }

  double loss = (currentInventoryCost - (currentInventorySize * price.price)) /
                currentInventoryCost * mode;
  if (loss >= stopLossLimit) {
    return true;
  }
  return false;
}

bool InventoryManager::trailingStop(Price price, int mode) {
  // skip if no inventory
  if (currentInventorySize == 0 || currentInventoryCost == 0) {
    return false;
  }
  // set initial stop value
  if (stopValue == 0.0) {
    stopValue =
        (currentInventorySize * price.price) * (1.0 - (stopLossLimit * mode));
    return false;
  }
  // update stop value if the price moves in profitable direction
  if (((currentInventorySize * price.price) * (1.0 - (stopLossLimit * mode)) *
       mode) > (stopValue * mode)) {
    stopValue =
        (currentInventorySize * price.price) * (1.0 - (stopLossLimit * mode));
  }
  // return true if price hits stopValue
  if ((currentInventorySize * price.price * mode) <= (stopValue * mode)) {
    return true;
  }

  return false;
}
