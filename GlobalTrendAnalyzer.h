#ifndef GLOBALTRENDANALYZER_H
#define GLOBALTRENDANALYZER_H

#include <map>
#include <string>
#include <vector>

#include "ADXCalculator.h"
#include "Price.h"

struct Pair {
  std::vector<PriceData> prices;
  ADXCalculator adxCalculator;
  double currentADX;
};

class GlobalTrendAnalyzer {
 private:
  std::map<std::string, Pair> pairs;

 public:
  void addPair(std::string ticker);
  bool addPrice(std::string ticker, Price price);
  // double getCurrentADX(std::string ticker);
  double getBuyFraction();
};

#endif  // !GLOBALTRENDANALYZER_H
