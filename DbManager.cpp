#include "DbManager.h"

#include <cstddef>
#include <cstdio>
#include <sstream>
#include <string>
#include <vector>

#include "Price.h"

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
  for (int i = 0; i < argc; i++) {
    printf("%s = %s\r\n", azColName [ i ], argv [ i ] ? argv [ i ] : "NULL");
  }
  printf("\r\n");
  return 0;
}

static int callbackTableExist(void *data, int argc, char **argv,
                              char **colName) {
  *(int *)data = argc;
  return 0;
}

// returns 0 if dosen't, 1 if dose, -1 on error
int DbManager::doseTableExist(std::string table) {
  // Open database
  // rc = sqlite3_open(dbFile, &db);

  // if (rc) {
  // fprintf(stderr, "Can't open databese: %s\r\n", sqlite3_errmsg(db));
  // return -1;
  //}
  // SQL statement
  std::ostringstream builder;
  builder << "SELECT name from sqlite_master WHERE type='table' AND name='"
          << table << "';";
  std::string sqlString = builder.str();
  sql = sqlString.data();

  int callbackData = 0;

  // Execute SQL statement
  rc = sqlite3_exec(db, sql, callbackTableExist, &callbackData, &zErrMsg);

  if (rc != SQLITE_OK) {
    fprintf(stderr, "SQL error: %s\r\n", zErrMsg);
    sqlite3_free(zErrMsg);
  }

  // Close database
  // sqlite3_close(db);

  if (callbackData) {
    return 1;
  }

  return 0;
}

void DbManager::createTable(std::string table) {
  // Open database
  // rc = sqlite3_open(dbFile, &db);

  // if (rc) {
  // fprintf(stderr, "Can't open databese: %s\r\n", sqlite3_errmsg(db));
  // return;
  //}

  // SQL statement
  std::ostringstream builder;
  builder << "CREATE TABLE " << table
          << "(ticker TEXT NOT NULL,"
             "time BIGINT NOT NULL,"
             "openPrice REAL NOT NULL,"
             "PRIMARY KEY (ticker, time));";
  std::string sqlString = builder.str();
  sql = sqlString.data();

  // Execute SQL statement
  rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

  if (rc != SQLITE_OK) {
    fprintf(stderr, "SQL error: %s\r\n", zErrMsg);
    sqlite3_free(zErrMsg);
  } else {
    fprintf(stdout, "Table created successfully\r\n");
  }

  // Close database
  // sqlite3_close(db);

  return;
}

void DbManager::insertRow(std::string table, Price price) {
  // Open database
  // rc = sqlite3_open(dbFile, &db);

  // if (rc) {
  // fprintf(stderr, "Can't open databese: %s\r\n", sqlite3_errmsg(db));
  // return;
  //}
  //

  int tableExists = doseTableExist(table);
  if (tableExists == 0) {
    createTable(table);
  } else if (tableExists == -1) {
    return;
  }

  // SQL statement
  std::ostringstream builder;
  builder << "INSERT INTO " << table << " (ticker, time, openPrice)"
          << " VALUES ('" << price.ticker << "', " << std::to_string(price.time)
          << ", " << std::to_string(price.price) << ");";

  std::string sqlString = builder.str();
  sql = sqlString.data();

  // Execute SQL statement
  rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

  if (rc != SQLITE_OK) {
    fprintf(stderr, "SQL error: %s\r\n", zErrMsg);
    sqlite3_free(zErrMsg);
  }

  // Close database
  // sqlite3_close(db);

  return;
}

std::vector<Price> DbManager::getPrices(char *dbFile, std::string table,
                                        int64_t timeFrom, int64_t timeTo) {
  // Open database
  rc = sqlite3_open(dbFile, &db);

  if (rc) {
    fprintf(stderr, "Can't open databese: %s\r\n", sqlite3_errmsg(db));
    return std::vector<Price>();
  }

  // SQL statement
  std::ostringstream builder;
  builder << "SELECT * FROM " << table << " WHERE time > "
          << std::to_string(timeFrom) << " AND time < "
          << std::to_string(timeTo) << ";";

  std::string sqlString = builder.str();
  sql = sqlString.data();

  std::vector<Price> list;
  sqlite3_stmt *stmt;

  rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

  if (rc != SQLITE_OK) {
    fprintf(stderr, "SQL error: %s\r\n", sqlite3_errmsg(db));
    return std::vector<Price>();
  }

  while (true) {
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_DONE) {
      break;
    }
    if (rc != SQLITE_ROW) {
      fprintf(stderr, "SQL error: %s\r\n", sqlite3_errmsg(db));
      break;
    }

    Price price;
    const char *ticker = (const char *)sqlite3_column_text(stmt, 0);
    price.ticker = ticker ? ticker : "";
    price.time = sqlite3_column_int64(stmt, 1);
    price.price = sqlite3_column_double(stmt, 2);
    list.push_back(price);
  }

  sqlite3_finalize(stmt);

  return list;
}
