#include <opencv2/opencv.hpp>
#include <vector>
using namespace cv;
using namespace std;

int main(){
    Mat img = imread("./images/lane.png", 0); 
    Mat dst;
    
    imshow("Output", img);
    GaussianBlur(img, dst, Size(7, 7), 1.0, 1.0);
    imshow("1.0", dst);
    GaussianBlur(img, dst, Size(7, 7), 2.0, 2.0);
    imshow("2.0", dst);
    GaussianBlur(img, dst, Size(7, 7), 3.0, 3.0); 
    imshow("3.0", dst);
    GaussianBlur(img, dst, Size(7, 7), 4.0, 4.0); 
    imshow("4.0", dst);
    
    waitKey(0);
}