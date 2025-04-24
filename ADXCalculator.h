#ifndef ADXCALCULATOR_H
#define ADXCALCULATOR_H

#include <algorithm>
#include <cmath>
#include <vector>

struct PriceData {
  double high;
  double low;
  double close;
};

class ADXCalculator {
 private:
  int period;                     // Typically 14
  std::vector<double> trueRange;  // first period amount
  std::vector<double> plusDMs;    // first period amount
  std::vector<double> minusDMs;   // first period amount
  std::vector<double> dXs;        // first first period amount
  bool firstPrice = true;
  PriceData previousPrice;
  double currentTrueRange;
  double currentPlusDM;
  double currentMinusDM;
  double previousSmoothedTr = -1.0;
  double previousSmoothedPlusDM = -1.0;
  double previousSmoothedMinusDM = -1.0;
  double lastADX = 0.0;

  double wildersSmooth(double current, double previous, int period);

 public:
  ADXCalculator(int period = 14) : period(period) {}

  void addPriceData(const PriceData& data);
  double calculateDX();
  double calculateADX(const PriceData& data);
};

#endif  // !ADXCALCULATOR_H
