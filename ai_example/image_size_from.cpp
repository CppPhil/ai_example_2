#include "image_size_from.hpp"
#include "dimension_constants.hpp"
#include "idx_file.hpp"
#include "throw_with_source_info.hpp"

namespace aie {
std::uint32_t imageSizeFrom(const IdxFile& idxFile)
{
  if (idxFile.countOfDimensions() != imageFileDimensions) {
    AIE_THROW_WITH_SOURCE_INFO(
      std::domain_error, "Count of dimensions wasn't {}!", imageFileDimensions);
  }

  const std::vector<std::uint32_t>& dimensions{idxFile.dimensions()};

  return dimensions[1] * dimensions[2];
}
} // namespace aie
