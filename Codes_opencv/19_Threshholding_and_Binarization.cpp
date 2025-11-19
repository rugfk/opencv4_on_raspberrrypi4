#include <opencv2/opencv.hpp>
#include <vector>
using namespace cv;
using namespace std;

void thresh_test(const char *name){
Mat img = imread(name, IMREAD_GRAYSCALE); 
Mat dst;
imshow("org", img);
threshold(img, dst, 100, 255, THRESH_BINARY); 
imshow("BINARY", dst);
threshold(img, dst, 100, 255, THRESH_BINARY_INV); 
imshow("INV", dst);
threshold(img, dst, 100, 255, THRESH_TRUNC); 
imshow("TRUNC", dst);
threshold(img, dst, 100, 255, THRESH_TOZERO); 
imshow("TOZERO", dst);

waitKey(0);
}

int main()
{
    thresh_test("./images/lenna_gray.tif");
}