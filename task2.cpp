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
ThStruct methodByKMeansClustering(int k, Mat src);
ThStruct methodByThresholding(Mat src);
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
    dilate(blurImg, blurImg, Mat::ones(3, 3, CV_8UC1), Point(-1, 1), 1);

    // METHOD 1 --- THRESHOLDING on GRAY Picture
    ThStruct res1 = methodByThresholding(blurImg);
    show(res1);

    // METHOD 2 --- KMEANS on COLORED Picture
    ThStruct res2 = methodByKMeansClustering(3, blurImg); // 3 is the number of clusters
    show(res2);

    return 0;
}

ThStruct methodByThresholding(Mat src)
{

    cvtColor(src, src, COLOR_BGR2GRAY);

    int thSky = 200;

    Mat mask1 = (src <= 130);
    Mat mask2 = (src >= 60);
    Mat maskAsphalt;
    bitwise_and(mask1, mask2, maskAsphalt);
    Mat maskSky = (src >= thSky);
    Mat maskRest = ~(maskAsphalt | maskSky);

    ThStruct res;
    src.copyTo(res.r1, maskAsphalt);
    src.copyTo(res.r2, maskSky);
    src.copyTo(res.r3, maskRest);

    return res;
}

ThStruct methodByKMeansClustering(int k, Mat src)
{
    TermCriteria criteria(TermCriteria::EPS + TermCriteria::COUNT, 10, 1.0);
    Mat1f centers;
    Mat labels;
    src.convertTo(src, CV_32F);
    kmeans(src, k, labels, criteria, 3, KMEANS_PP_CENTERS, centers);

    labels = labels.reshape(3, src.rows);
    labels.convertTo(labels, CV_8U);

    Mat maskAsphalt = (labels == 0);
    Mat maskSky = (labels == 1);
    Mat maskRest = (labels == 2);

    // reshape masks to have same size as src
    maskAsphalt = maskAsphalt.reshape(src.rows, src.cols);
    maskSky = maskSky.reshape(src.rows, src.cols);
    maskRest = maskRest.reshape(src.rows, src.cols);

    ThStruct res;
    src.copyTo(res.r1, maskAsphalt);
    src.copyTo(res.r2, maskSky);
    src.copyTo(res.r3, maskRest);

    return res;
}

void show(ThStruct res)
{
    namedWindow("Asphalt", WINDOW_KEEPRATIO);
    imshow("Asphalt", res.r1);

    namedWindow("Sky", WINDOW_KEEPRATIO);
    imshow("Sky", res.r2);

    namedWindow("Else", WINDOW_KEEPRATIO);
    imshow("Else", res.r3);

    waitKey(0);
}
