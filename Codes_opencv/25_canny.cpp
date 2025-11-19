#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main(){
    Mat img = imread("./images/Fig04_house.tif", 0);
    Mat dst;
    Canny(img, dst, 80, 200, 3, false);
    imshow("Canny", dst);
    
    waitKey(0);
}