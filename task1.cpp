#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

struct Result
{
    Mat morph;
    Mat kernel;
};

Result regionGrowingMethod(Mat morphImg, Mat blurImg, int minTh);
Mat watershedMethod(Mat wsImg, Mat blurImg);
Mat clusteringMethod(Mat clustImg, Mat blurImg);

int main(int argc, char **argv)
{

    Mat src1;
    Mat srcGray;
    Mat blurImg;

    string str1 = "../Asphalt-1.png";
    string str2 = "../Asphalt-2.png";
    string str3 = "../Asphalt-3.png"; // this picture needs more iterations of gaussian blur filter
    vector<string> strings = {str1, str2, str3};

    for (string s : strings)
    {
        src1 = imread(s, IMREAD_COLOR);
        if (src1.empty())
        {
            cout << "Cannot read image " << s << endl;
            return -1;
        }

        cvtColor(src1, srcGray, COLOR_BGR2GRAY);

        if (s == str1)
        {
            GaussianBlur(srcGray, blurImg, Size(5, 5), 0);

            // METODO 1 ---- REGION GROWING
            Result resGrowing;
            resGrowing = regionGrowingMethod(resGrowing.morph, blurImg, 100);
            namedWindow("res Regions", WINDOW_KEEPRATIO);
            imshow("res Regions", resGrowing.morph);
            resGrowing.morph.release();
        }
        else if (s == str2)
        {

            // GaussianBlur(srcGray, blurImg, Size(3, 3), 0);
            medianBlur(srcGray,
                       blurImg,
                       3);

            // GaussianBlur(blurImg, blurImg, Size(3, 3), 0);

            // METODO 1 ---- REGION GROWING
            Result resGrowing;
            resGrowing = regionGrowingMethod(resGrowing.morph, blurImg, 90);
            namedWindow("res Regions", WINDOW_KEEPRATIO);

            dilate(resGrowing.morph, resGrowing.morph, resGrowing.kernel, Point(-1, 1), 1);

            imshow("res Regions", resGrowing.morph);
            resGrowing.morph.release();
        }
        else if (s == str3)
        {
            GaussianBlur(srcGray, blurImg, Size(3, 3), 0);

            // METODO 1 ---- REGION GROWING
            Result resGrowing;
            resGrowing = regionGrowingMethod(resGrowing.morph, blurImg, 60);
            namedWindow("res Regions", WINDOW_KEEPRATIO);
            imshow("res Regions", resGrowing.morph);
            resGrowing.morph.release();
        }

        waitKey(0);
    }

    return 0;
}

Result regionGrowingMethod(Mat morphImg, Mat blurImg, int minTh)
{
    Result res;
    Mat thImg;
    threshold(blurImg, thImg, minTh, 255, THRESH_BINARY); // the closest to black is the minTrhreshold,
                                                          // the better the result
    Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));
    morphologyEx(thImg, morphImg, MORPH_CLOSE, kernel); // change the MORPH value and the pic changes!

    res.morph = morphImg.clone();
    res.kernel = kernel.clone();

    return res;
}

Mat watershedMethod(Mat wsImg, Mat blurImg)
{
}
Mat clusteringMethod(Mat clustImg, Mat blurImg)
{
}
