#pragma once
#include <cstddef>

#include <vector>

namespace aie {
std::vector<double> asDoubleVector(
  const std::vector<std::byte>& grayscaleImage);

std::vector<double> asDoubleVector(std::byte label);
} // namespace aie
