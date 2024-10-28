#include "image_processing.h"


Image::Image() {
    ptrImage = nullptr;
}

Image::~Image() {
    delete[] ptrImage;
}


void Image::tasks(Image &image1, Image &image2, Image &image3, Image &newImage, unsigned int task, const string &tracker) {
    string fileName = "output/part" + to_string(task) + (task == 8 ? tracker : "") + ".tga";
    if (newImage.ptrImage == nullptr) {
        newImage.ptrImage = new unsigned char**[newImage.w];
        for(int i = 0; i < newImage.w; i++) {
            newImage.ptrImage[i] = new unsigned char*[newImage.h];
            for(int j = 0; j<newImage.h; j++) {
                newImage.ptrImage[i][j] = new unsigned char[3];
            }
        }
    }

    for(int i = 0; i<newImage.w; i++) {
        for(int j = 0; j<newImage.h; j++) {
            for(int k = 0; k<3; k++) {
                switch(task) {
                    case 1:
                        newImage.ptrImage[i][j][k] = processMultiply(image1.ptrImage[i][j][k], image2.ptrImage[i][j][k]);
                        break;
                    case 2:
                        newImage.ptrImage[i][j][k] = processSubtract(image1.ptrImage[i][j][k], image2.ptrImage[i][j][k]);
                        break;
                    case 3:
                        newImage.ptrImage[i][j][k] = processScreen(
                            processMultiply(image1.ptrImage[i][j][k], image2.ptrImage[i][j][k]), image3.ptrImage[i][j][k]);
                        break;
                    case 4:
                        newImage.ptrImage[i][j][k] = processSubtract(
                            processMultiply(image1.ptrImage[i][j][k], image2.ptrImage[i][j][k]), image3.ptrImage[i][j][k]);
                        break;
                    case 5:
                        newImage.ptrImage[i][j][k] = processOverlay(image1.ptrImage[i][j][k], image2.ptrImage[i][j][k]);
                        break;
                    case 6:
                        if(k == 1) {
                            newImage.ptrImage[i][j][k] = min(255, image1.ptrImage[i][j][k]+200);
                        }
                        else {
                            newImage.ptrImage[i][j][k] = image1.ptrImage[i][j][k];
                        }
                        break;
                    case 7:
                        if(k==0) {
                            newImage.ptrImage[i][j][k] = 0;
                        }
                        else if(k==2) {
                            int scale = image1.ptrImage[i][j][k]*4;
                            newImage.ptrImage[i][j][k] = (scale > 255) ? 255 : scale;
                        }
                        else {
                            newImage.ptrImage[i][j][k] = image1.ptrImage[i][j][k];
                        }
                        break;
                    case 8:
                        newImage.ptrImage[i][j][k] = image1.ptrImage[i][j][k];
                        break;
                    case 9:
                        if(k == 0) {
                            newImage.ptrImage[i][j][k] = image3.ptrImage[i][j][k];
                        }
                        else if(k==1) {
                            newImage.ptrImage[i][j][k] = image2.ptrImage[i][j][k];
                        }
                        else if(k==2) {
                            newImage.ptrImage[i][j][k] = image1.ptrImage[i][j][k];
                        }
                        break;
                    case 10:
                        newImage.ptrImage[i][j][k] = image1.ptrImage[image1.w - i - 1][image1.h - j - 1][k];
                        break;
                }
            }
        }
    }
    if(task != 8) {
        writeHeader(fileName, newImage);
        writeImage(fileName, newImage);
    }
}
unsigned char Image::processMultiply(unsigned char p1, unsigned char p2) {
    return static_cast<unsigned char>((p1 / 255.0f) * (p2/ 255.0f) * 255.0f);
}

unsigned char Image::processSubtract(unsigned char p1, unsigned char p2) {
    int result = p1 - p2;
    return static_cast<unsigned char>(max(0, result));
}

unsigned char Image::processScreen(unsigned char p1, unsigned char p2) {
    return static_cast<unsigned char>(255 -(255 -p1) * (255-p2)/ 255.0f);
}

unsigned char Image::processOverlay(unsigned char p1, unsigned char p2) {
    float np1 = p1 / 255.0f;
    float np2 = p2 / 255.0f;
    return static_cast<unsigned char>((np2 <= 0.5f) ? (2 * np1 * np2 * 255) : ((1 -2 *(1-np1) * (1-np2)) * 255));
}

void Image::writeHeader(const string& fileName, const Image& image) {
    ofstream file(fileName, ios::binary | ios::out);
    file.write(reinterpret_cast<const char*>(&image.header), sizeof(Header));
    file.close();
}
void Image::writeImage(const string& fileName, const Image& image) {
    ofstream file(fileName, ios::binary | ios::app);
    for(int i = 0; i < image.h; i++) {
        for(int j = 0; j < image.w; j++) {
            file.write(reinterpret_cast<const char*>(image.ptrImage[i][j]), 3);
        }
    }
    file.close();
}

void Image::loadImage(const string& fileName, Image& image) {
    ifstream file(fileName, ios::binary);
    file.read(reinterpret_cast<char*>(&image.header), sizeof(Header));

    if(image.ptrImage == nullptr) {
        image.ptrImage = new unsigned char**[image.h];
        for(int i = 0; i < image.h; i++) {
            image.ptrImage[i] = new unsigned char*[image.w];
            for(int j = 0; j<image.w; j++) {
                image.ptrImage[i][j] = new unsigned char[3];
            }
        }
    }

    for(int i = 0; i < image.h; i++) {
        for(int j = 0; j < image.w; j++) {
            file.read(reinterpret_cast<char*>(image.ptrImage[i][j]), 3);
        }
    }


}

