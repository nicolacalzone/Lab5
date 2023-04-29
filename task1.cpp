#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include "utils.h"   // definies struct to save Results and enum for methods to apply
#include "methods.h" // defines all the functions for the Lab5

int main(int argc, char **argv)
{
    cv::Mat src;
    cv::Mat srcGray;
    cv::Mat blurImg;

    std::vector<std::string> strings = {"../Asphalt-1.png", "../Asphalt-2.png", "../Asphalt-3.png"};

    for (std::string s : strings)
    {
        src = cv::imread(s, cv::IMREAD_COLOR);

        if (src.empty() || !src.data)
        {
            std::cout << "Cannot read image " << s << std::endl;
            return -1;
        }

        cv::cvtColor(src, srcGray, cv::COLOR_BGR2GRAY);

        if (s == strings[0])
        {
            cv::GaussianBlur(srcGray, blurImg, cv::Size(3, 3), 0);

            // METODO 1 ---- REGION GROWING
            Result resGrowing;
            int minThr = 70;
            int maxThr = 255;
            resGrowing = regionGrowingMethod(resGrowing.morph, blurImg, minThr, maxThr, THRESH_Method);

            // erode(resGrowing.morph, resGrowing.morph, resGrowing.kernel, Point(-1, 1), 2);

            cv::namedWindow("res Regions", cv::WINDOW_KEEPRATIO);
            cv::imshow("res Regions", resGrowing.morph);

            resGrowing.morph.release();
            resGrowing.kernel.release();
            blurImg.release();
        }
        else if (s == strings[1])
        {

            cv::medianBlur(srcGray, blurImg, 5);

            // METODO 1 ---- REGION GROWING
            Result resGrowing;
            int minThr = 65;
            int maxThr = 255;

            resGrowing = regionGrowingMethod(resGrowing.morph, blurImg, minThr, maxThr, THRESH_Method);

            // cv::erode(resGrowing.morph, resGrowing.morph, resGrowing.kernel, cv::Point(-1, 1), 1);

            cv::namedWindow("res Regions", cv::WINDOW_KEEPRATIO);
            cv::imshow("res Regions", resGrowing.morph);

            resGrowing.morph.release();
            resGrowing.kernel.release();
            blurImg.release();
        }

        else if (s == strings[2])
        {
            cv::GaussianBlur(srcGray, blurImg, cv::Size(5, 5), 0);

            // METODO 1 ---- REGION GROWING
            Result resGrowing;
            int minThr = 50;
            int maxThr = 150;
            resGrowing = regionGrowingMethod(resGrowing.morph, blurImg, minThr, maxThr, INRANGE_Method); // best minTH around 45

            // erode(resGrowing.morph, resGrowing.morph, resGrowing.kernel, Point(-1, 1), 2);

            cv::namedWindow("res Regions", cv::WINDOW_KEEPRATIO);
            cv::imshow("res Regions", resGrowing.morph);

            resGrowing.morph.release();
            resGrowing.kernel.release();
            blurImg.release();
        }

        cv::waitKey(0);
    }

    return 0;
}
