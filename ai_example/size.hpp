#pragma once

namespace aie {
class Size {
public:
  constexpr Size(int width, int height) : m_width{width}, m_height{height}
  {
  }

  constexpr int width() const noexcept
  {
    return m_width;
  }

  constexpr int height() const noexcept
  {
    return m_height;
  }

private:
  int m_width;
  int m_height;
};
} // namespace aie
