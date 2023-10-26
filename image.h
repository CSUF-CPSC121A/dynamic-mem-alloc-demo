#ifndef IMAGE_H
#define IMAGE_H

// Incomplete class that represents an Image. It can load and display an image
class Image {
  public:
    Image(const std::string& filename) {
        std::cout << "loading " << filename << "\n";
        // code that will load the image into the data character array.
    }
    void Display() {
        // code that will display the image.
    }
  private:
    char data[8000000000];
};

#endif