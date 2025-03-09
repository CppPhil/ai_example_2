#pragma once
#include <cstddef>

#include <vector>

namespace aie {
class IdxFile;

const std::vector<std::byte>& extractGrayscaleImages(const IdxFile& idxFile);
} // namespace aie
