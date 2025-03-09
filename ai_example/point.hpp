#pragma once

namespace aie {
class Point {
public:
  constexpr Point(int xPosition, int yPosition)
    : m_xPosition{xPosition}, m_yPosition{yPosition}
  {
  }

  constexpr int x() const noexcept
  {
    return m_xPosition;
  }

  constexpr int y() const noexcept
  {
    return m_yPosition;
  }

private:
  int m_xPosition;
  int m_yPosition;
};
} // namespace
