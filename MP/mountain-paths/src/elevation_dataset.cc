#include "elevation_dataset.hpp"

// clang-format off
ElevationDataset::ElevationDataset(const std::string& filename, size_t width, size_t height)
: width_(width), height_(height), 
  data_(
    std::vector<std::vector<int>>(height_, std::vector<int>(width_, 0))
  ), max_ele_(std::numeric_limits<int>::min()), min_ele_(std::numeric_limits<int>::max()) {
  std::ifstream ifs{filename};
  size_t count = 0;
  if (!ifs.is_open()) throw std::runtime_error("the file is not open");
  int val = 0;
  while (ifs.good()) {
    ifs >> val;
    if (ifs.fail()) {
      ifs.clear();
      ifs.ignore(1, '\n');
    } else {
      max_ele_ = std::max(max_ele_, val);
      min_ele_ = std::min(min_ele_, val);
      if (count == width_ * height_) throw std::runtime_error("too many data");
      data_.at(count / width_).at(count % width_) = val;
      ++count;
    }
  }
  if (count < width_ * height_) throw std::runtime_error("too few data");
}
