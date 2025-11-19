#include <opencv2/opencv.hpp>
#include <vector>
using namespace cv;
using namespace std;

int main()
{
    Mat src = imread("./images/Fig09_text_image.tif");
    Mat dst;
    int n = 3;
    int element_shape = MORPH_RECT;
    Mat element = getStructuringElement(element_shape, Size(n, n));

    double thresh = 100, maxval = 255;
    int threshType = THRESH_BINARY;
    Mat resDilate, resErode;

    threshold(src, dst, thresh, maxval, threshType);
    imshow("Threshold", dst);
    dilate(dst, resDilate, element, Point(-1, -1), 3);
    imshow("Dilate", dst);
    erode(dst, resErode, element, Point(-1, -1), 3);
    imshow("Erode", dst);

    waitKey(0);
} 