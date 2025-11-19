#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
//#include <iostream>
using namespace cv;
using namespace std;

void test(const char *name){
    Mat pic = imread(name, IMREAD_GRAYSCALE);  // read an image file from disk
    imshow("Hello OpenCV", pic);
    waitKey(0);
}

int main(){
    // Put the path.
    test("./images/Fig06_lenna.tif");   
}