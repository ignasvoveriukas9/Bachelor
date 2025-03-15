#ifndef PROBABILITYINDICATOR_H
#define PROBABILITYINDICATOR_H

class ProbabilityIndicator {
 private:
  double probabilityIndicator = 1;
  double surprise = 0;
  double weight;
  double H1, H2;
  double K;

  double computeH1(double delta);
  double computeH2(double delta);
  double cumulativeDistributionOfNormalDistribution(double x);

 public:
  ProbabilityIndicator(double K, double delta);
  void updateProbabilityIndicator(int event);
  double getProbabilityIndicator() { return probabilityIndicator; }
};

#endif  // !PROBABILITYINDICATOR_H
