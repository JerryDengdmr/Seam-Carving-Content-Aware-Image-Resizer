#include "Matrix.hpp"
#include "Matrix_test_helpers.hpp"
#include "unit_test_framework.hpp"
#include <sstream>
using namespace std;
TEST(test_fill_basic) {
  Matrix mat;
  const int width = 3;
  const int height = 5;
  const int value = 1;
  Matrix_init(&mat, 3, 5);
  Matrix_fill(&mat, value);
  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(&mat, r, c), value);
    }
  }
}
TEST(test_init_1x1) {
  Matrix mat;
  Matrix_init(&mat, 1, 1);
  ASSERT_EQUAL(Matrix_width(&mat), 1);
  ASSERT_EQUAL(Matrix_height(&mat), 1);
  ASSERT_EQUAL(*Matrix_at(&mat, 0, 0), 0);
}
TEST(test_init_zeros) {
  Matrix mat;
  Matrix_init(&mat, 4, 3);
  for (int r = 0; r < 3; r++) {
    for (int c = 0; c < 4; c++) {
      ASSERT_EQUAL(*Matrix_at(&mat, r, c), 0);
    }
  }
}
TEST(test_width_height) {
  Matrix mat;
  Matrix_init(&mat, 2, 1);
  ASSERT_EQUAL(Matrix_width(&mat), 2);
  ASSERT_EQUAL(Matrix_height(&mat), 1);
}
TEST(test_at_modify) {
  Matrix mat;
  Matrix_init(&mat, 3, 3);
  *Matrix_at(&mat, 1, 2) = 100;
  ASSERT_EQUAL(*Matrix_at(&mat, 1, 2), 100);
  ASSERT_EQUAL(*Matrix_at(&mat, 0, 0), 0);
}
TEST(test_at_corners) {
  Matrix mat;
  Matrix_init(&mat, 5, 4);
  *Matrix_at(&mat, 0, 0) = 1;
  *Matrix_at(&mat, 0, 4) = 2;
  *Matrix_at(&mat, 3, 0) = 3;
  *Matrix_at(&mat, 3, 4) = 4;
  ASSERT_EQUAL(*Matrix_at(&mat, 0, 0), 1);
  ASSERT_EQUAL(*Matrix_at(&mat, 0, 4), 2);
  ASSERT_EQUAL(*Matrix_at(&mat, 3, 0), 3);
  ASSERT_EQUAL(*Matrix_at(&mat, 3, 4), 4);
}
TEST(test_print_2x3) {
  Matrix mat;
  Matrix_init(&mat, 2, 3);
  *Matrix_at(&mat, 0, 0) = 1;
  *Matrix_at(&mat, 0, 1) = 2;
  *Matrix_at(&mat, 1, 0) = 3;
  *Matrix_at(&mat, 1, 1) = 4;
  *Matrix_at(&mat, 2, 0) = 5;
  *Matrix_at(&mat, 2, 1) = 6;
  ostringstream expected;
  expected << "2 3\n" << "1 2 \n" << "3 4 \n" << "5 6 \n";
  ostringstream actual;
  Matrix_print(&mat, actual);
  ASSERT_EQUAL(expected.str(), actual.str());
}
TEST(test_fill_negative) {
  Matrix mat;
  Matrix_init(&mat, 2, 2);
  Matrix_fill(&mat, -5);
  for (int r = 0; r < 2; r = r + 1) {
    for (int c = 0; c < 2; c = c + 1) {
      ASSERT_EQUAL(*Matrix_at(&mat, r, c), -5);
    }
  }
}
TEST(test_fill_border_3x3) {
  Matrix mat;
  Matrix_init(&mat, 3, 3);
  Matrix_fill(&mat, 0);
  Matrix_fill_border(&mat, 1);
  ASSERT_EQUAL(*Matrix_at(&mat, 0, 0), 1);
  ASSERT_EQUAL(*Matrix_at(&mat, 0, 1), 1);
  ASSERT_EQUAL(*Matrix_at(&mat, 0, 2), 1);
  ASSERT_EQUAL(*Matrix_at(&mat, 1, 0), 1);
  ASSERT_EQUAL(*Matrix_at(&mat, 1, 1), 0);
  ASSERT_EQUAL(*Matrix_at(&mat, 1, 2), 1);
  ASSERT_EQUAL(*Matrix_at(&mat, 2, 0), 1);
  ASSERT_EQUAL(*Matrix_at(&mat, 2, 1), 1);
  ASSERT_EQUAL(*Matrix_at(&mat, 2, 2), 1);
}
TEST(test_fill_border_1x5) {
  Matrix mat;
  Matrix_init(&mat, 5, 1);
  Matrix_fill(&mat, 0);
  Matrix_fill_border(&mat, 7);
  for (int c = 0; c < 5; c = c + 1) {
    ASSERT_EQUAL(*Matrix_at(&mat, 0, c), 7);
  }
}
TEST(test_fill_border_5x1) {
  Matrix mat;
  Matrix_init(&mat, 1, 5);
  Matrix_fill(&mat, 0);
  Matrix_fill_border(&mat, 8);
  for (int r = 0; r < 5; r = r + 1) {
    ASSERT_EQUAL(*Matrix_at(&mat, r, 0), 8);
  }
}
TEST(test_max_same_values) {
  Matrix mat;
  Matrix_init(&mat, 3, 3);
  Matrix_fill(&mat, 5);
  ASSERT_EQUAL(Matrix_max(&mat), 5);
}
TEST(test_max_different_positions) {
  Matrix mat;
  Matrix_init(&mat, 3, 3);
  Matrix_fill(&mat, 1);
  *Matrix_at(&mat, 2, 1) = 100;
  ASSERT_EQUAL(Matrix_max(&mat), 100);
}
TEST(test_max_negative) {
  Matrix mat;
  Matrix_init(&mat, 2, 2);
  *Matrix_at(&mat, 0, 0) = -10;
  *Matrix_at(&mat, 0, 1) = -5;
  *Matrix_at(&mat, 1, 0) = -20;
  *Matrix_at(&mat, 1, 1) = -1;
  ASSERT_EQUAL(Matrix_max(&mat), -1);
}
TEST(test_min_value_in_row_basic) {
  Matrix mat;
  Matrix_init(&mat, 5, 1);
  *Matrix_at(&mat, 0, 0) = 10;
  *Matrix_at(&mat, 0, 1) = 5;
  *Matrix_at(&mat, 0, 2) = 3;
  *Matrix_at(&mat, 0, 3) = 8;
  *Matrix_at(&mat, 0, 4) = 6;
  ASSERT_EQUAL(Matrix_min_value_in_row(&mat, 0, 0, 5), 3);
}
TEST(test_min_value_in_row_partial) {
  Matrix mat;
  Matrix_init(&mat, 5, 1);
  *Matrix_at(&mat, 0, 0) = 1;
  *Matrix_at(&mat, 0, 1) = 5;
  *Matrix_at(&mat, 0, 2) = 3;
  *Matrix_at(&mat, 0, 3) = 2;
  *Matrix_at(&mat, 0, 4) = 6;
  ASSERT_EQUAL(Matrix_min_value_in_row(&mat, 0, 1, 4), 2);
}
TEST(test_column_of_min_basic) {
  Matrix mat;
  Matrix_init(&mat, 5, 1);
  *Matrix_at(&mat, 0, 0) = 10;
  *Matrix_at(&mat, 0, 1) = 5;
  *Matrix_at(&mat, 0, 2) = 3;
  *Matrix_at(&mat, 0, 3) = 8;
  *Matrix_at(&mat, 0, 4) = 6;
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(&mat, 0, 0, 5), 2);
}
TEST(test_column_of_min_tie) {
  Matrix mat;
  Matrix_init(&mat, 5, 1);
  *Matrix_at(&mat, 0, 0) = 5;
  *Matrix_at(&mat, 0, 1) = 3;
  *Matrix_at(&mat, 0, 2) = 3;
  *Matrix_at(&mat, 0, 3) = 3;
  *Matrix_at(&mat, 0, 4) = 7;
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(&mat, 0, 0, 5), 1);
}
TEST(test_column_of_min_single) {
  Matrix mat;
  Matrix_init(&mat, 5, 1);
  *Matrix_at(&mat, 0, 0) = 10;
  *Matrix_at(&mat, 0, 1) = 5;
  *Matrix_at(&mat, 0, 2) = 3;
  *Matrix_at(&mat, 0, 3) = 8;
  *Matrix_at(&mat, 0, 4) = 6;
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(&mat, 0, 2, 3), 2);
}
TEST(test_matrix_equal) {
  Matrix mat1;
  Matrix mat2;
  Matrix_init(&mat1, 2, 2);
  Matrix_init(&mat2, 2, 2);
  Matrix_fill(&mat1, 5);
  Matrix_fill(&mat2, 5);
  ASSERT_TRUE(Matrix_equal(&mat1, &mat2));
}
TEST_MAIN()