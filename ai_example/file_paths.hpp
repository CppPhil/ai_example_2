#pragma once
#include <string_view>

namespace aie {
inline constexpr std::string_view trainingImagesFilePath{
  "../../../../data/train-images.idx3-ubyte"};
inline constexpr std::string_view trainingLabelsFilePath{
  "../../../../data/train-labels.idx1-ubyte"};
inline constexpr std::string_view testingImagesFilePath{
  "../../../../data/t10k-images.idx3-ubyte"};
inline constexpr std::string_view testingLabelsFilePath{
  "../../../../data/t10k-labels.idx1-ubyte"};
} // namespace aie
