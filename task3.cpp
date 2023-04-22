#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat kmeansMethod(int k, Mat src)
{
    vector<int> labels;
    Mat1f colors;
    int attempts = 5;
    TermCriteria criteria = TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 10, 1.);

    Mat input = src.reshape(1, src.rows * src.cols);
    input.convertTo(input, CV_32F);

    kmeans(input, k, labels, criteria, attempts, KMEANS_PP_CENTERS, colors);

    for (unsigned int i = 0; i < src.rows * src.cols; i++)
    {
        input.at<float>(i, 0) = colors(labels[i], 0);
        input.at<float>(i, 1) = colors(labels[i], 1);
        input.at<float>(i, 2) = colors(labels[i], 2);
    }

    Mat output = input.reshape(3, src.rows);
    output.convertTo(output, CV_8U);
    return output;
}

int main(int argc, char **argv)
{

    Mat src, src_gray;

    string str1 = "../robocup.jpg";
    src = imread(str1, IMREAD_COLOR);
    if (src.empty())
    {
        cout << "Cannot read image " << src << endl;
        return -1;
    }

    Mat blurImg;
    GaussianBlur(src, blurImg, Size(5, 5), 0);

    Mat res = kmeansMethod(6, blurImg);

    // if clusters are 5, the ball goes together with the shirts
    // if clusters are 4, ball goes together with shirts but shirts go together with arms / other parts
    // if clusters are 3, the ball gets halfly lost in the ground

    namedWindow("Result", WINDOW_KEEPRATIO);
    imshow("Result", res);
    waitKey(0);

    // TAKE ONLY THE SHIRTS:
    Scalar low = Scalar(5, 80, 100); // BGR
    Scalar high = Scalar(80, 200, 250);
    inRange(res, low, high, res);
    namedWindow("Result", WINDOW_KEEPRATIO);
    imshow("Result", res);
    waitKey(0);

    // Better doing inRange because you never know where is a cluster stored in the labels... It might be in
    // a certain label once and in another the next time. So this is the only way

    return 0;
}