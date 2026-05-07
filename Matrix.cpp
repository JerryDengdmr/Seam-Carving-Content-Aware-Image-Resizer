#include <cassert>
#include "Matrix.hpp"
using namespace std;

// REQUIRES: mat points to a Matrix
//           0 < width && 0 < height
// MODIFIES: *mat
// EFFECTS:  Initializes *mat as a Matrix with the given width and height,
//           with all elements initialized to 0.
void Matrix_init(Matrix* mat, int width, int height) {
  assert(width > 0);
  assert(height > 0);
  (*mat).width = width;
  (*mat).height = height;
  int total_elements = width * height;
  (*mat).data.assign(total_elements, 0);

}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: os
// EFFECTS:  First, prints the width and height for the Matrix to os:
//             WIDTH [space] HEIGHT [newline]
//           Then prints the rows of the Matrix to os with one row per line.
//           Each element is followed by a space and each row is followed
//           by a newline. This means there will be an "extra" space at
//           the end of each line.
void Matrix_print(const Matrix* mat, std::ostream& os) {
  os << (*mat).width << " " << (*mat).height << "\n";
  for (int row = 0; row < (*mat).height; row++) {
    for (int col = 0; col < (*mat).width; col++) {
      const int* element_ptr = Matrix_at(mat, row, col);
      os << *element_ptr << " ";
    }
    os << "\n";
  }
}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the width of the Matrix.
int Matrix_width(const Matrix* mat) {
  return (*mat).width;
}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the height of the Matrix.
int Matrix_height(const Matrix* mat) {
  return (*mat).height;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// MODIFIES: (The returned pointer may be used to modify an
//            element in the Matrix.)
// EFFECTS:  Returns a pointer to the element in the Matrix
//           at the given row and column.
int* Matrix_at(Matrix* mat, int row, int column) {
  assert(row >= 0 && row < Matrix_height(mat));
  assert(column >= 0 && column < Matrix_width(mat));
  int index = row * (*mat).width + column;
  return &(*mat).data[index];
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// EFFECTS:  Returns a pointer-to-const to the element in
//           the Matrix at the given row and column.
const int* Matrix_at(const Matrix* mat, int row, int column) {
  assert(row >= 0 && row < Matrix_height(mat));
  assert(column >= 0 && column < Matrix_width(mat));
  int index = row * (*mat).width + column;
  return &(*mat).data[index];
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element of the Matrix to the given value.
void Matrix_fill(Matrix* mat, int value) {
  for (int row = 0; row < (*mat).height; row++) {
    for (int col = 0; col < (*mat).width; col++) {
      int* element_ptr = Matrix_at(mat, row, col);
      *element_ptr = value;
    }
  }
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element on the border of the Matrix to
//           the given value. These are all elements in the first/last
//           row or the first/last column.
void Matrix_fill_border(Matrix* mat, int value) {
  int width = (*mat).width;
  int height = (*mat).height;
  for (int col = 0; col < width; col++) {
    int* element_ptr = Matrix_at(mat, 0, col);
    *element_ptr = value;
  }
  for (int col = 0; col < width; col++) {
    int* element_ptr = Matrix_at(mat, height - 1, col);
    *element_ptr = value;
  }
  for (int row = 1; row < height - 1; row++) {
    int* element_ptr = Matrix_at(mat, row, 0);
    *element_ptr = value;
  }
  for (int row = 1; row < height - 1; row++) {
    int* element_ptr = Matrix_at(mat, row, width - 1);
    *element_ptr = value;
  }
}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the value of the maximum element in the Matrix
int Matrix_max(const Matrix* mat) {
  const int* first_ptr = Matrix_at(mat, 0, 0);
  int max_value = *first_ptr;
  for (int row = 0; row < (*mat).height; row++) {
    for (int col = 0; col < (*mat).width; col++) {
      const int* element_ptr = Matrix_at(mat, row, col);
      int current_value = *element_ptr;
      if (current_value > max_value) {
        max_value = current_value;
      }
    }
  }
  return max_value;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column_start && column_end <= Matrix_width(mat)
//           column_start < column_end
// EFFECTS:  Returns the column of the element with the minimal value
//           in a particular region. The region is defined as elements
//           in the given row and between column_start (inclusive) and
//           column_end (exclusive).
//           If multiple elements are minimal, returns the column of
//           the leftmost one.
int Matrix_column_of_min_value_in_row(const Matrix* mat, 
  int row, int column_start, int column_end) {
    
  assert(row >= 0 && row < Matrix_height(mat));
  assert(column_start >= 0 && column_end <= Matrix_width(mat));
  assert(column_start < column_end);
  int min_col = column_start;
  const int* first_ptr = Matrix_at(mat, row, column_start);
  int min_value = *first_ptr;
  for (int col = column_start + 1; col < column_end; col++) {
    const int* element_ptr = Matrix_at(mat, row, col);
    int current_value = *element_ptr;
    if (current_value < min_value) {
      min_value = current_value;
      min_col = col;
    }
  }
  return min_col;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column_start && column_end <= Matrix_width(mat)
//           column_start < column_end
// EFFECTS:  Returns the minimal value in a particular region. The region
//           is defined as elements in the given row and between
//           column_start (inclusive) and column_end (exclusive).
int Matrix_min_value_in_row(const Matrix* mat, 
  int row, int column_start, int column_end) {

  assert(row >= 0 && row < Matrix_height(mat));
  assert(column_start >= 0 && column_end <= Matrix_width(mat));
  assert(column_start < column_end);
  const int* first_ptr = Matrix_at(mat, row, column_start);
  int min_value = *first_ptr;
  for (int col = column_start + 1; col < column_end; col++) {
    const int* element_ptr = Matrix_at(mat, row, col);
    int current_value = *element_ptr;
    if (current_value < min_value) {
      min_value = current_value;
    }
  }
  return min_value;
}
