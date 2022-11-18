#include <iostream>

#include "db.hpp"
#include "db_table.hpp"

int main() {
  DbTable db;
  db.AddColumn({"name", DataType::kString});
  db.AddColumn({"UIN", DataType::kInt});
  db.AddRow({"Nolan", "123"});
  db.AddRow({"Icey", "23"});
  db.AddRow({"Mark", "33"});
  db.AddRow({"Fan", "26"});

  db.AddColumn({"email", DataType::kInt});
  db.AddColumn({"address", DataType::kInt});
  db.AddColumn({"parent", DataType::kDouble});

  db.AddRow({"a", "1", "2", "3", "4.4 "});

  DbTable db2(db);

  // db.DeleteColumnByIdx(0);

  std::cout << db2 << std::endl;

  return 0;
}