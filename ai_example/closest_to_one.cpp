#include "closest_to_one.hpp"

namespace aie {
std::size_t closestToOne(const std::vector<double>& vector)
{
  std::size_t label{0};

  for (std::size_t i{0}; i < vector.size(); ++i) {
    if ((1.0 - vector[i]) < (1.0 - vector[label])) {
      label = i;
    }
  }

  return label;
}
} // namespace aie
