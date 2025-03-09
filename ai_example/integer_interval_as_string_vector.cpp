#include "integer_interval_as_string_vector.hpp"

namespace aie {
std::vector<std::string> integerIntervalAsStringVector(
  std::uint32_t begin,
  std::uint32_t end)
{
  std::vector<std::string> result{};
  result.reserve(end - begin);

  for (std::uint32_t i{begin}; i < end; ++i) {
    result.push_back(std::to_string(i));
  }

  return result;
}
} // namespace aie
