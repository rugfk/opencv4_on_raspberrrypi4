#include <opencv2/opencv.hpp>
#include <vector>
using namespace cv;
using namespace std;

int main()
{
    Mat src = imread("./images/Fig09_noisyFingerprint.tif");
    Mat dst;
    int n = 3;
    int element_shape = MORPH_RECT;
    Mat element = getStructuringElement(element_shape, Size(n, n));
    double thresh = 100, maxval = 255;
    int threshType = THRESH_BINARY;
    threshold(src, dst, thresh, maxval, threshType);
        imshow("Original", dst);
        imshow("Threshold", dst);
    Mat resOpen, resClose;
    morphologyEx(dst, resOpen, CV_MOP_OPEN, element); 
        imshow("Opening", dst);
    morphologyEx(dst, resClose, CV_MOP_CLOSE, element);
        imshow("Closing", dst);

    waitKey(0);
} 