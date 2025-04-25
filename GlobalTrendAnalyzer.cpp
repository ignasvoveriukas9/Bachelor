#include "GlobalTrendAnalyzer.h"

#include <algorithm>
#include <iostream>
#include <ostream>

#include "ADXCalculator.h"

void GlobalTrendAnalyzer::addPair(std::string ticker) {
  Pair pair = {{}, ADXCalculator(14), 0.0};
  pairs [ ticker ] = pair;
}

bool GlobalTrendAnalyzer::addPrice(std::string ticker, Price price) {
  if (pairs.count(ticker) < 1) {
    std::cerr << "No pair with ticker: " << ticker << std::endl;
    return false;
  }

  Pair pair = pairs [ ticker ];

  if (pair.prices.size() < 15) {
    pair.prices.push_back({price.high, price.low, price.close});
  }

  if (pair.prices.size() == 15) {
    PriceData OHLC15;
    OHLC15.close = pair.prices.back().close;
    OHLC15.low = pair.prices [ 0 ].low;
    OHLC15.high = pair.prices [ 0 ].high;

    for (const auto& candle : pair.prices) {
      OHLC15.high = std::max(OHLC15.high, candle.high);
      OHLC15.low = std::min(OHLC15.low, candle.low);
    }

    pair.currentADX = pair.adxCalculator.calculateADX(OHLC15);
    pair.prices.clear();

    std::cout << ticker << " currentADX: " << pair.currentADX;

    pairs [ ticker ] = pair;
    return true;
  }

  pairs [ ticker ] = pair;
  return false;
}

double GlobalTrendAnalyzer::getBuyFraction() {
  double globalADX = 0.0;
  for (auto const& [ key, value ] : pairs) {
    globalADX += value.currentADX;
  }
  globalADX = globalADX / pairs.size();

  return (1.0 - std::max(0.0, (globalADX - 25) / 100));
}
