// Convert From Grayscale Image To Binaryscale Image.
// Grayscale:    8bit (0 ~ 255) 
// Binaryscale:  2bi  (0, 1)
// Date: 22nd August 2018
// Edited By Stephen Lee

#include <string>
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

int main()
{
    Mat img = imread("./img0.png",0);//loading gray scale image
    //Mat img = imread("./mice.png",0);//loading gray scale image
    threshold(img, img, 128, 255, CV_THRESH_BINARY);//threshold binary, you can change threshold 128 to your convenient threshold
    imwrite("./black-white0.png",img);
    //imwrite("./mice_black_white.png",img);
    return 0;
}
