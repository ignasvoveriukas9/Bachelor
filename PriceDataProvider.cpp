#include "PriceDataProvider.h"

#include <pstl/glue_algorithm_defs.h>

#include <cstdint>
#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "Price.h"

std::vector<Price> PriceDataProvider::getPrices(char* dataFile,
                                                std::string ticker,
                                                int64_t timeFrom,
                                                int64_t timeTo) {
  std::vector<Price> result;

  std::ifstream file(dataFile);

  if (!file.is_open()) {
    std::cerr << "Error opening fiel: " << dataFile << std::endl;
    return result;
  }

  std::string line;
  while (std::getline(file, line)) {
    // remove any carriage return char
    // line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());

    std::istringstream iss(line);
    std::string token;
    std::vector<std::string> tokens;

    // Split line by pipe
    while (std::getline(iss, token, '|')) {
      tokens.push_back(token);
    }

    if (tokens.size() < 5) {
      continue;  // Skip malformed lines
    }

    try {
      int64_t timestamp = std::stoll(tokens [ 0 ]);

      if (timestamp >= timeFrom && timestamp <= timeTo) {
        Price data;
        data.ticker = ticker;
        data.time = timestamp;
        data.price = std::stod(tokens [ 1 ]);
        data.high = std::stod(tokens [ 2 ]);
        data.low = std::stod(tokens [ 3 ]);
        data.close = std::stod(tokens [ 4 ]);

        result.push_back(data);
      }
    } catch (const std::exception& e) {
      std::cerr << "Error parsing line: " << line << " - " << e.what()
                << std::endl;
      continue;
    }
  }
  return result;
}
