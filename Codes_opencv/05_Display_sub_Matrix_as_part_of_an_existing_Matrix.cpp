#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main(){
    Mat img = imread("./images/Fig06_lenna.tif", IMREAD_COLOR);
    Mat sub1(img, Rect(30, 60, 200, 400));
    Mat sub2(img, Rect(Point(230, 60), Point(430,460)));
    
    sub1 = Scalar(0, 255, 0); // sub1 Green
    sub2 = Scalar(255, 255, 255); // sub2White
    
    imshow("sub", sub1);
    imshow("sub2", sub2);
    imshow("org+sub", img);
    
    waitKey(0);
    return 0;
}