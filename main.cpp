#include <cstdio>
#include <ctime>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

#include "ADXCalculator.h"
#include "Agent.h"
#include "DbFiller.h"
#include "DbManager.h"
#include "InventoryManager.h"
#include "Price.h"

int main() {
  /*DbManager dbManager;

  Agent agentSOL3Long = Agent(
      1, 0.03, 1, 0.1, "../rez/SOL/3percent/byBitSOLUSDTLongSellLogDRAL.csv",
      "../rez/SOL/3percent/byBitSOLUSDTLongBuyLogtrs.csv");

  Agent agentSOL3Short = Agent(
      -1, 0.03, 1, 0.1, "../rez/SOL/3percent/byBitSOLUSDTShortSellLogDRAL.csv",
      "../rez/SOL/3percent/byBitSOLUSDTShortBuyLogtrs.csv");

  std::vector<Price> priceList = dbManager.getPrices(
      "test.db", "byBit_SOLUSDT", 1715011199999, 1717344000001);

  for (int i = 0; i < priceList.size(); ++i) {
    agentSOL3Long.run(priceList [ i ]);
    // agentSOL3Short.run(priceList [ i ]);
  }*/

  ADXCalculator adx = ADXCalculator(14);

  std::vector<PriceData> sampleData = {
      {44.53, 43.98, 44.52}, {44.93, 44.36, 44.65}, {45.39, 44.70, 45.22},
      {45.70, 45.13, 45.45}, {45.63, 44.89, 45.49}, {45.52, 44.20, 44.24},
      {44.71, 44.00, 44.62}, {45.15, 43.76, 45.15}, {45.65, 44.46, 44.54},
      {45.87, 45.13, 45.66}, {45.99, 45.27, 45.95}, {46.35, 45.80, 46.33},
      {46.61, 46.10, 46.31}, {46.47, 45.77, 45.94}, {46.30, 45.14, 45.60},
      {45.98, 44.97, 45.70}, {46.68, 46.10, 46.56}, {46.59, 46.14, 46.36},
      {46.88, 46.39, 46.83}, {46.81, 46.41, 46.72}, {46.74, 45.94, 46.65},
      {47.08, 46.68, 46.97}, {46.84, 46.17, 46.56}, {45.81, 45.10, 45.29},
      {45.13, 44.35, 44.94}, {44.96, 44.61, 44.62}, {45.01, 44.20, 44.70},
      {45.67, 44.93, 45.27}, {45.71, 45.01, 45.44}, {45.35, 44.46, 44.76}};

  for (const auto& data : sampleData) {
    // adx.addPriceData(data);
    double currentADX = adx.calculateADX(data);
    std::cout << "currentADX: " << currentADX << std::endl;
  }
  // double currentADX = adx.calculateADX();
  // std::cout << "currentADX: " << currentADX << std::endl;
  return 0;
}
