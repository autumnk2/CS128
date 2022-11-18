#include "grayscale_image.hpp"

// clang-format off
GrayscaleImage::GrayscaleImage(const ElevationDataset& dataset)
: width_(dataset.Width()), height_(dataset.Height()), 
  image_(
    std::vector<std::vector<Color>>(dataset.Height(), std::vector<Color>(dataset.Width(), Color(0, 0, 0)))
  ) {
  if (dataset.MaxEle() == dataset.MinEle()) return;
  for (size_t row = 0; row < height_; ++row) {
    for (size_t col = 0; col < width_; ++col) {
      int shade_of_gray = static_cast<int>(
        std::round(
          static_cast<double>(dataset.DatumAt(row, col) - dataset.MinEle()) /
          static_cast<double>(dataset.MaxEle() - dataset.MinEle()) *
          static_cast<double>(kMaxColorValue)
        )
      );
      image_.at(row).at(col) = Color(shade_of_gray, shade_of_gray, shade_of_gray);
    }
  }
}

GrayscaleImage::GrayscaleImage(const std::string& filename, size_t width, size_t height)
: width_(width), height_(height), 
  image_(
    std::vector<std::vector<Color>>(height, std::vector<Color>(width, Color(0, 0, 0)))
  ) {
  ElevationDataset dataset(filename, width_, height_);
  if (dataset.MaxEle() == dataset.MinEle()) return;
  for (size_t row = 0; row < height_; ++row) {
    for (size_t col = 0; col < width_; ++col) {
      int shade_of_gray = static_cast<int>(
        std::round(
          static_cast<double>(dataset.DatumAt(row, col) - dataset.MinEle()) /
          static_cast<double>(dataset.MaxEle() - dataset.MinEle()) *
          static_cast<double>(kMaxColorValue)
        )
      );
      image_.at(row).at(col) = Color(shade_of_gray, shade_of_gray, shade_of_gray);
    }
  }
}

void GrayscaleImage::ToPpm(const std::string& name) const {
  std::ofstream ofs{name};
  ofs << "P3\n" << width_ << ' ' << height_ << '\n' << "255\n";
  for (size_t row = 0; row < height_; ++row) {
    for (size_t col = 0; col < width_; ++col) {
      if (col == 0) ofs << image_.at(row).at(col).Red();
      else ofs << " " << image_.at(row).at(col).Red();
      ofs << " " << image_.at(row).at(col).Green() 
          << " " << image_.at(row).at(col).Blue();
    }
    ofs << '\n';
  }
}