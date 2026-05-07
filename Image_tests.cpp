#include "Matrix.hpp"
#include "Image.hpp"
#include "Image_test_helpers.hpp"
#include "unit_test_framework.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cassert>
using namespace std;
TEST(test_print_basic) {
  Image img;
  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};
  Image_init(&img, 2, 2);
  Image_set_pixel(&img, 0, 0, red);
  Image_set_pixel(&img, 0, 1, green);
  Image_set_pixel(&img, 1, 0, blue);
  Image_set_pixel(&img, 1, 1, white);
  ostringstream s;
  Image_print(&img, s);
  ostringstream correct;
  correct << "P3\n2 2\n255\n";
  correct << "255 0 0 0 255 0 \n";
  correct << "0 0 255 255 255 255 \n";
  ASSERT_EQUAL(s.str(), correct.str());
}
TEST(test_init_1x1) {
  Image img;
  Image_init(&img, 1, 1);
  ASSERT_EQUAL(Image_width(&img), 1);
  ASSERT_EQUAL(Image_height(&img), 1);
  Pixel p = Image_get_pixel(&img, 0, 0);
  ASSERT_EQUAL(p.r, 0);
  ASSERT_EQUAL(p.g, 0);
  ASSERT_EQUAL(p.b, 0);
}
TEST(test_init_black) {
  Image img;
  Image_init(&img, 3, 2);
  for (int r = 0; r < 2; r = r + 1) {
    for (int c = 0; c < 3; c = c + 1) {
      Pixel p = Image_get_pixel(&img, r, c);
      ASSERT_EQUAL(p.r, 0);
      ASSERT_EQUAL(p.g, 0);
      ASSERT_EQUAL(p.b, 0);
    }
  }
}
TEST(test_width_height) {
  Image img;
  Image_init(&img, 5, 3);
  ASSERT_EQUAL(Image_width(&img), 5);
  ASSERT_EQUAL(Image_height(&img), 3);
}
TEST(test_set_get_pixel) {
  Image img;
  Image_init(&img, 3, 3);
  Pixel color = {1, 2, 3};
  Image_set_pixel(&img, 1, 2, color);
  Pixel result = Image_get_pixel(&img, 1, 2);
  ASSERT_TRUE(Pixel_equal(result, color));
}
TEST(test_set_pixel_corners) {
  Image img;
  Image_init(&img, 4, 3);
  Pixel p1 = {1, 2, 3};
  Pixel p2 = {4, 5, 6};
  Pixel p3 = {7, 8, 9};
  Pixel p4 = {10, 11, 12};
  Image_set_pixel(&img, 0, 0, p1);
  Image_set_pixel(&img, 0, 3, p2);
  Image_set_pixel(&img, 2, 0, p3);
  Image_set_pixel(&img, 2, 3, p4);
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(&img, 0, 0), p1));
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(&img, 0, 3), p2));
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(&img, 2, 0), p3));
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(&img, 2, 3), p4));
}
TEST(test_fill) {
  Image img;
  Image_init(&img, 3, 2);
  Pixel color = {1, 2, 3};
  Image_fill(&img, color);
  for (int r = 0; r < 2; r = r + 1) {
    for (int c = 0; c < 3; c = c + 1) {
      ASSERT_TRUE(Pixel_equal(Image_get_pixel(&img, r, c), color));
    }
  }
}
TEST(test_fill_white) {
  Image img;
  Image_init(&img, 2, 2);
  Pixel white = {255, 255, 255};
  Image_fill(&img, white);
  for (int r = 0; r < 2; r = r + 1) {
    for (int c = 0; c < 2; c = c + 1) {
      ASSERT_TRUE(Pixel_equal(Image_get_pixel(&img, r, c), white));
    }
  }
}
TEST(test_print_1x1) {
  Image img;
  Image_init(&img, 1, 1);
  Pixel p = {1, 2, 3};
  Image_set_pixel(&img, 0, 0, p);
  ostringstream actual;
  Image_print(&img, actual);
  ostringstream expected;
  expected << "P3\n1 1\n255\n";
  expected << "1 2 3 \n";
  ASSERT_EQUAL(actual.str(), expected.str());
}
TEST(test_init_from_stream) {
  Image img;
  string input = "P3\n2 2\n255\n255 0 0 0 255 0\n0 0 255 255 255 255\n";
  istringstream ss(input);
  Image_init(&img, ss);
  ASSERT_EQUAL(Image_width(&img), 2);
  ASSERT_EQUAL(Image_height(&img), 2);
  Pixel red = {255, 0, 0};
  Pixel green = {0, 255, 0};
  Pixel blue = {0, 0, 255};
  Pixel white = {255, 255, 255};
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(&img, 0, 0), red));
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(&img, 0, 1), green));
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(&img, 1, 0), blue));
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(&img, 1, 1), white));
}
TEST(test_init_from_stream_whitespace) {
  Image img;
  string input = "P3 2 2\t255 100 50 25\n75\n125 175 200 150 100 50 25 0\n";
  istringstream ss(input);
  Image_init(&img, ss);
  ASSERT_EQUAL(Image_width(&img), 2);
  ASSERT_EQUAL(Image_height(&img), 2);
  Pixel p00 = Image_get_pixel(&img, 0, 0);
  ASSERT_EQUAL(p00.r, 100);
  ASSERT_EQUAL(p00.g, 50);
  ASSERT_EQUAL(p00.b, 25);
}
TEST(test_ppm_roundtrip) {
  Image img1;
  Image_init(&img1, 3, 2);
  Image_set_pixel(&img1, 0, 0, {10, 20, 30});
  Image_set_pixel(&img1, 0, 1, {40, 50, 60});
  Image_set_pixel(&img1, 0, 2, {70, 80, 90});
  Image_set_pixel(&img1, 1, 0, {100, 110, 120});
  Image_set_pixel(&img1, 1, 1, {130, 140, 150});
  Image_set_pixel(&img1, 1, 2, {160, 170, 180});
  ostringstream out;
  Image_print(&img1, out);
  Image img2;
  istringstream in(out.str());
  Image_init(&img2, in);
  ASSERT_TRUE(Image_equal(&img1, &img2));
}
TEST(test_image_equal) {
  Image img1;
  Image img2;
  Image_init(&img1, 2, 2);
  Image_init(&img2, 2, 2);
  Pixel color = {1, 2, 3};
  Image_fill(&img1, color);
  Image_fill(&img2, color);
  ASSERT_TRUE(Image_equal(&img1, &img2));
}
TEST(test_image_not_equal) {
  Image img1;
  Image img2;
  Image_init(&img1, 2, 2);
  Image_init(&img2, 2, 2);
  Pixel color1 = {1, 2, 3};
  Pixel color2 = {4, 5, 6};
  Image_fill(&img1, color1);
  Image_fill(&img2, color2);
  ASSERT_FALSE(Image_equal(&img1, &img2));
}
TEST(test_load_dog) {
  Image img;
  ifstream x("dog.ppm");
  Image_init(&img, x);
  ASSERT_EQUAL(Image_width(&img), 5);
  ASSERT_EQUAL(Image_height(&img), 5);
}
TEST_MAIN()
