#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main(){
    Mat dst;
    Mat img = imread("./images/Fig06_lenna.tif", IMREAD_GRAYSCALE);
    imshow("input", img);

    Mat gaussian_noise = img.clone(); //alloc space
    randn(gaussian_noise, 0,20); // makes noise
    dst = img + gaussian_noise; // inserts noise
    imshow("Noisy", dst);
    
    //Mat dst;
    Canny(dst, dst, 70, 180); // detect edges
    imshow("Noisy Canny", dst);
    waitKey(0);
    return 0;
}