#include <opencv2/opencv.hpp>
#include <vector>
using namespace cv;
using namespace std;

void sharpening(const char *name)
{ 
    Mat img = imread(name, 0); 
    Mat blurred, dst;
    blur(img, blurred, Size(7, 7)); 
    addWeighted(img, 2.0, blurred, -1.0, 0.0, dst); 
    imshow("org", img);
    imshow("blurred", blurred);
    imshow("shapen", dst);
    waitKey(0);
}

int main() 
{
    sharpening("./images/Fig03_dipxe.tif"); 
}