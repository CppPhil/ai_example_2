#include <stdexcept>

#include <pl/except.hpp>

#include "file_paths.hpp"

namespace aie {
std::filesystem::path findFile(std::string_view fileName)
{
  constexpr int         maxRecursionDepth{5};
  std::filesystem::path currentPath{std::filesystem::current_path()};
  int                   depthCounter{0};

  while (currentPath.has_parent_path()) {
    if (depthCounter >= maxRecursionDepth) {
      break;
    }

    const std::filesystem::path filePath{currentPath / fileName};

    if (
      std::filesystem::exists(filePath)
      && std::filesystem::is_regular_file(filePath)) {
      return filePath;
    }

    currentPath = currentPath.parent_path();
    ++depthCounter;
  }

  PL_THROW_WITH_SOURCE_INFO(
    std::domain_error, "File not found: " + std::string{fileName});
}

std::filesystem::path trainingImagesFilePath()
{
  return findFile(trainingImagesFileName);
}

std::filesystem::path trainingLabelsFilePath()
{
  return findFile(trainingLabelsFileName);
}

std::filesystem::path testingImagesFilePath()
{
  return findFile(testingImagesFileName);
}

std::filesystem::path testingLabelsFilePath()
{
  return findFile(testingLabelsFileName);
}
} // namespace aie
