#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include "utils.h"
#include "methods.h"

using namespace cv;
using namespace std;

// FUNCTIONS
void show(ThStruct res);

// MAIN
int main(int argc, char **argv)
{

    Mat src, srcGray;

    string str1 = "../street_scene.png";
    src = imread(str1, IMREAD_COLOR);
    if (src.empty())
    {
        cout << "Cannot read image " << src << endl;
        return -1;
    }

    Mat blurImg;
    GaussianBlur(src, blurImg, Size(5, 5), 0);
    // dilate(blurImg, blurImg, Mat::ones(3, 3, CV_8UC1), Point(-1, 1), 1);

    // METHOD 1 --- THRESHOLDING on GRAY Picture
    cvtColor(blurImg, srcGray, COLOR_BGR2GRAY);
    ThStruct res1 = thresholdMethod(srcGray);
    show(res1);

    // METHOD 2 --- KMEANS on COLORED Picture
    int numClusters = 3;
    ThStruct res2 = kmeansMethod2(numClusters, blurImg); // 3 is the number of clusters
    show(res2);

    return 0;
}

void show(ThStruct res)
{
    namedWindow("Asphalt", WINDOW_KEEPRATIO);
    imshow("Asphalt", res.r1);

    namedWindow("Else", WINDOW_KEEPRATIO);
    imshow("Else", res.r2);

    namedWindow("Sky", WINDOW_KEEPRATIO);
    imshow("Sky", res.r3);

    waitKey(0);
}
