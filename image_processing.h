#ifndef IMAGE_PROCESSING_H
#define IMAGE_PROCESSING_H

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

struct Pixel {
    unsigned char blue, green, red;
};

struct Header {
    char idLength;
    char colorMapType;
    char dataTypeCode;
    short colorMapOrigin;;
    short colorMapLength;
    short colorMapDepth;;
    short xOrigin;
    short yOrigin;
    short width;
    short height;
    char bitsPerPixel;
    char imageDescriptor;
};

class Image {
public:
    Header header;
    vector<Pixel> pixels;
    char idLen, cMapType, dTypeCode, bitsPer, imageDesc;
    short w, h, cMapOrigin, cMapLength, xOr,yOr;
    unsigned char ***ptrImage;

    Image();
    ~Image();
    void operator=(const Header& obj);
    void operator=(const Image& obj);

    void tasks(Image& image1, Image& image2, Image& image3, Image& newImage, unsigned int taskNum, const string& tracker);
    unsigned char processMultiply(unsigned char p1, unsigned char p2);
    unsigned char processSubtract(unsigned char p1, unsigned char p2);
    unsigned char processScreen(unsigned char p1, unsigned char p2);
    unsigned char processOverlay(unsigned char p1, unsigned char p2);

    void writeHeader(const string& fileName, const Image& image);
    void writeImage(const string& fileName, const Image& image);
    void loadHeader(const string& fileName, Image& image);
    void loadImage(const string& fileName, Image& image);
    void loadFirst(const string& fileName, Image& image);


};

#endif //IMAGE_PROCESSING_H
