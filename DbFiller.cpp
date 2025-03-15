#include "DbFiller.h"

#include <cstdint>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

using json = nlohmann::json;

#include "Price.h"

int DbFiller::fillFromCryptoarchive(char *dbFile, std::string table,
                                    std::string csvFile, std::string ticker) {
  int count = 0;
  // File pointer
  std::fstream fin;

  fin.open(csvFile, std::ios::in);

  std::vector<std::string> row;
  std::string line, word, temp;

  // Open database
  int rc = sqlite3_open(dbFile, &dbManager.db);

  if (rc) {
    fprintf(stderr, "Can't open databese: %s\r\n",
            sqlite3_errmsg(dbManager.db));
    return -1;
  }

  while (getline(fin, line)) {
    row.clear();
    // getline(fin, line);

    std::stringstream s(line);

    while (getline(s, word, '|')) {
      row.push_back(word);
    }

    ++count;

    if (count % 1000 == 0) {
      fprintf(stderr, std::to_string(count).c_str());
    }

    dbManager.insertRow(
        table, Price{ticker, std::stoi(row [ 0 ]), std::stod(row [ 1 ])});
  }

  sqlite3_close(dbManager.db);

  return count;
}

int DbFiller::fillFromByBit(char *dbFile, std::string table,
                            std::string jsonFile, std::string ticker) {
  std::ifstream file(jsonFile);
  if (!file.is_open()) {
    std::cerr << "Failed to open file: " << jsonFile << std::endl;
    return -1;
  }

  // Open database
  int rc = sqlite3_open(dbFile, &dbManager.db);

  if (rc) {
    fprintf(stderr, "Can't open databese: %s\r\n",
            sqlite3_errmsg(dbManager.db));
    return -1;
  }

  std::string line;

  int count = 0;

  while (std::getline(file, line)) {
    try {
      json j = json::parse(line);

      int64_t t = j.at("t").get<int64_t>();
      double lastPrice =
          std::stod(j.at("d").at("lastPrice").get<std::string>());

      if (count % 1000 == 0) {
        fprintf(stderr, std::to_string(count).c_str());
      }
      dbManager.insertRow(table, Price{ticker, t, lastPrice});
      ++count;
    } catch (const std::exception &e) {
      std::cerr << "Error parsing line: " << e.what() << std::endl;
    }
  }

  sqlite3_close(dbManager.db);
  file.close();

  return count;
}
