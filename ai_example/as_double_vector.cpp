#include <pl/algo/ranged_algorithms.hpp>

#include "as_double_vector.hpp"
#include "neural_network_constants.hpp"

namespace aie {
namespace {
double mnistPixelAsDouble(std::byte mnistPixelValue)
{
  return static_cast<double>(mnistPixelValue) / 255.0;
}
} // anonymous namespace

std::vector<double> asDoubleVector(const std::vector<std::byte>& grayscaleImage)
{
  std::vector<double> resultVector(grayscaleImage.size());
  pl::algo::transform(
    grayscaleImage, resultVector.begin(), &mnistPixelAsDouble);
  return resultVector;
}

std::vector<double> asDoubleVector(std::byte label)
{
  std::vector<double> result(aie::outputLayerNeuronCount, 0.0);
  result.at(static_cast<std::size_t>(label)) = 1.0;
  return result;
}
} // namespace aie
