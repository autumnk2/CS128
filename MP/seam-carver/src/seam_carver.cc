#include "seam_carver.hpp"

// implement the rest of SeamCarver's functions here

// given functions below, DO NOT MODIFY

SeamCarver::SeamCarver(const ImagePPM& image): image_(image) {
  height_ = image.GetHeight();
  width_ = image.GetWidth();
}

void SeamCarver::SetImage(const ImagePPM& image) {
  image_ = image;
  width_ = image.GetWidth();
  height_ = image.GetHeight();
}

const ImagePPM& SeamCarver::GetImage() const { return image_; }

int SeamCarver::GetHeight() const { return height_; }

int SeamCarver::GetWidth() const { return width_; }

int SeamCarver::GetEnergy(int row, int col) const {
  Pixel top = row == 0 ? image_.GetPixel(height_ - 1, col)
                       : image_.GetPixel(row - 1, col),
        bottom = row == height_ - 1 ? image_.GetPixel(0, col)
                                    : image_.GetPixel(row + 1, col),
        left = col == 0 ? image_.GetPixel(row, width_ - 1)
                        : image_.GetPixel(row, col - 1),
        right = col == width_ - 1 ? image_.GetPixel(row, 0)
                                  : image_.GetPixel(row, col + 1);

  return (top.GetRed() - bottom.GetRed()) * (top.GetRed() - bottom.GetRed()) +
         (top.GetGreen() - bottom.GetGreen()) *
             (top.GetGreen() - bottom.GetGreen()) +
         (top.GetBlue() - bottom.GetBlue()) *
             (top.GetBlue() - bottom.GetBlue()) +
         (left.GetRed() - right.GetRed()) * (left.GetRed() - right.GetRed()) +
         (left.GetGreen() - right.GetGreen()) *
             (left.GetGreen() - right.GetGreen()) +
         (left.GetBlue() - right.GetBlue()) *
             (left.GetBlue() - right.GetBlue());
}

int* SeamCarver::GetVerticalSeam() const {
  int** values = new int*[height_];
  for (int row = 0; row < height_; ++row) values[row] = new int[width_];
  for (int col = 0; col < width_; ++col)
    values[height_ - 1][col] = GetEnergy(height_ - 1, col);
  for (int row = height_ - 2; row >= 0; --row)
    for (int col = 0; col < width_; ++col)
      values[row][col] =
          (col == 0 ? std::min(values[row + 1][col], values[row + 1][col + 1])
           : col == width_ - 1
               ? std::min(values[row + 1][col - 1], values[row + 1][col])
               : Min(values[row + 1][col - 1],
                     values[row + 1][col],
                     values[row + 1][col + 1])) +
          GetEnergy(row, col);
  int* path = new int[height_];
  int col = PathStartIdx(values[0], width_);
  path[0] = col;
  int min_val = 0;
  for (int row = 1; row < height_; ++row) {
    min_val =
        col == 0 ? std::min(values[row][col], values[row][col + 1])
        : col == width_ - 1
            ? std::min(values[row][col - 1], values[row][col])
            : Min(values[row][col - 1], values[row][col], values[row][col + 1]);
    col = values[row][col] == min_val       ? col
          : col == 0                        ? col + 1
          : col == width_ - 1               ? col - 1
          : values[row][col - 1] == min_val ? col - 1
                                            : col + 1;
    path[row] = col;
  }
  for (int row = 0; row < height_; ++row) delete[] values[row];
  delete[] values;
  return path;
}

int* SeamCarver::GetHorizontalSeam() const {
  int** values = new int*[height_];
  for (int row = 0; row < height_; ++row) values[row] = new int[width_];
  for (int row = 0; row < height_; ++row)
    values[row][width_ - 1] = GetEnergy(row, width_ - 1);
  for (int col = width_ - 2; col >= 0; --col)
    for (int row = 0; row < height_; ++row)
      values[row][col] =
          (row == 0 ? std::min(values[row][col + 1], values[row + 1][col + 1])
           : row == height_ - 1
               ? std::min(values[row - 1][col + 1], values[row][col + 1])
               : Min(values[row - 1][col + 1],
                     values[row][col + 1],
                     values[row + 1][col + 1])) +
          GetEnergy(row, col);
  int* path = new int[width_];
  int* first_col = new int[height_];
  for (int row = 0; row < height_; ++row) first_col[row] = values[row][0];
  int row = PathStartIdx(first_col, height_);
  path[0] = row;
  int min_val = 0;
  for (int col = 1; col < width_; ++col) {
    min_val =
        row == 0 ? std::min(values[row][col], values[row + 1][col])
        : row == height_ - 1
            ? std::min(values[row - 1][col], values[row][col])
            : Min(values[row - 1][col], values[row][col], values[row + 1][col]);
    row = values[row][col] == min_val       ? row
          : row == 0                        ? row + 1
          : row == height_ - 1              ? row - 1
          : values[row - 1][col] == min_val ? row - 1
                                            : row + 1;
    path[col] = row;
  }
  for (int row = 0; row < height_; ++row) delete[] values[row];
  delete[] values;
  delete[] first_col;
  return path;
}

void SeamCarver::RemoveVerticalSeam() {
  int* path = GetVerticalSeam();
  --width_;
  auto** new_image = new Pixel*[height_];
  for (int row = 0; row < height_; ++row) new_image[row] = new Pixel[width_];
  int max_color_value = image_.GetMaxColorValue(), count = 0, r = 0, g = 0,
      b = 0;
  Pixel p{};
  for (int row = 0; row < height_; ++row) {
    for (int col = 0; col < width_; ++col) {
      if (path[row] == col) ++count;
      p = image_.GetPixel(row, col + count);
      r = p.GetRed(), g = p.GetGreen(), b = p.GetBlue();
      max_color_value = std::max(std::max(r, g), std::max(b, max_color_value));
      new_image[row][col] = Pixel(r, g, b);
    }
    count = 0;
  }
  image_.SetImage(height_, width_, max_color_value, new_image);
  delete[] path;
}

void SeamCarver::RemoveHorizontalSeam() {
  int* path = GetHorizontalSeam();
  --height_;
  auto** new_image = new Pixel*[height_];
  for (int row = 0; row < height_; ++row) new_image[row] = new Pixel[width_];
  int max_color_value = image_.GetMaxColorValue(), count = 0, r = 0, g = 0,
      b = 0;
  Pixel p{};
  for (int col = 0; col < width_; ++col) {
    for (int row = 0; row < height_; ++row) {
      if (path[col] == row) ++count;
      p = image_.GetPixel(row + count, col);
      r = p.GetRed(), g = p.GetGreen(), b = p.GetBlue();
      max_color_value = std::max(std::max(r, g), std::max(b, max_color_value));
      new_image[row][col] = Pixel(r, g, b);
    }
    count = 0;
  }
  image_.SetImage(height_, width_, max_color_value, new_image);
  delete[] path;
}