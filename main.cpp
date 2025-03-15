#include <cstdio>
#include <ctime>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

#include "Agent.h"
#include "DbFiller.h"
#include "DbManager.h"
#include "Price.h"

int main() {
  DbManager dbManager;

  Agent agentSOL3Long =
      Agent(1, 0.03, 1, 0.1, "../rez/SOL/3percent/byBitSOLUSDTLongSellLog.csv",
            "../rez/SOL/3percent/byBitSOLUSDTLongBuyLog.csv");

  Agent agentSOL3Short = Agent(
      -1, 0.03, 1, 0.1, "../rez/SOL/3percent/byBitSOLUSDTShortSellLog.csv",
      "../rez/SOL/3percent/byBitSOLUSDTShortBuyLog.csv");

  std::vector<Price> priceList = dbManager.getPrices(
      "test.db", "byBit_SOLUSDT", 1715011199999, 1717344000001);

  for (int i = 0; i < priceList.size(); ++i) {
    agentSOL3Long.run(priceList [ i ]);
    agentSOL3Short.run(priceList [ i ]);
  }

  return 0;
}
