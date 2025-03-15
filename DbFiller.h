#ifndef DBFILLER_H
#define DBFILLER_H

#include <string>

#include "DbManager.h"

class DbFiller {
 private:
  DbManager dbManager;

 public:
  // puts records from Cryptoarchive csv into the database
  // csv | seperated: Open timestamp|Open|...
  int fillFromCryptoarchive(char *dbFile, std::string table,
                            std::string csvFile, std::string ticker);

  int fillFromByBit(char *dbFile, std::string table, std::string jsonFile,
                    std::string ticker);
};

#endif
