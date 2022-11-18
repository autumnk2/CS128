#include "path.hpp"

// clang-format off
Path::Path(size_t length, size_t starting_row)
: length_(length), starting_row_(starting_row), path_(std::vector<size_t>(length)) {
  path_.at(0) = starting_row;
}

void Path::IncEleChange(unsigned int value) {
  if (value < 0) throw std::runtime_error("value must be positive");
  ele_change_ += value;
}

int FindMin(const unsigned int arr[]) {
  unsigned int min_val = std::min(std::min(arr[0], arr[1]), arr[2]);
  if (arr[1] == min_val) return 1;
  if (arr[2] == min_val) return 2;
  return 0;
}

std::pair<size_t, int> NextLoc(const ElevationDataset& dataset, size_t row, size_t col) {
  unsigned int ele1 = row != 0 ? std::abs(dataset.DatumAt(row - 1, col + 1) - dataset.DatumAt(row, col))
                               : std::numeric_limits<int>::max();
  unsigned int ele2 = std::abs(dataset.DatumAt(row, col + 1) - dataset.DatumAt(row, col));
  unsigned int ele3 = row != dataset.Height() - 1
                          ? std::abs(dataset.DatumAt(row + 1, col + 1) - dataset.DatumAt(row, col))
                          : std::numeric_limits<int>::max();
  unsigned int arr[]{ele1, ele2, ele3};
  int idx = FindMin(arr);
  if (idx == 0) return {row - 1, ele1};
  if (idx == 1) return {row, ele2};
  if (idx == 2) return {row + 1, ele3};
  return {0, 0};
}

void GeneratePath(const ElevationDataset& dataset, Path& path) {
  for (size_t col = 0; col < dataset.Width() - 1; ++col) {
    auto loc = NextLoc(dataset, path.GetPath().at(col), col);
    path.IncEleChange(loc.second);
    path.SetLoc(col + 1, loc.first);
  }
}