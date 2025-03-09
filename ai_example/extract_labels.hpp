#pragma once
#include <cstddef>

#include <vector>

namespace aie {
class IdxFile;

const std::vector<std::byte>& extractLabels(const IdxFile& idxFile);
} // namespace aie
