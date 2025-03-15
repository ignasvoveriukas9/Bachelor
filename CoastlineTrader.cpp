#include "CoastlineTrader.h"

#include <cstdio>

#include "InventoryManager.h"

CoastlineTrader::CoastlineTrader(int mode) : mode(mode) {}

int CoastlineTrader::run(int event, double price,
                         InventoryManager &inventoryManager) {
  // Long
  if (mode == 1) {
    if (event < 0) {
      return 1;
    } else if (event == 2 && inventoryManager.isProfitable(price, mode)) {
      return -1;
    }
  } else {  // Short
    if (event > 0) {
      return 1;
    } else if (event == -2 && inventoryManager.isProfitable(price, mode)) {
      return -1;
    }
  }

  return 0;
}
