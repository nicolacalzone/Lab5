#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include "methods.h"

int main(int argc, char **argv)
{
    cv::Mat src;

    std::string str1 = "../robocup.jpg";
    src = cv::imread(str1, cv::IMREAD_COLOR);

    if (src.empty() || !src.data)
    {
        std::cout << "Cannot read image " << src << std::endl;
        return -1;
    }

    cv::Mat blurImg;
    cv::GaussianBlur(src, blurImg, cv::Size(5, 5), 0);

    int numClusters = 6;
    cv::Mat res = kmeansMethod3(numClusters, blurImg);

    // if clusters are 5, the ball goes together with the shirts
    // if clusters are 4, ball goes together with shirts but shirts go together with arms / other parts
    // if clusters are 3, the ball gets halfly lost in the ground

    cv::namedWindow("Result", cv::WINDOW_KEEPRATIO);
    cv::imshow("Result", res);
    cv::waitKey(0);

    // TAKE ONLY THE SHIRTS:
    cv::Scalar low = cv::Scalar(5, 80, 100); // BGR
    cv::Scalar high = cv::Scalar(80, 200, 250);
    cv::inRange(res, low, high, res);
    cv::namedWindow("Result", cv::WINDOW_KEEPRATIO);
    cv::imshow("Result", res);
    cv::waitKey(0);

    // Better doing inRange because you never know where is a cluster stored in the labels... It might be in
    // a certain label once and in another the next time. So this is the only way

    return 0;
}

/*
    KMEANS METHOD

    @param
    k       => number of clusters
    src     => blurred image in the task3

    @result
    output  => Mat image converted to CV_8U

 */
cv::Mat kmeansMethod3(int k, cv::Mat &src)
{
    std::vector<int> labels;
    cv::Mat1f centers;
    int attempts = 5;
    cv::TermCriteria criteria = cv::TermCriteria(cv::TermCriteria::EPS + cv::TermCriteria::COUNT, 10, 1.);

    cv::Mat input = src.reshape(1, src.rows * src.cols);
    input.convertTo(input, CV_32F);

    cv::kmeans(input, k, labels, criteria, attempts, cv::KMEANS_PP_CENTERS, centers);

    for (unsigned int i = 0; i < src.rows * src.cols; i++)
    {
        input.at<float>(i, 0) = centers(labels[i], 0);
        input.at<float>(i, 1) = centers(labels[i], 1);
        input.at<float>(i, 2) = centers(labels[i], 2);
    }

    cv::Mat output = input.reshape(3, src.rows);
    output.convertTo(output, CV_8U);
    return output;
}