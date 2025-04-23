#include "InventoryManager.h"

#include <cmath>
#include <cstdio>
#include <cwchar>
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

  printf("buy position of size: %f, for %f, price%f\r\n",
         currentUnitSize * fraction, currentUnitSize * fraction * price.price,
         price.price);

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

double InventoryManager::unrealizedLoss(Price price, int mode) {
  if (currentInventorySize == 0.0 || currentInventoryCost == 0.0) {
    return 0;
  }

  return (currentInventoryCost - (currentInventorySize * price.price)) /
         currentInventoryCost * mode;
}

bool InventoryManager::stopLoss(Price price, int mode) {
  if (currentInventorySize == 0.0 || currentInventoryCost == 0.0) {
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

void InventoryManager::dynamicPositionReductionLinear(Price price, int mode,
                                                      double startLoss,
                                                      double step,
                                                      double reduction,
                                                      std::string log) {
  if (currentInventorySize > 0.0 && currentInventoryCost > 0.0) {
    double loss = unrealizedLoss(price, mode);

    // addujust to start from a specific loss
    // (e.g. startLoss 0.2, step 0.5, reduction 0.1, at loss 0.1 sell 0, at loss
    // 0.2 sell 0, at loss 0.25 sell 0.1, at loss 0.3 sell 0.2 ...)
    loss -= startLoss;

    int mult = (int)(loss / step);

    // sell
    if (mult >= 1) {
      if ((mult * reduction) >= 1) {
        printf("sell all from loss\r\n");
        sellPosition(price, mode, log);
        return;
      }

      double sellAmount = ((mult * reduction) * currentInventorySize);
      double sellCost = sellAmount * price.price;
      double buyCost =
          ((currentInventoryCost / currentInventorySize) * sellAmount);
      double profit = (double)mode * sellCost - (double)mode * buyCost;

      printf(
          "sell position of size: %f, for %f, for profit %f, "
          "mult %d, price%f\r\n",
          mode * sellAmount, sellCost, profit, mult, price.price);

      std::fstream fout;

      fout.open(log, std::ios::out | std::ios::app);
      fout << price.ticker << "," << price.time << ","
           << std::to_string(mode * sellAmount) << ","
           << std::to_string(buyCost) << "," << std::to_string(sellCost) << ","
           << std::to_string(profit) << ","
           << std::to_string(profit / buyCost * 100) << "\r\n";

      fout.close();

      currentInventorySize -= sellAmount;
      currentInventoryCost -= sellCost;
    }
  }
}

void InventoryManager::dynamicPositionReductionExponetial(Price price, int mode,
                                                          double startLoss,
                                                          double k,
                                                          std::string log,
                                                          double minRemaining) {
  if (unrealizedLoss(price, mode) <= startLoss) {
    return;
  } else if (unrealizedLoss(price, mode) >= 1.0 ||
             (currentInventorySize / originalUnitSize) < 0.2) {
    printf("sell all from loss\r\n");
    sellPosition(price, mode, log);
    return;
  } else {
    double excessLoss = unrealizedLoss(price, mode) - startLoss;
    double sellPct = 1.0 - std::max(exp(-k * excessLoss), minRemaining);

    double sellAmount = currentInventorySize * sellPct;
    double sellCost = sellAmount * price.price;
    double buyCost =
        ((currentInventoryCost / currentInventorySize) * sellAmount);
    double profit = (double)mode * sellCost - (double)mode * buyCost;
    printf(
        "sell position of size: %f, for %f, for profit %f, price%f, loss%f, "
        "excessLoss%f, currentInventorySize%f, currentInventoryCost%f\r\n",
        mode * sellAmount, sellCost, profit, price.price,
        unrealizedLoss(price, mode), excessLoss, currentInventorySize,
        currentInventoryCost);

    std::fstream fout;

    fout.open(log, std::ios::out | std::ios::app);
    fout << price.ticker << "," << price.time << ","
         << std::to_string(mode * sellAmount) << "," << std::to_string(buyCost)
         << "," << std::to_string(sellCost) << "," << std::to_string(profit)
         << "," << std::to_string(profit / buyCost * 100) << "\r\n";

    fout.close();

    currentInventorySize -= sellAmount;
    currentInventoryCost -= sellCost;
  }
}

void InventoryManager::dynamicStopLoss(Price price, int mode,
                                       double probabilityIndicator,
                                       double minLoss, double maxLoss,
                                       std::string log) {
  // linear interpolation
  if (unrealizedLoss(price, mode) >=
      (minLoss + ((maxLoss - minLoss) * probabilityIndicator))) {
    printf("sell from dynamics stoploss");
    sellPosition(price, mode, log);
  }
}
