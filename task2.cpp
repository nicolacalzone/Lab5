#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

struct ThStruct
{
    Mat r1;
    Mat r2;
    Mat r3;
};

ThStruct methodByThresholding(Mat src)
{
    int thSky = 200;

    Mat mask1 = (src <= 130);
    Mat mask2 = (src >= 60);
    Mat maskAsphalt;
    bitwise_and(mask1, mask2, maskAsphalt);
    Mat maskSky = (src >= thSky);
    Mat maskRest = ~(maskAsphalt | maskSky);

    Mat region_asphalt, region_sky, region_else;
    src.copyTo(region_asphalt, maskAsphalt);
    src.copyTo(region_sky, maskSky);
    src.copyTo(region_else, maskRest);

    ThStruct res;
    res.r1 = region_asphalt;
    res.r2 = region_sky;
    res.r3 = region_else;

    return res;
}

ThStruct methodByKMeansClustering(int k, Mat src)
{
    TermCriteria criteria(TermCriteria::EPS + TermCriteria::COUNT, 10, 1.0);
    Mat labels, centers;
    kmeans(src, k, labels, criteria, 3, KMEANS_PP_CENTERS, centers);

    labels = labels.reshape(1, src.rows);

    Mat mask_asphalt = (labels == 0);
    Mat mask_sky = (labels == 1);
    Mat mask_else = (labels == 2);

    Mat region_asphalt, region_sky, region_else;
    src.copyTo(region_asphalt, mask_asphalt);
    src.copyTo(region_sky, mask_sky);
    src.copyTo(region_else, mask_else);

    ThStruct res;
    res.r1 = region_asphalt;
    res.r2 = region_sky;
    res.r3 = region_else;

    return res;
}

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

    cvtColor(src, src_gray, COLOR_BGR2GRAY);

    Mat blurImg;
    GaussianBlur(src_gray, blurImg, Size(5, 5), 0);
    dilate(blurImg, blurImg, Mat::ones(3, 3, CV_8UC1), Point(-1, 1), 10);

    // METHOD 1 --- THRESHOLDING
    ThStruct res1 = methodByThresholding(blurImg);
    imshow("Asphalt", res1.r1);
    imshow("Sky", res1.r2);
    imshow("Else", res1.r3);
    waitKey(0);

    // METHOD 2 --- KMEANS
    int k = 3; // number of clusters
    ThStruct res2 = methodByKMeansClustering(k, blurImg);

    imshow("Asphalt", res2.r1);
    imshow("Sky", res2.r2);
    imshow("Else", res2.r3);
    waitKey(0);

    waitKey(0);

    return 0;
}