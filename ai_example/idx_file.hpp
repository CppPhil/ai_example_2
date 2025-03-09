#pragma once
#include <cstddef>
#include <cstdint>

#include <vector>
#include <string_view>
#include <iosfwd>
#include <stdexcept>

namespace aie {
enum class Type : std::uint8_t {
  UnsignedByte = 0x08,
  SignedByte   = 0x09,
  Short        = 0x0B, /* 2 bytes */
  Int          = 0x0C, /* 4 bytes */
  Float        = 0x0D, /* 4 bytes */
  Double       = 0x0E  /* 8 bytes */
};

class IdxFile {
public:
  static IdxFile create(std::string_view filePath);

  explicit IdxFile(std::istream& inputStream);

  Type type() const;

  std::uint8_t countOfDimensions() const;

  const std::vector<std::uint32_t>& dimensions() const;

  const std::vector<std::byte>& data() const;

  std::size_t byteCount() const;

private:
  std::byte                  m_magicNumberFirstByte;
  std::byte                  m_magicNumberSecondByte;
  std::byte                  m_magicNumberTypeCode;
  std::byte                  m_magicNumberDimensionCode;
  std::vector<std::uint32_t> m_dimensions;
  std::vector<std::byte>     m_data;
};
} // namespace aie
