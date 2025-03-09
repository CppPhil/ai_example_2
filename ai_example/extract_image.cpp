#include <cstring>

#include "extract_image.hpp"

namespace aie {
std::vector<std::byte> extractImage(
  const std::vector<std::byte>& idxFileData,
  std::uint32_t                 image,
  std::uint32_t                 imageByteCount)
{
  std::vector<std::byte> extractedImage(imageByteCount);
  std::memcpy(
    extractedImage.data(),
    idxFileData.data() + (image * imageByteCount),
    imageByteCount);
  return extractedImage;
}
} // namespace aie
