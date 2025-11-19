#include <opencv2/opencv.hpp>
//#include <vector>
using namespace cv;
using namespace std;

int main(){
    const char* name = "./images/Fig06_color_bars.tif";
    Mat img = imread(name, IMREAD_COLOR);
    if(img.empty())
    //return;
    
    resize(img, img, Size(300, 300.0 * img.rows/img.cols));
    imshow("org", img);
    Mat M1(img); // share the whole image area
    Mat M2, M3, M4;
    
    M2 = img;
    M3 = img.clone();
    img.copyTo(M4);
    M2 = Scalar(200, 100, 100);
    M3 = Scalar(0, 0, 255);
    M4 = Scalar(0, 255, 0);
    
    imshow("M1", M1);
    imshow("M2", M2);
    imshow("M3", M3);
    imshow("M4", M4);
    waitKey(0);
    return(0);
}