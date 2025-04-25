#ifndef PRICEDATAPROVIDER_H
#define PRICEDATAPROVIDER_H

#include <cstddef>
#include <cstdio>
#include <sstream>
#include <string>
#include <vector>

#include "Price.h"

class PriceDataProvider {
 private:
 public:
  std::vector<Price> getPrices(char *dataFile, std::string ticker,
                               int64_t timeFrom, int64_t timeTo);
};
#endif  // PRICEDATAPROVIDER_H
