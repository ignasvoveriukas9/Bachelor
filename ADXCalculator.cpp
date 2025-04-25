#include "ADXCalculator.h"

#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <numeric>
#include <ostream>

double ADXCalculator::wildersSmooth(double current, double previous,
                                    int period) {
  return previous - (previous / period) + current;
}

void ADXCalculator::addPriceData(const PriceData& data) {
  if (firstPrice) {
    previousPrice = data;
    firstPrice = false;
    return;
  }

  // Calculate True Range and Directional Movments when we have enought data;
  // True Range
  double tr1 = data.high - data.low;
  double tr2 = std::abs(data.high - previousPrice.close);
  double tr3 = std::abs(data.low - previousPrice.close);
  double tr = std::max({tr1, tr2, tr3});
  currentTrueRange = tr;
  if (trueRange.size() < period) {
    trueRange.push_back(tr);
  }

  // +DM and -DM
  double upMove = data.high - previousPrice.high;
  double downMove = previousPrice.low - data.low;

  if (upMove > downMove && upMove > 0) {
    currentPlusDM = upMove;
    currentMinusDM = 0.0;
  } else if (downMove > upMove && downMove > 0) {
    currentPlusDM = 0.0;
    currentMinusDM = downMove;
  } else {
    currentPlusDM = 0.0;
    currentMinusDM = 0.0;
  }

  if (plusDMs.size() < period || minusDMs.size() < period) {
    plusDMs.push_back(currentPlusDM);
    minusDMs.push_back(currentMinusDM);
  }

  previousPrice = data;

  /*std::cout << "TR: " << currentTrueRange << " +DM1: " << currentPlusDM
            << " -DM1: " << currentMinusDM;*/
}

double ADXCalculator::calculateDX() {
  if (trueRange.size() < period || plusDMs.size() < period ||
      minusDMs.size() < period) {
    /*std::cout << " no data " << std::endl;*/
    return 0.0;  // Not enought data
  }

  double smoothedTR;
  double smoothedPlusDM;
  double smoothedMinusDM;

  // Init average (first period)
  if (previousSmoothedTr == -1.0 || previousSmoothedPlusDM == -1.0 ||
      previousSmoothedMinusDM == -1.0) {
    previousSmoothedTr = 0.0;
    previousSmoothedPlusDM = 0.0;
    previousSmoothedMinusDM = 0.0;

    for (int i = 0; i < period; i++) {
      previousSmoothedTr += trueRange [ i ];
      previousSmoothedPlusDM += plusDMs [ i ];
      previousSmoothedMinusDM += minusDMs [ i ];
    }

    smoothedTR = previousSmoothedTr;
    smoothedPlusDM = previousSmoothedPlusDM;
    smoothedMinusDM = previousSmoothedMinusDM;
  } else {  // Subsequent values use wildersSmooth
    smoothedTR = wildersSmooth(currentTrueRange, previousSmoothedTr, period);
    smoothedPlusDM =
        wildersSmooth(currentPlusDM, previousSmoothedPlusDM, period);
    smoothedMinusDM =
        wildersSmooth(currentMinusDM, previousSmoothedMinusDM, period);

    previousSmoothedTr = smoothedTR;
    previousSmoothedPlusDM = smoothedPlusDM;
    previousSmoothedMinusDM = smoothedMinusDM;
  }

  // Calculate +DI and -DI
  double plusDI = 100 * (smoothedPlusDM / smoothedTR);
  double minusDI = 100 * (smoothedMinusDM / smoothedTR);

  // Calculate DX
  if ((plusDI + minusDI) == 0.0) return 0.0;
  double dx = 100 * (std::abs(minusDI - plusDI) / (plusDI + minusDI));

  if (dXs.size() < period) {
    dXs.push_back(dx);
  }

  /*std::cout << " TR14: " << smoothedTR << " +DM14 " << smoothedPlusDM
            << " -DM14 " << smoothedMinusDM << " DX " << dx << std::endl;*/

  return dx;
}

double ADXCalculator::calculateADX(const PriceData& data) {
  addPriceData(data);

  if (dXs.size() < (period - 1)) {
    calculateDX();
    return 0.0;  // not enought DX
  }
  // First ADX is avg of first period DX values
  if (lastADX == 0.0) {
    calculateDX();
    double sum = std::accumulate(dXs.begin(), dXs.begin() + period, 0.0);
    lastADX = sum / period;
    return lastADX;
  }

  // If we have enought DX values, smooth them
  double currentDX = calculateDX();
  lastADX = (lastADX * (period - 1) + currentDX) / period;

  return lastADX;
}
