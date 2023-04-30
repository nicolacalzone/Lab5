#ifndef UTILS_H
#define UTILS_H

#include <opencv2/core.hpp>

enum Method
{
    THRESH_Method = 0,
    INRANGE_Method = 1,
};

struct Result
{
    cv::Mat morph;
    cv::Mat kernel;
};

struct KMeansRes
{
    cv::Mat r1;
    cv::Mat r2;
    cv::Mat r3;
};

#endif