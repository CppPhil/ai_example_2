#pragma once
#include <cstddef>

#include <string>
#include <vector>

#include <FL/Fl_Table.H>

#include "point.hpp"
#include "size.hpp"

namespace aie {
class Table : public Fl_Table {
public:
  Table(
    Point                    topLeft,
    Size                     size,
    std::vector<std::string> rowHeaders,
    std::vector<std::string> columnHeaders,
    std::string              label,
    int                      imageWidth,
    int                      imageHeight);

  int rowCount() const;

  int columnCount() const;

  void loadImages(
    const std::vector<std::vector<std::byte>>& images,
    int                                        width,
    int                                        height);

  std::string& at(int row, int column);

  const std::string& at(int row, int column) const;

protected:
  void draw_cell(
    TableContext context,
    int          row    = 0,
    int          column = 0,
    int          x      = 0,
    int          y      = 0,
    int          w      = 0,
    int          h      = 0) override;

private:
  void drawHeader(const std::string& string, int x, int y, int w, int h);

  void drawData(
    const std::string& string,
    int                x,
    int                y,
    int                w,
    int                h,
    int                row,
    int                column);

  std::size_t                           m_rowCount;
  std::size_t                           m_columnCount;
  std::vector<std::string>              m_rowHeaders;
  std::vector<std::string>              m_columnHeaders;
  std::string                           m_label;
  std::vector<std::vector<std::string>> m_matrix;
};
} // namespace aie
