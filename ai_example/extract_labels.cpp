#include "extract_labels.hpp"
#include "dimension_constants.hpp"
#include "idx_file.hpp"
#include "throw_with_source_info.hpp"

namespace aie {
const std::vector<std::byte>& extractLabels(const IdxFile& idxFile)
{
  if (idxFile.type() != Type::UnsignedByte) {
    PL_THROW_WITH_SOURCE_INFO(
      std::domain_error, "Type of IDX file wasn't unsigned byte!");
  }

  if (idxFile.countOfDimensions() != labelFileDimensions) {
    AIE_THROW_WITH_SOURCE_INFO(
      std::domain_error, "count of dimensions wasn't {}!", labelFileDimensions);
  }

  return idxFile.data();
}
} // namespace aie