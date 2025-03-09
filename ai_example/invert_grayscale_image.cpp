#include <cstdint>

#include "invert_grayscale_image.hpp"

namespace aie {
void invertGrayscaleImage(std::vector<std::byte>* grayscaleImage)
{
  for (std::byte& byte : *grayscaleImage) {
    byte = static_cast<std::byte>(
      static_cast<std::uint8_t>(0xFF) - static_cast<std::uint8_t>(byte));
  }
}
} // namespace aie
