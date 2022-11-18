#include "db_table.hpp"

const unsigned int kRowGrowthRate = 2;

void DbTable::Growth() {
  for (auto& [id, row] : rows_) {
    void** new_row = new void*[static_cast<unsigned long>(row_col_capacity_) *
                               kRowGrowthRate];
    for (unsigned int i = 0; i < row_col_capacity_; ++i) new_row[i] = row[i];
    delete[] row;
    row = new_row;
  }
  row_col_capacity_ *= kRowGrowthRate;
}

void DbTable::AddColumn(const std::pair<std::string, DataType>& col_desc) {
  if (col_descs_.size() == row_col_capacity_) Growth();
  col_descs_.push_back(col_desc);
  for (auto& [id, row] : rows_) {
    if (col_desc.second == DataType::kString) {
      row[col_descs_.size() - 1] = static_cast<void*>(new std::string{""});
    } else if (col_desc.second == DataType::kInt) {
      row[col_descs_.size() - 1] = static_cast<void*>(new int{0});
    } else if (col_desc.second == DataType::kDouble) {
      row[col_descs_.size() - 1] = static_cast<void*>(new double{0.0});
    }
  }
}

void DbTable::DeleteColumnByIdx(unsigned int col_idx) {
  if (col_idx < 0 || col_idx >= col_descs_.size())
    throw std::out_of_range("col idx out of range");
  if (col_descs_.size() == 1 && !rows_.empty())
    throw std::runtime_error(
        "any table with at least one row must have at least one column");
  for (auto& [id, row] : rows_) {
    if (col_descs_.at(col_idx).second == DataType::kString) {
      delete static_cast<std::string*>(row[col_idx]);
    } else if (col_descs_.at(col_idx).second == DataType::kInt) {
      delete static_cast<int*>(row[col_idx]);
    } else if (col_descs_.at(col_idx).second == DataType::kDouble) {
      delete static_cast<double*>(row[col_idx]);
    }
    for (unsigned int i = col_idx + 1; i < col_descs_.size(); ++i) {
      row[i - 1] = row[i];
    }
  }
  col_descs_.erase(col_descs_.begin() + col_idx);
}

void DbTable::AddRow(const std::initializer_list<std::string>& col_data) {
  if (col_data.size() != col_descs_.size())
    throw std::invalid_argument(
        "size of col_data doesn't match that of col_descs_");
  rows_[next_unique_id_] = new void*[row_col_capacity_];
  int i = 0;
  for (const auto& ele : col_data) {
    if (col_descs_.at(i).second == DataType::kString) {
      rows_[next_unique_id_][i] = static_cast<void*>(new std::string{ele});
    } else if (col_descs_.at(i).second == DataType::kInt) {
      rows_[next_unique_id_][i] = static_cast<void*>(new int{std::stoi(ele)});
    } else if (col_descs_.at(i).second == DataType::kDouble) {
      rows_[next_unique_id_][i] =
          static_cast<void*>(new double{std::stod(ele)});
    }
    ++i;
  }
  ++next_unique_id_;
}

void DbTable::DeleteRowById(unsigned int id) {
  if (!rows_.contains(id)) throw std::invalid_argument("the id does not exit");
  for (unsigned int i = 0; i < col_descs_.size(); ++i) {
    if (col_descs_.at(i).second == DataType::kString) {
      delete static_cast<std::string*>(rows_[id][i]);
    } else if (col_descs_.at(i).second == DataType::kInt) {
      delete static_cast<int*>(rows_[id][i]);
    } else if (col_descs_.at(i).second == DataType::kDouble) {
      delete static_cast<double*>(rows_[id][i]);
    }
  }
  delete[] rows_[id];
  rows_.erase(id);
}

DbTable::DbTable(const DbTable& rhs):
    next_unique_id_(rhs.next_unique_id_),
    row_col_capacity_(rhs.row_col_capacity_),
    col_descs_(rhs.col_descs_) {
  for (const auto& [id, row] : rhs.rows_) {
    rows_[id] = new void*[row_col_capacity_];
    for (unsigned int i = 0; i < col_descs_.size(); ++i) {
      if (rhs.col_descs_.at(i).second == DataType::kString) {
        rows_[id][i] = static_cast<void*>(
            new std::string{*static_cast<std::string*>(row[i])});
      } else if (rhs.col_descs_.at(i).second == DataType::kInt) {
        rows_[id][i] = static_cast<void*>(new int{*static_cast<int*>(row[i])});
      } else if (rhs.col_descs_.at(i).second == DataType::kDouble) {
        rows_[id][i] =
            static_cast<void*>(new double{*static_cast<double*>(row[i])});
      }
    }
  }
}

void DbTable::Delete() {
  for (unsigned int i = 0; i < next_unique_id_; ++i) {
    if (rows_.contains(i)) {
      DeleteRowById(i);
    }
  }
  rows_.clear();
}

DbTable& DbTable::operator=(const DbTable& rhs) {
  if (this == &rhs) return *this;
  Delete();
  next_unique_id_ = rhs.next_unique_id_;
  row_col_capacity_ = rhs.row_col_capacity_;
  col_descs_ = rhs.col_descs_;
  for (const auto& [id, row] : rhs.rows_) {
    rows_[id] = new void*[row_col_capacity_];
    for (unsigned int i = 0; i < col_descs_.size(); ++i) {
      if (rhs.col_descs_.at(i).second == DataType::kString) {
        rows_[id][i] = static_cast<void*>(
            new std::string{*static_cast<std::string*>(row[i])});
      } else if (rhs.col_descs_.at(i).second == DataType::kInt) {
        rows_[id][i] = static_cast<void*>(new int{*static_cast<int*>(row[i])});
      } else if (rhs.col_descs_.at(i).second == DataType::kDouble) {
        rows_[id][i] =
            static_cast<void*>(new double{*static_cast<double*>(row[i])});
      }
    }
  }
  return *this;
}

DbTable::~DbTable() { Delete(); }

std::ostream& operator<<(std::ostream& os, const DbTable& table) {
  for (unsigned int i = 0; i < table.col_descs_.size(); ++i) {
    os << table.col_descs_.at(i).first << "("
       << (table.col_descs_.at(i).second == DataType::kString   ? "std::string"
           : table.col_descs_.at(i).second == DataType::kInt    ? "int"
           : table.col_descs_.at(i).second == DataType::kDouble ? "double"
                                                                : "")
       << ")";
    if (i != table.col_descs_.size() - 1) os << ", ";
  }
  os << "\n";
  unsigned int idx = 0;
  for (const auto& [id, row] : table.rows_) {
    for (unsigned int i = 0; i < table.col_descs_.size(); ++i) {
      if (table.col_descs_.at(i).second == DataType::kString) {
        os << *static_cast<std::string*>(row[i]);
      } else if (table.col_descs_.at(i).second == DataType::kInt) {
        os << *static_cast<int*>(row[i]);
      } else if (table.col_descs_.at(i).second == DataType::kDouble) {
        os << *static_cast<double*>(row[i]);
      }
      if (i != table.col_descs_.size() - 1) os << ", ";
    }
    if (idx != table.rows_.size() - 1) os << "\n";
  }
  return os;
}
