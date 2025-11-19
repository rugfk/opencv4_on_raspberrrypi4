#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main(){
    Mat dst;
    Mat img = imread("./images/Fig06_lenna.tif", IMREAD_GRAYSCALE);
    imshow("input", img);

    Laplacian(img, dst, CV_16S, 3);
    convertScaleAbs(dst, dst);
    imshow("Laplacian", dst);
    
    waitKey(0);
    return 0;
}