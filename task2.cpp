#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include "utils.h"
#include "methods.h"

// FUNCTIONS
void show(KMeansRes res);

// MAIN
int main(int argc, char **argv)
{

    cv::Mat src, blurGray;

    std::string str1 = "../street_scene.png";
    src = cv::imread(str1, cv::IMREAD_COLOR);
    if (src.empty() || !src.data)
    {
        std::cout << "Cannot read image " << src << std::endl;
        return -1;
    }

    cv::Mat blurImg;
    cv::GaussianBlur(src, blurImg, cv::Size(5, 5), 0);
    // dilate(blurImg, blurImg, Mat::ones(3, 3, CV_8UC1), Point(-1, 1), 1);

    // METHOD 1 --- THRESHOLDING on GRAY Picture
    cv::cvtColor(blurImg, blurGray, cv::COLOR_BGR2GRAY);
    KMeansRes res1 = thresholdMethod(blurGray);
    show(res1);

    // METHOD 2 --- KMEANS on COLORED Picture
    int numClusters = 3;
    KMeansRes res2 = kmeansMethod2(numClusters, blurImg); // 3 is the number of clusters
    show(res2);

    return 0;
}

void show(KMeansRes res)
{
    cv::namedWindow("Asphalt", cv::WINDOW_KEEPRATIO);
    cv::imshow("Asphalt", res.r1);

    cv::namedWindow("Else", cv::WINDOW_KEEPRATIO);
    cv::imshow("Else", res.r2);

    cv::namedWindow("Sky", cv::WINDOW_KEEPRATIO);
    cv::imshow("Sky", res.r3);

    cv::waitKey(0);
}

KMeansRes kmeansMethod2(int k, cv::Mat &src)
{
    std::vector<int> labels;
    cv::Mat1f colors;
    int attempts = 5;
    cv::TermCriteria criteria = cv::TermCriteria(cv::TermCriteria::EPS + cv::TermCriteria::COUNT, 10, 1.);

    cv::Mat input = src.reshape(1, src.rows * src.cols);
    input.convertTo(input, CV_32F);

    cv::kmeans(input, k, labels, criteria, attempts, cv::KMEANS_PP_CENTERS, colors);

    cv::Mat maskAsphalt = cv::Mat::zeros(src.size(), CV_8U);
    cv::Mat maskSky = cv::Mat::zeros(src.size(), CV_8U);
    cv::Mat maskElse = cv::Mat::zeros(src.size(), CV_8U);

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

    KMeansRes res;
    src.copyTo(res.r1, maskAsphalt);
    src.copyTo(res.r2, maskSky);
    src.copyTo(res.r3, maskElse);

    return res;
}
/*
    Thresholding Method ---- TASK 2
 */
KMeansRes thresholdMethod(cv::Mat &src)
{
    cv::Mat mask1 = (src <= 140); // best th value for asphalt
    cv::Mat mask2 = (src >= 60);  //
    cv::Mat maskAsphalt;
    cv::bitwise_and(mask1, mask2, maskAsphalt);
    cv::Mat maskSky = (src >= 160);              // best th for sky
    cv::Mat maskRest = ~(maskAsphalt | maskSky); // bitwise OR between masks, then bitwise NOT of resulting mask

    KMeansRes res;
    src.copyTo(res.r1, maskAsphalt);
    src.copyTo(res.r3, maskSky);
    src.copyTo(res.r2, maskRest);

    return res;
}
