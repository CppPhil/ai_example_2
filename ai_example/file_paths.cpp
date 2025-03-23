#include <stdexcept>

#include <pl/except.hpp>

#include "file_paths.hpp"

namespace aie {
namespace {
std::filesystem::path findFile(std::string_view fileName)
{
  std::filesystem::path currentPath{std::filesystem::current_path()};

  while (currentPath.has_parent_path()) {
    const std::filesystem::path filePath{currentPath / fileName};

    if (
      std::filesystem::exists(filePath)
      && std::filesystem::is_regular_file(filePath)) {
      return filePath;
    }

    currentPath = currentPath.parent_path();
  }

  PL_THROW_WITH_SOURCE_INFO(
    std::domain_error, "File not found: " + std::string{fileName});
}
} // anonymous namespace

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
