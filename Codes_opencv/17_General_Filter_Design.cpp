#include <opencv2/opencv.hpp>
#include <vector>
using namespace cv;
using namespace std; 

int main(){
    const int KSIZE = 3;
    Mat img = imread("./images/lenna_gray.tif", 0);
    imshow("Input", img); 
    Mat dst;
    Mat kernel(KSIZE, KSIZE, CV_32F);

    kernel = (Mat_<float>(3, 3) << 1.0, 2.0, 1.0, 2.0, 4.0, 2.0, 1.0, 2.0, 1.0);
    kernel = kernel / 16.0;

    cout << kernel;
    filter2D(img, dst, -1, kernel); 
    imshow("Filter output", dst);

    waitKey(0); 
}

/* Output:
[0.0625, 0.125, 0.0625;
 0.125, 0.25, 0.125;
 0.0625, 0.125, 0.0625]
*/