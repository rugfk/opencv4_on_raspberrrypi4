#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main(){
    Mat img = imread("./images/Fig06_lenna.tif", IMREAD_COLOR);
    Mat dst, dst2, dst3;
    
    cvtColor(img, dst, COLOR_BGR2GRAY);
    cvtColor(img, dst2, COLOR_BGR2HSV);
    cvtColor(img, dst3, COLOR_BGR2YUV);
    
    imshow("img", img);
    imshow("GRAY", dst);
    imshow("HSV", dst2);
    imshow("YUV", dst3);

    waitKey(0);
    return 0;
}