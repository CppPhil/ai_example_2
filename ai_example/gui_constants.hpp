#pragma once
#include <string>
#include <vector>

#include "point.hpp"
#include "size.hpp"

namespace aie {
inline constexpr int windowWidth{300};
inline constexpr int windowHeight{400};
inline constexpr int verticalBorderThickness{30};
inline constexpr int horizontalBorderThickness{30};

inline constexpr int labelColumn{1};
inline constexpr int calculatedLabelsColumn{2};

inline constexpr char windowLabel[] = "AI example application";
inline constexpr char tableLabel[]  = "Results";

inline constexpr Point tableTopLeft{
  verticalBorderThickness,
  horizontalBorderThickness};
inline constexpr Size tableSize{
  windowWidth - verticalBorderThickness,
  windowHeight - horizontalBorderThickness};

extern const std::vector<std::string> columnHeaders;
} // namespace aie
