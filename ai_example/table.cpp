#include <utility>

#include <FL/fl_draw.H>

#include <pl/assert.hpp>

#include "table.hpp"

namespace aie {
Table::Table(
  Point                    topLeft,
  Size                     size,
  std::vector<std::string> rowHeaders,
  std::vector<std::string> columnHeaders,
  std::string              label,
  int                      imageWidth,
  int                      imageHeight)
  : Fl_Table{topLeft.x(), topLeft.y(), size.width(), size.height()}
  , m_rowCount{rowHeaders.size()}
  , m_columnCount{columnHeaders.size()}
  , m_rowHeaders{std::move(rowHeaders)}
  , m_columnHeaders{std::move(columnHeaders)}
  , m_label{std::move(label)}
  , m_matrix{}
{
  Fl_Widget::label(m_label.c_str()); // Set the label.
  m_matrix.resize(
    static_cast<std::size_t>(m_rowCount),
    std::vector<std::string>(static_cast<std::size_t>(m_columnCount)));

  rows(m_rowCount); // Set the number of rows in the table.
  row_header(1);    // Show headers for the rows.
  row_height_all(
    imageHeight);      // Set the height of all rows to imageHeight pixels.
  row_resize(0);       // Don't allow rows to be resized.
  cols(m_columnCount); // Set the number of columns in the table.
  col_header(1);       // Show column headers.
  col_width_all(
    imageWidth); // Set the width of all columns to imageWith pixels.
  col_resize(0); // don't allow columns to be resized.
  end(); // End the group: any new widgets added to the widget tree will be
         // added to the parent of the group.
}

int Table::rowCount() const
{
  return m_rowCount;
}

int Table::columnCount() const
{
  return m_columnCount;
}

void Table::loadImages(
  const std::vector<std::vector<std::byte>>& images,
  int                                        width,
  int                                        height)
{
  PL_CHECK_PRE(images.size() == static_cast<std::size_t>(m_rowCount));

  for (std::size_t i{0}; i < images.size(); ++i) {
    const std::vector<std::byte>& imageBytes{images.at(i)};
    at(/* row */ i, /* column */ 0)
      .assign(
        reinterpret_cast<const char*>(&imageBytes[0]),
        reinterpret_cast<const char*>(&imageBytes[0]) + imageBytes.size());
  }
}

std::string& Table::at(int row, int column)
{
  return m_matrix.at(static_cast<std::size_t>(row))
    .at(static_cast<std::size_t>(column));
}

const std::string& Table::at(int row, int column) const
{
  return const_cast<Table*>(this)->at(row, column);
}

void Table::draw_cell(
  TableContext context,
  int          row,
  int          column,
  int          x,
  int          y,
  int          w,
  int          h)
{
  switch (context) {
  case CONTEXT_STARTPAGE: // Before drawing a page -> set the font.
    fl_font(
      FL_HELVETICA, 17); // Sets the current font, which is then used in various
                         // drawing routines. (font face, font size)
    return;
  case CONTEXT_COL_HEADER:
    drawHeader(
      m_columnHeaders.at(static_cast<std::size_t>(column)), x, y, w, h);
    return;
  case CONTEXT_ROW_HEADER:
    drawHeader(m_rowHeaders.at(static_cast<std::size_t>(row)), x, y, w, h);
    return;
  case CONTEXT_CELL:
    drawData(at(row, column), x, y, w, h, row, column);
    return;
  }
}

void Table::drawHeader(const std::string& string, int x, int y, int w, int h)
{
  // FLTK uses a clip stack.

  fl_push_clip(
    x, y, w, h); // Intersects the current clip region with a rectangle and
                 // pushes this new region onto the stack.
  fl_draw_box(FL_THIN_UP_BOX, x, y, w, h, row_header_color()); // Draw a box.
  fl_color(FL_BLACK); // Sets the color for all subsequent drawing operations.
  fl_draw(string.c_str(), x, y, w, h, FL_ALIGN_CENTER); // Draw a string.
  fl_pop_clip(); // Restores the previous clip region.
}

void Table::drawData(
  const std::string& string,
  int                x,
  int                y,
  int                w,
  int                h,
  int                row,
  int                column)
{
  constexpr int imageColumn{0};

  if (column == imageColumn) {
    fl_push_clip(x, y, w, h);
    fl_draw_image_mono( // Draw the grayscale image.
      /* buf */ reinterpret_cast<const uchar*>(string.data()),
      /* X */ x,
      /* Y */ y,
      /* W */ w,
      /* H */ h);
    fl_pop_clip();
    return;
  }

  fl_push_clip(x, y, w, h);
  fl_color(FL_WHITE);
  fl_rectf(x, y, w, h); // Fill the background in white.
  fl_color(FL_GRAY0);
  fl_draw(string.c_str(), x, y, w, h, FL_ALIGN_CENTER); // Write the label.
  fl_pop_clip();
}
} // namespace aie
