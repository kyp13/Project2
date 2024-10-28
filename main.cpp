#include "image_processing.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

void executeTask(Image& img1, Image& img2, Image& img3, Image& newImg, int task);
bool compareFiles(const string& outputFile, const string& exampleFile);

int main(){
    vector<string> files = {
        "layer1.tga", "layer2.tga", "layer_blue.tga", "layer_green.tga", "layer_red.tga",
            "pattern1.tga", "pattern2.tga", "text.tga", "text2.tga", "car.tga", "circles.tga"};
    string filePath = "input/";
    Image image1, image2, image3, newImage;

    for(int task = 1; task <=10; task++) {
        executeTask(image1, image2, image3, newImage, task);
    }

    for(int task = 1; task <= 10; task++) {
        string outputFile = "output/part" + to_string(task) + ".tga";
        string exampleFile = "examples/EXAMPLE_part" + to_string(task) + ".tga";
        if(compareFiles(outputFile, exampleFile)) {
            cout << task << "Test: " << "Complete: Files are identical."<< endl;
        }
        else {
            cout << task << "Test: " << "Failed: Files are identical."<< endl;
        }
    }

    return 0;
}

void executeTask(Image& img1, Image& img2, Image& img3, Image& newImg, int task) {
    vector<string> files = {"layer1.tga", "layer2.tga", "layer_blue.tga", "layer_green.tga", "layer_red.tga",
        "pattern1.tga", "pattern2.tga", "text.tga", "text2.tga", "car.tga", "circles.tga"
    };
    string path = "input/";
    Image img1, img2, img3, newImage;

    if (task == 1) {
        img1.loadImage(path + files[0], img1);
        img2.loadImage(path + files[5], img2);
    }
    if(task == 2) {
        img1.loadImage(path + files[0], img1);
        img2.loadImage(path + files[6], img2);
    }
    if(task == 3) {
        img1.loadImage(path + files[0], img1);
        img2.loadImage(path + files[6], img2);
    }
    if(task == 4) {
        img1.loadImage(path + files[1], img1);
        img2.loadImage(path + files[10], img2);
    }
    if(task == 5) {
        img1.loadImage(path + files[0], img1);
        img2.loadImage(path + files[5], img2);
    }
    if(task == 6) {
        img1.loadImage(path + files[9], img1);
    }
    if(task == 7) {
        img1.loadImage(path + files[9], img1);
    }
    if(task == 9) {
        img1.loadImage(path + files[4], img1);
        img2.loadImage(path + files[3], img2);
        img3.loadImage(path + files[2], img3);
    }
    if(task == 10) {
        img1.loadImage(path + files[8], img1);
    }

    if (task == 9) {
        img2 = nullptr;
        newImage.tasks(img1, img3, img2, newImage, task, "");
    }
    if(task != 9) {
        Image* img3 = nullptr;
        newImage.tasks(img1, img2, img3, newImage, task, "");
    }
}