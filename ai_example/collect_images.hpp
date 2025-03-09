#pragma once
#include <cstddef>
#include <cstdint>

#include <vector>

namespace aie {
std::vector<std::vector<std::byte>> collectImages(
  std::uint32_t                 imageCount,
  const std::vector<std::byte>& idxFileData,
  std::uint32_t                 imageByteSize);
} // namespace aie
