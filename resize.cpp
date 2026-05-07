 #include <iostream>
#include <fstream>
#include <string>
#include "processing.hpp"
#include "Image.hpp"

using namespace std;

int main(int argc, char *argv[]) {
  //Members of the argv
  string filename, newfile;
  int width, height;
  filename = argv[1];
  newfile = argv[2]; 

  //Create ifstream and check if file opened
  Image original_image;
  ifstream file(filename);

  if (!file.is_open()){
    cout << "Error opening file: " << filename << endl;

    return 1;
  }

  //Initialize Image object
  Image_init(&original_image, file);

  int orig_width = Image_width(&original_image);
  int orig_height = Image_height(&original_image);

  //Checks command line arguments & carve
  if (argc == 4){

    width = stoi(argv[3]);
    if (!(argc == 5 && stoi(argv[3]) > 0 && width <= orig_width)){

        cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
        << "WIDTH and HEIGHT must be less than or equal to original" << endl;

        return 1;
    } else {

        seam_carve_width(&original_image, width);
    }
  } else if (argc == 5){

    width = stoi(argv[3]);
    height = stoi(argv[4]);
    if (!(width > 0 && width <= orig_width && height > 0 && height <= orig_height)){

        cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
        << "WIDTH and HEIGHT must be less than or equal to original" << endl;

        return 1;
    } else{

        width = stoi(argv[3]);
        height = stoi(argv[4]);
        seam_carve(&original_image, width, height);
    }
  } else {

    cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
    << "WIDTH and HEIGHT must be less than or equal to original" << endl;

    return 1;
  }

  ofstream new_file(newfile);
  Image_print(&original_image, new_file);
}
