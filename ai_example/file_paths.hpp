#pragma once
#include <filesystem>
#include <string_view>

namespace aie {
inline constexpr std::string_view trainingImagesFileName{
  "train-images.idx3-ubyte"};
inline constexpr std::string_view trainingLabelsFileName{
  "train-labels.idx1-ubyte"};
inline constexpr std::string_view testingImagesFileName{
  "t10k-images.idx3-ubyte"};
inline constexpr std::string_view testingLabelsFileName{
  "t10k-labels.idx1-ubyte"};

std::filesystem::path trainingImagesFilePath();

std::filesystem::path trainingLabelsFilePath();

std::filesystem::path testingImagesFilePath();

std::filesystem::path testingLabelsFilePath();
} // namespace aie
