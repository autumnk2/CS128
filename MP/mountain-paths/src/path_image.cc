#include "path_image.hpp"

// clang-format off
PathImage::PathImage(const GrayscaleImage& image, const ElevationDataset& dataset)
: width_(image.Width()), height_(image.Height()), path_image_(image.GetImage()) {
  unsigned int min_change = std::numeric_limits<unsigned int>::max();
  for (size_t row = 0; row < height_; ++row) {
    Path path(width_, row);
    GeneratePath(dataset, path);
    paths_.push_back(path);
    if (path.EleChange() < min_change) {
      min_change = path.EleChange();
      best_path_idx_ = row;
    }
    for (size_t i = 0; i < paths_.size(); ++i) {
      if (i == best_path_idx_) continue;
      for (size_t col = 0; col < width_; ++col)
        path_image_.at(paths_.at(i).GetPath().at(col)).at(col) = kRed;
    }
    for (size_t col = 0; col < width_; ++col)
      path_image_.at(paths_.at(best_path_idx_).GetPath().at(col)).at(col) = kGreen;
  }
}

void PathImage::ToPpm(const std::string& name) const {
  std::ofstream ofs{name};
  ofs << "P3\n" << width_ << ' ' << height_ << '\n' << "255\n";
  for (size_t row = 0; row < height_; ++row) {
    for (size_t col = 0; col < width_; ++col) {
      if (col == 0) ofs << path_image_.at(row).at(col).Red();
      else ofs << " " << path_image_.at(row).at(col).Red();

      ofs << " " << path_image_.at(row).at(col).Green() 
          << " " << path_image_.at(row).at(col).Blue();
    }
    ofs << '\n';
  }
}