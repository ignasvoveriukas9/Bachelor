#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <sqlite3.h>

#include <cstdint>
#include <string>
#include <vector>

#include "Price.h"

class DbManager {
 private:
  char *zErrMsg = 0;
  int rc;
  char *sql;

 public:
  void createTable(std::string table);
  int doseTableExist(std::string table);

 public:
  sqlite3 *db;
  void insertRow(std::string table, Price price);
  std::vector<Price> getPrices(char *dbFile, std::string table,
                               int64_t timeFrom, int64_t timeTo);
};

#endif
