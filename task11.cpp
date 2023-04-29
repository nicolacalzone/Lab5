#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char **argv)
{

    Mat src1, src2, src3;
    Mat src1_gray, src2_gray, src3_gray;

    string str1 = "../Asphalt-1.png";
    string str2 = "../Asphalt-2.png";
    string str3 = "../Asphalt-3.png";
    vector<string> strings = {str1, str2, str3};

    src1 = imread(str1, IMREAD_COLOR);
    src2 = imread(str2, IMREAD_COLOR);
    src3 = imread(str3, IMREAD_COLOR);
    if (src1.empty() || src2.empty() || src3.empty())
    {
        cout << "Cannot read one of the images " << endl;
        return -1;
    }

    cvtColor(src1, src1_gray, COLOR_BGR2GRAY);
    cvtColor(src2, src2_gray, COLOR_BGR2GRAY);
    cvtColor(src3, src3_gray, COLOR_BGR2GRAY);

    Mat blur1Img, blur2Img, blur3Img;
    GaussianBlur(src1_gray, blur1Img, Size(5, 5), 0);
    GaussianBlur(src2_gray, blur2Img, Size(5, 5), 0);
    GaussianBlur(src3_gray, blur3Img, Size(5, 5), 0);

    // METODO 1 ---- REGION GROWING
    Mat morphImg1, morphImg2, morphImg3;

    Mat thImg1, thImg2, thImg3;
    threshold(blur1Img, thImg1, 50, 255, THRESH_BINARY); // the closest to black is the minTrhreshold,
                                                         // the better the result
    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
    morphologyEx(thImg1, morphImg1, MORPH_CLOSE, kernel); // change the MORPH value and the pic changes!

    threshold(blur2Img, thImg2, 60, 255, THRESH_BINARY);
    Mat kernel1 = getStructuringElement(MORPH_RECT, Size(3, 3));
    morphologyEx(thImg2, morphImg2, MORPH_CLOSE, kernel);

    threshold(blur3Img, thImg3, 50, 255, THRESH_BINARY);
    Mat kernel2 = getStructuringElement(MORPH_RECT, Size(3, 3));
    morphologyEx(thImg3, morphImg3, MORPH_CLOSE, kernel);

    namedWindow("1", WINDOW_KEEPRATIO);
    imshow("1", morphImg1);

    namedWindow("2", WINDOW_KEEPRATIO);
    imshow("2", morphImg2);

    namedWindow("3", WINDOW_KEEPRATIO);
    imshow("3", morphImg3);

    waitKey(0);
    return 0;
}
