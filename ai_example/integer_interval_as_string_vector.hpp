#pragma once
#include <cstdint>

#include <string>
#include <vector>

namespace aie {
std::vector<std::string> integerIntervalAsStringVector(
  std::uint32_t begin,
  std::uint32_t end);
} // namespace aie
