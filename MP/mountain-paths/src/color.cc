#include "color.hpp"

// clang-format off
Color::Color(int r, int g, int b): red_(r), green_(g), blue_(b) {
  if (r < 0 || r > kColorMax || g < 0 || g > kColorMax || b < 0 || b > kColorMax)
    throw std::runtime_error("invalid RGB value");
}

bool operator==(const Color& rhs, const Color& lhs) {
  return (rhs.Red() == lhs.Red() && rhs.Green() == lhs.Green() && rhs.Blue() == lhs.Blue());
}