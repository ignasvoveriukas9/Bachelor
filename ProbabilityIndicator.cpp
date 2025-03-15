#include "ProbabilityIndicator.h"

#include <cmath>
#include <cstdio>

ProbabilityIndicator::ProbabilityIndicator(double K, double delta) {
  weight = exp(-2.0 / (K + 1));
  H1 = computeH1(delta);
  H2 = computeH2(delta);
  this->K = K;
}

double ProbabilityIndicator::computeH1(double delta) {
  return -exp(-delta * 2.525729 / delta) * log(exp(-delta * 2.525729 / delta)) -
         (1.0 - exp(-delta * 2.525729 / delta)) *
             log(1.0 - exp(-delta * 2.525729 / delta));
}

double ProbabilityIndicator::computeH2(double delta) {
  return exp(-delta * 2.525729 / delta) *
             pow((log(exp(-delta * 2.525729 / delta))), 2) -
         (1.0 - exp(-delta * 2.525729 / delta)) *
             pow(log(1.0 - exp(-delta * 2.525729 / delta)), 2) -
         H1 * H1;
}

double ProbabilityIndicator::cumulativeDistributionOfNormalDistribution(
    double x) {
  return 0.5 * (1.0 + erf(x / sqrt(2.0)));
}

void ProbabilityIndicator::updateProbabilityIndicator(int event) {
  if (event == 1 || event == -1) {  // Directional change
    // printf("dc\r\n");
    surprise = (weight * 0.08338161) + ((1.0 - weight) * surprise);
  } else if (event == 2 || event == -2) {  // Overshoot
    // printf("over\r\n");
    surprise = (weight * 2.525729) + ((1.0 - weight) * surprise);
  } else {
    return;
  }
  probabilityIndicator = 1 - cumulativeDistributionOfNormalDistribution(
                                 sqrt(K) * (surprise - H1) / sqrt(H2));

  // printf("Indic: %f\r\n", probabilityIndicator);
}
