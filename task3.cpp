#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include "methods.h"

using namespace cv;
using namespace std;

int main(int argc, char **argv)
{
    Mat src;

    string str1 = "../robocup.jpg";
    src = imread(str1, IMREAD_COLOR);

    if (src.empty() || !src.data)
    {
        cout << "Cannot read image " << src << endl;
        return -1;
    }

    Mat blurImg;
    GaussianBlur(src, blurImg, Size(5, 5), 0);

    int numClusters = 6;
    Mat res = kmeansMethod3(numClusters, blurImg);

    // if clusters are 5, the ball goes together with the shirts
    // if clusters are 4, ball goes together with shirts but shirts go together with arms / other parts
    // if clusters are 3, the ball gets halfly lost in the ground

    namedWindow("Result", WINDOW_KEEPRATIO);
    imshow("Result", res);
    waitKey(0);

    // TAKE ONLY THE SHIRTS:
    Scalar low = Scalar(5, 80, 100); // BGR
    Scalar high = Scalar(80, 200, 250);
    inRange(res, low, high, res);
    namedWindow("Result", WINDOW_KEEPRATIO);
    imshow("Result", res);
    waitKey(0);

    // Better doing inRange because you never know where is a cluster stored in the labels... It might be in
    // a certain label once and in another the next time. So this is the only way

    return 0;
}