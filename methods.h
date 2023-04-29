#ifndef METHODS_H
#define METHODS_H

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "utils.h"

using namespace cv;
using namespace std;

// ------------------------------ TASK 1 ------------------------------
/*
    REGION GROWING METHOD ---- TASK 1
 */
Result regionGrowingMethod(cv::Mat morphImg, cv::Mat blurImg, int minTh, int maxTh, Method m)
{
    Result res;
    cv::Mat thImg;

    switch (m)
    {
    case THRESH_Method:
        threshold(blurImg, thImg, minTh, maxTh, cv::THRESH_BINARY);
        break;
    case INRANGE_Method:
        inRange(blurImg, cv::Scalar(minTh), cv::Scalar(maxTh), thImg);
        break;
    }

    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(3, 3));
    morphologyEx(thImg, morphImg, cv::MORPH_CLOSE, kernel); // change the MORPH value and the pic changes! 3 == Morph_Close

    res.morph = morphImg;
    res.kernel = kernel;
    return res;
}

// ------------------------------ TASK 2 ------------------------------
/*
    KMEANS ---- TASK 2
 */
ThStruct kmeansMethod2(int k, Mat src)
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
/*
    Thresholding Method ---- TASK 2
 */
ThStruct thresholdMethod(Mat src)
{
    Mat mask1 = (src <= 140); // best th value for asphalt
    Mat mask2 = (src >= 60);  //
    Mat maskAsphalt;
    bitwise_and(mask1, mask2, maskAsphalt);
    Mat maskSky = (src >= 160);              // best th for sky
    Mat maskRest = ~(maskAsphalt | maskSky); // bitwise OR between masks, then bitwise NOT of resulting mask

    ThStruct res;
    src.copyTo(res.r1, maskAsphalt);
    src.copyTo(res.r3, maskSky);
    src.copyTo(res.r2, maskRest);

    return res;
}

// ------------------------------ TASK 3 ------------------------------
/*
    KMEANS METHOD ---- TASK 3

    @param
    k       => number of clusters
    src     => blurred image in the task3

    @result
    output  => Mat image converted to CV_8U

 */
Mat kmeansMethod3(int k, Mat src)
{
    vector<int> labels;
    Mat1f centers;
    int attempts = 5;
    TermCriteria criteria = TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 10, 1.);

    Mat input = src.reshape(1, src.rows * src.cols);
    input.convertTo(input, CV_32F);

    kmeans(input, k, labels, criteria, attempts, KMEANS_PP_CENTERS, centers);

    for (unsigned int i = 0; i < src.rows * src.cols; i++)
    {
        input.at<float>(i, 0) = centers(labels[i], 0);
        input.at<float>(i, 1) = centers(labels[i], 1);
        input.at<float>(i, 2) = centers(labels[i], 2);
    }

    Mat output = input.reshape(3, src.rows);
    output.convertTo(output, CV_8U);
    return output;
}

#endif