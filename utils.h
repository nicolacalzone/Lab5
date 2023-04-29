#ifndef UTILS_H
#define UTILS_H

#include <opencv2/core.hpp>

enum Method
{
    THRESH_Method,
    INRANGE_Method
};

struct Result
{
    cv::Mat morph;
    cv::Mat kernel;
};

#endif