#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

Mat get_HorizDerivKernel() {
    Mat kernel = (Mat_<float>(3, 3) << -1, 0, 1, -1, 0, 1, -1, 0, 1);
    kernel = kernel/3.0;
    return kernel;
}

Mat get_VertDerivKernel() {
    Mat kernel = (Mat_<float>(3, 3) << -1, -1, -1, 0, 0, 0, 1, 1, 1);
    kernel = kernel / 3.0;
    return kernel;
}

int main(){
    Mat img = imread("./images/Fig04_house.tif", 0);
    
    Mat horiz_kernel = get_HorizDerivKernel();
    Mat vert_kernel = get_VertDerivKernel();
    Mat deriv_X, deriv_Y;
    std::cout << horiz_kernel << std::endl;
    std::cout << vert_kernel << std::endl;
    filter2D(img, deriv_X, CV_16S, horiz_kernel);
    filter2D(img, deriv_Y, CV_16S, vert_kernel);
    
    // sobel
    Sobel(img, deriv_X, CV_16S, 1,0);
    Sobel(img, deriv_Y, CV_16S, 0,1);
    convertScaleAbs(deriv_X, deriv_X); // 16S -> 8U
    convertScaleAbs(deriv_Y, deriv_Y); // 16S -> 8U
    imshow("detivatives X", deriv_X);
    imshow("derivatives Y", deriv_Y);
    /*
    convertScaleAbs(deriv_X, deriv_X); // 16S -> 8U
    convertScaleAbs(deriv_Y, deriv_Y); // 16S -> 8U
    imshow("Horiz_Derivative", deriv_X);
    imshow("Vertical_Derivative", deriv_Y);
    */
    waitKey(0);
}

/* Output:
2 images,

[-0.33333334, 0, 0.33333334;
 -0.33333334, 0, 0.33333334;
 -0.33333334, 0, 0.33333334]
[-0.33333334, -0.33333334, -0.33333334;
 0, 0, 0;
 0.33333334, 0.33333334, 0.33333334]
*/