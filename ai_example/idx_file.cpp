#include <bit>
#include <fstream>
#include <functional>

#include <pl/algo/ranged_algorithms.hpp>
#include <pl/assert.hpp>
#include <pl/bswap.hpp>

#include "idx_file.hpp"
#include "throw_with_source_info.hpp"

namespace aie {
namespace {
bool binaryRead(std::istream& source, void* destination, std::size_t byteCount)
{
  return static_cast<bool>(
    source.read(static_cast<char*>(destination), byteCount));
}

template<typename Type>
bool readInto(std::istream& inputStream, Type* object)
{
  static_assert(std::is_trivial_v<Type>, "Type was not a trivial type.");
  return binaryRead(inputStream, object, sizeof(*object));
}

bool readMagicNumber(
  std::istream& inputStream,
  std::byte*    magicNumberFirstByte,
  std::byte*    magicNumberSecondByte,
  std::byte*    magicNumberTypeCode,
  std::byte*    magicNumberDimensionCode)
{
  bool success{false};

#define AIE_TRY_READ(Destination)                 \
  do {                                            \
    success = readInto(inputStream, Destination); \
    if (!success) {                               \
      return false;                               \
    }                                             \
  } while (false)

  AIE_TRY_READ(magicNumberFirstByte);
  AIE_TRY_READ(magicNumberSecondByte);
  AIE_TRY_READ(magicNumberTypeCode);
  AIE_TRY_READ(magicNumberDimensionCode);
  return true;
}

bool readDimensions(
  std::istream&               inputStream,
  std::vector<std::uint32_t>* dimensions,
  std::uint8_t                countOfDimensions)
{
  dimensions->resize(static_cast<std::size_t>(countOfDimensions));

  for (std::uint8_t i{0}; i < countOfDimensions; ++i) {
    std::uint32_t& currentDimension{(*dimensions)[i]};

    if (!readInto(inputStream, &currentDimension)) {
      return false;
    }

    if constexpr (std::endian::native == std::endian::little) {
      currentDimension = pl::bswap(currentDimension);
    }
  }

  return true;
}
} // anonymous namespace

IdxFile IdxFile::create(std::string_view filePath)
{
  std::ifstream inputFileStream{filePath.data(), std::ios_base::binary};

  if (!inputFileStream) {
    AIE_THROW_WITH_SOURCE_INFO(
      std::domain_error, "Couldn't open \"{}\"!", filePath);
  }

  return IdxFile{inputFileStream};
}

IdxFile::IdxFile(std::istream& inputStream)
  : m_magicNumberFirstByte{}
  , m_magicNumberSecondByte{}
  , m_magicNumberTypeCode{}
  , m_magicNumberDimensionCode{}
  , m_dimensions{}
  , m_data{}
{
  if (!readMagicNumber(
        inputStream,
        &m_magicNumberFirstByte,
        &m_magicNumberSecondByte,
        &m_magicNumberTypeCode,
        &m_magicNumberDimensionCode)) {
    PL_THROW_WITH_SOURCE_INFO(
      std::domain_error, "Could not read magic number!");
  }

  if (
    (m_magicNumberFirstByte != std::byte{0})
    || (m_magicNumberSecondByte != std::byte{0})) {
    PL_THROW_WITH_SOURCE_INFO(
      std::domain_error,
      "One of the first two bytes of the magic number wasn't 0!");
  }

  if (!readDimensions(inputStream, &m_dimensions, countOfDimensions())) {
    PL_THROW_WITH_SOURCE_INFO(
      std::domain_error, "Couldn't read the dimensions!");
  }

  const std::size_t countOfBytes{byteCount()};
  m_data.resize(countOfBytes);

  if (!binaryRead(inputStream, m_data.data(), m_data.size())) {
    PL_THROW_WITH_SOURCE_INFO(
      std::domain_error, "Couldn't read the binary data!");
  }
}

Type IdxFile::type() const
{
  return static_cast<Type>(m_magicNumberTypeCode);
}

std::uint8_t IdxFile::countOfDimensions() const
{
  return static_cast<std::uint8_t>(m_magicNumberDimensionCode);
}

const std::vector<std::uint32_t>& IdxFile::dimensions() const
{
  PL_CHECK_PRE(m_dimensions.size() == countOfDimensions());
  return m_dimensions;
}

const std::vector<std::byte>& IdxFile::data() const
{
  return m_data;
}

std::size_t IdxFile::byteCount() const
{
  const std::vector<std::uint32_t>& theDimensions{dimensions()};
  return pl::algo::accumulate(
    theDimensions,
    static_cast<std::uint32_t>(1U),
    std::multiplies<std::uint32_t>{});
}
} // namespace aie
