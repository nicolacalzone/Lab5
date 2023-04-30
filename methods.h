#ifndef METHODS_H
#define METHODS_H

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "utils.h"

// ------------------------------ TASK 1 ------------------------------
Result regionGrowingMethod(cv::Mat &morphImg, cv::Mat &blurImg, int minTh, int maxTh, Method m);

// ------------------------------ TASK 2 ------------------------------
KMeansRes kmeansMethod2(int k, cv::Mat &src);
KMeansRes thresholdMethod(cv::Mat &src);

// ------------------------------ TASK 3 ------------------------------
cv::Mat kmeansMethod3(int k, cv::Mat &src);

#endif