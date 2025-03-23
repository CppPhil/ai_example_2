#pragma once
#include <cstdio>

namespace aie {
class File {
public:
  File(const char* fileName, const char* mode);

  File(const File&) = delete;

  File& operator=(const File&) = delete;

  ~File();

  std::FILE* get();

  const std::FILE* get() const;

private:
  std::FILE* m_file;
};
} // namespace aie
