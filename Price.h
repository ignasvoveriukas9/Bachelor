#ifndef PRICE_H
#define PRICE_H

#include <cstdint>
#include <string>
struct Price {
  std::string ticker;
  int64_t time;
  double price;
};

#endif
