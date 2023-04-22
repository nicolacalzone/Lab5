#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

// GLOBAL
struct ThStruct
{
    Mat r1;
    Mat r2;
    Mat r3;
};

// FUNCTIONS
ThStruct kmeansMethod(int k, Mat src);
ThStruct thresholdMethod(Mat src);
void show(ThStruct res);

// MAIN
int main(int argc, char **argv)
{

    Mat src, src_gray;

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
    ThStruct res1 = thresholdMethod(blurImg);
    show(res1);

    // METHOD 2 --- KMEANS on COLORED Picture
    ThStruct res2 = kmeansMethod(3, blurImg); // 3 is the number of clusters
    show(res2);

    return 0;
}

ThStruct thresholdMethod(Mat src)
{

    cvtColor(src, src, COLOR_BGR2GRAY);

    int thSky = 160;

    Mat mask1 = (src <= 140);
    Mat mask2 = (src >= 60);
    Mat maskAsphalt;
    bitwise_and(mask1, mask2, maskAsphalt);
    Mat maskSky = (src >= thSky);
    Mat maskRest = ~(maskAsphalt | maskSky);

    ThStruct res;
    src.copyTo(res.r1, maskAsphalt);
    src.copyTo(res.r3, maskSky);
    src.copyTo(res.r2, maskRest);

    return res;
}

ThStruct kmeansMethod(int k, Mat src)
{
    vector<int> labels;
    Mat1f colors;
    int attempts = 5;
    TermCriteria criteria = TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 10, 1.);

    Mat input = src.reshape(1, src.rows * src.cols);
    input.convertTo(input, CV_32F);

    kmeans(input, k, labels, criteria, attempts, KMEANS_PP_CENTERS, colors);

    Mat maskAsphalt = Mat::zeros(src.size(), CV_8U);
    Mat maskSky = Mat::zeros(src.size(), CV_8U);
    Mat maskElse = Mat::zeros(src.size(), CV_8U);

    for (int i = 0; i < src.rows * src.cols; i++)
    {
        if (labels[i] == 0)
        {
            maskAsphalt.at<uchar>(i / src.cols, i % src.cols) = 255;
        }
        else if (labels[i] == 1)
        {
            maskSky.at<uchar>(i / src.cols, i % src.cols) = 255;
        }
        else if (labels[i] == 2)
        {
            maskElse.at<uchar>(i / src.cols, i % src.cols) = 255;
        }
    }

    ThStruct res;
    src.copyTo(res.r1, maskAsphalt);
    src.copyTo(res.r2, maskSky);
    src.copyTo(res.r3, maskElse);

    return res;
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
