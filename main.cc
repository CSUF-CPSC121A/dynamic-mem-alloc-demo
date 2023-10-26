#include <iostream>
#include "image.h"

// Loads an image given a filename
void LoadImage(const std::string& filename) {
    Image my_image{filename};
    my_image.Display();
}

// Asks the user to provide a filename and loads the image.
int main() {
    std::string filename;
    std::cout << "Please enter image filename: ";
    std::cin >> filename;
    LoadImage(filename);    
    return 0;
}