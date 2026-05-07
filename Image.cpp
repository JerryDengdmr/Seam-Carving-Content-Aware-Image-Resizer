#include <cassert>
#include <string>
#include "Image.hpp"

using namespace std;

void Image_init(Image* img, int width, int height) {
  assert(0 < width && 0 < height);
  
  (*img).width = width;
  (*img).height = height;
  
  Matrix_init(&(*img).red_channel, width, height);
  Matrix_init(&(*img).green_channel, width, height);
  Matrix_init(&(*img).blue_channel, width, height);
}

void Image_init(Image* img, istream& is) {
  string magic;
  int width;
  int height;
  int max_val;

  is >> magic;
  is >> width;
  is >> height;
  is >> max_val;

  assert(magic == "P3");
  assert(max_val == 255);
  (*img).width = width;
  (*img).height = height;
  
  Matrix_init(&(*img).red_channel, width, height);
  Matrix_init(&(*img).green_channel, width, height);
  Matrix_init(&(*img).blue_channel, width, height);
  
  for (int row = 0; row < height; row++) {
    for (int col = 0; col < width; col++) {
      int red;
      int green;
      int blue;
      
      is >> red >> green >> blue;
      
      int* red_ptr = Matrix_at(&(*img).red_channel, row, col);
      *red_ptr = red;
      int* green_ptr = Matrix_at(&(*img).green_channel, row, col);
      *green_ptr = green;
      int* blue_ptr = Matrix_at(&(*img).blue_channel, row, col);
      *blue_ptr = blue;
    }
  }
}

void Image_print(const Image* img, ostream& os) {
  os << "P3" << "\n";
  os << (*img).width << " " << (*img).height << "\n";
  os << "255" << "\n";
  
  for (int row = 0; row < (*img).height; row = row + 1) {
    for (int col = 0; col < (*img).width; col = col + 1) {
      const int* red_ptr = Matrix_at(&(*img).red_channel, row, col);
      int red = *red_ptr;
      const int* green_ptr = Matrix_at(&(*img).green_channel, row, col);
      int green = *green_ptr;
      const int* blue_ptr = Matrix_at(&(*img).blue_channel, row, col);
      int blue = *blue_ptr;
      os << red << " " << green << " " << blue << " ";
    }
    os << "\n";
  }
}

int Image_width(const Image* img) {
  return (*img).width;
}

int Image_height(const Image* img) {
  return (*img).height;
}

Pixel Image_get_pixel(const Image* img, int row, int column) {
  assert(0 <= row && row < Image_height(img));
  assert(0 <= column && column < Image_width(img));
  
  Pixel p;
  const int* red_ptr = Matrix_at(&(*img).red_channel, row, column);
  const int* green_ptr = Matrix_at(&(*img).green_channel, row, column);
  const int* blue_ptr = Matrix_at(&(*img).blue_channel, row, column);
  
  p.r = *red_ptr;
  p.g = *green_ptr;
  p.b = *blue_ptr;
  
  return p;
}

void Image_set_pixel(Image* img, int row, int column, Pixel color) {
  assert(0 <= row && row < Image_height(img));
  assert(0 <= column && column < Image_width(img));
  
  int* red_ptr = Matrix_at(&(*img).red_channel, row, column);
  int* green_ptr = Matrix_at(&(*img).green_channel, row, column);
  int* blue_ptr = Matrix_at(&(*img).blue_channel, row, column);
  
  *red_ptr = color.r;
  *green_ptr = color.g;
  *blue_ptr = color.b;
}

void Image_fill(Image* img, Pixel color) {
  Matrix_fill(&(*img).red_channel, color.r);
  Matrix_fill(&(*img).green_channel, color.g);
  Matrix_fill(&(*img).blue_channel, color.b);
}
