#pragma once
#include <cstddef>
#include <cstdint>

#include <vector>

namespace aie {
std::vector<std::byte> extractImage(
  const std::vector<std::byte>& idxFileData,
  std::uint32_t                 image,
  std::uint32_t                 imageByteCount);
} // namespace
