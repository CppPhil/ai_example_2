#include "collect_images.hpp"
#include "extract_image.hpp"
#include "invert_grayscale_image.hpp"

namespace aie {
std::vector<std::vector<std::byte>> collectImages(
  std::uint32_t                 imageCount,
  const std::vector<std::byte>& idxFileData,
  std::uint32_t                 imageByteSize)
{
  std::vector<std::vector<std::byte>> images{};
  images.reserve(imageCount);

  for (std::uint32_t i{0}; i < imageCount; ++i) {
    std::vector<std::byte> currentImageBytes{
      aie::extractImage(idxFileData, i, imageByteSize)};
    aie::invertGrayscaleImage(&currentImageBytes);
    images.push_back(std::move(currentImageBytes));
  }

  return images;
}
} // namespace aie
