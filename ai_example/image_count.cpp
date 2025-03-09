#include "image_count.hpp"
#include "dimension_constants.hpp"
#include "idx_file.hpp"
#include "throw_with_source_info.hpp"

namespace aie {
std::uint32_t imageCount(const IdxFile& idxFile)
{
  if (idxFile.countOfDimensions() != imageFileDimensions) {
    AIE_THROW_WITH_SOURCE_INFO(
      std::domain_error, "Count of dimensions wasn't {}!", imageFileDimensions);
  }

  return idxFile.dimensions().front();
}
} // namespace aie
