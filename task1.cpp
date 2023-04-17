#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

enum condition
{
    crack,
    noncrack
};

Mat regionGrowingMethod(Mat morphImg, Mat blurImg);
Mat watershedMethod(Mat wsImg, Mat blurImg);
Mat clusteringMethod(Mat clustImg, Mat blurImg);

int main(int argc, char **argv)
{

    Mat src1, src2, src3;
    Mat src1_gray, src2_gray, src3_gray;

    string str1 = "../Asphalt-1.png";
    string str2 = "../Asphalt-2.png";
    string str3 = "../Asphalt-3.png";
    vector<string> strings = {str1, str2, str3};

    for (string s : strings)
    {
        src1 = imread(s, IMREAD_COLOR);
        if (src1.empty())
        {
            cout << "Cannot read image " << s << endl;
            return -1;
        }

        cvtColor(src1, src1_gray, COLOR_BGR2GRAY);

        Mat blurImg;
        GaussianBlur(src1_gray, blurImg, Size(7, 7), 7);

        // METODO 1 ---- REGION GROWING
        Mat morphImg;
        morphImg = regionGrowingMethod(morphImg, blurImg);

        // METODO 2 ---- WATERSHED

        imshow("res Regions", morphImg);
        waitKey(0);
    }

    return 0;
}

Mat regionGrowingMethod(Mat morphImg, Mat blurImg)
{
    Mat thImg;
    threshold(blurImg, thImg, 40, 255, THRESH_BINARY); // the closest to black is the minTrhreshold,
                                                       // the better the result
    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
    morphologyEx(thImg, morphImg, MORPH_DILATE, kernel); // change the MORPH value and the pic changes!

    return morphImg;
}

Mat watershedMethod(Mat wsImg, Mat blurImg)
{
}
Mat clusteringMethod(Mat clustImg, Mat blurImg)
{
}
