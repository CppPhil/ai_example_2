#include <string>

#include <pl/except.hpp>

#include "file.hpp"

namespace aie {
File::File(const char* fileName, const char* mode)
  : m_file{std::fopen(fileName, mode)}
{
  if (m_file == nullptr) {
    PL_THROW_WITH_SOURCE_INFO(
      std::runtime_error,
      "fopen failed, could not open file: " + std::string{fileName});
  }
}

File::~File()
{
  if (m_file != nullptr) {
    std::fclose(m_file);
  }
}

std::FILE* File::get()
{
  return m_file;
}

const std::FILE* File::get() const
{
  return m_file;
}
} // namespace aie
