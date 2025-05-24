#include "Agent.h"

#include <cstdio>
#include <fstream>
#include <locale>

#include "CoastlineTrader.h"
#include "EventDetector.h"
#include "InventoryManager.h"
#include "Price.h"
#include "ProbabilityIndicator.h"

Agent::Agent(int mode, double delta, double unitSize, double stopLossLimit,
             std::string sellLog, std::string buyLog)
    : eventDetector(delta, delta),
      coastlineTrader(mode),
      mode(mode),
      probabilityIndicator(50.0, delta),
      inventoryManager(unitSize, stopLossLimit),
      adx(14),
      deltaOriginal(delta),
      sellLog(sellLog),
      buyLog(buyLog) {}

void Agent::adjustThresholds() {
  // double inventorySize = inventoryManager.getInventorySize() * (double)mode;
  double inventoryCost = inventoryManager.getInventoryCost() * (double)mode;

  double inventorySize = inventoryCost / inventoryManager.getOriginalUnitSize();

  if (inventorySize >= 15.0 && inventorySize < 30.0) {
    eventDetector.updateDelta(0.75 * deltaOriginal, 1.5 * deltaOriginal);
    fraction = 0.5;
  } else if (inventorySize >= 30.0) {
    eventDetector.updateDelta(0.5 * deltaOriginal, 2.0 * deltaOriginal);
    fraction = 0.25;
  } else if (inventorySize <= -15.0 && inventorySize > -30.0) {
    eventDetector.updateDelta(1.5 * deltaOriginal, 0.75 * deltaOriginal);
    fraction = 0.5;
  } else if (inventorySize <= -30.0) {
    eventDetector.updateDelta(2.0 * deltaOriginal, 0.5 * deltaOriginal);
    fraction = 0.25;
  } else {
    eventDetector.updateDelta(deltaOriginal, deltaOriginal);
    fraction = 1.0;
  }
}

double Agent::getInventoryValue(Price price) {
  return inventoryManager.getInventorySize() * price.price * mode;
}

double Agent::run(Price price, double globalFraction, double cashAvailable) {
  double updatedCashAvailable = cashAvailable;
  int intrinsicEvent = eventDetector.detectEvent(price.price);
  int action =
      coastlineTrader.run(intrinsicEvent, price.price, inventoryManager);

  int probabilityIndicatorEvent =
      eventDetector.detectProbabilityIndicatorEvent(price.price);
  probabilityIndicator.updateProbabilityIndicator(probabilityIndicatorEvent);

  if (action == 1) {
    inventoryManager.updateUnitSize(
        probabilityIndicator.getProbabilityIndicator());
    updatedCashAvailable = inventoryManager.buyOrder(
        price, fraction * globalFraction, mode, buyLog, updatedCashAvailable);
    adjustThresholds();
  } else if (action == -1) {
    updatedCashAvailable = inventoryManager.sellPosition(price, mode, sellLog,
                                                         updatedCashAvailable);
    adjustThresholds();
  }

  /*if (inventoryManager.stopLoss(price, mode)) {
    // printf("stopLoss triggerd");
    updatedCashAvailable = inventoryManager.sellPosition(price, mode, sellLog,
                                                         updatedCashAvailable);
  }*/

  if (inventoryManager.trailingStop(price, mode)) {
    // printf("trailingStop triggerd\r\n");
    updatedCashAvailable = inventoryManager.sellPosition(price, mode, sellLog,
                                                         updatedCashAvailable);
  }

  /*updatedCashAvailable = inventoryManager.dynamicPositionReductionLinear(
      price, mode, 0.2, 0.05, 0.10, sellLog, updatedCashAvailable);*/

  /*updatedCashAvailable = inventoryManager.dynamicPositionReductionExponential(
      price, mode, 0.25, 2.5, sellLog, 0.80, updatedCashAvailable);*/

  /*updatedCashAvailable = inventoryManager.dynamicStopLoss(
      price, mode, probabilityIndicator.getProbabilityIndicator(), 0.30, 0.40,
      sellLog, updatedCashAvailable);*/

  return updatedCashAvailable;
}
