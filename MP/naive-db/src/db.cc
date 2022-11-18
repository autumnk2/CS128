#include "db.hpp"

void Database::CreateTable(const std::string& table_name) {
  tables_[table_name] = new DbTable();
}

void Database::DropTable(const std::string& table_name) {
  if (!tables_.contains(table_name))
    throw std::invalid_argument("table_name does not exist");
  tables_[table_name]->Delete();
  delete tables_[table_name];
  tables_.erase(table_name);
}

DbTable& Database::GetTable(const std::string& table_name) {
  if (!tables_.contains(table_name))
    throw std::invalid_argument("table_name does not exist");
  return *tables_[table_name];
}

Database::Database(const Database& rhs) {
  for (const auto& [name, table] : rhs.tables_) {
    tables_[name] = new DbTable(*table);
  }
}

Database& Database::operator=(const Database& rhs) {
  if (this == &rhs) return *this;
  for (auto& [name, table] : tables_) {
    table->Delete();
    delete table;
  }
  tables_.clear();
  for (const auto& [name, table] : rhs.tables_) {
    tables_[name] = new DbTable(*table);
  }
  return *this;
}

Database::~Database() {
  for (auto& [name, table] : tables_) {
    table->Delete();
    delete table;
  }
  tables_.clear();
}

std::ostream& operator<<(std::ostream& os, const Database& db) {
  for (const auto& [name, table] : db.tables_) {
    os << name << "\n";
    os << table << "\n";
  }
  return os;
}