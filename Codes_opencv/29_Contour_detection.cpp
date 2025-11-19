#include <opencv2/opencv.hpp>
#include <vector>

using namespace cv;
using namespace std;

int main(){
    //edge extraction
    //find contours
    Mat src = imread("./images/Tangram/bird.png"); 
    imshow("input", src);
    Mat gray;
    cvtColor(src, gray, CV_BGR2GRAY);

    //edge extraction
    Mat canny;
    Canny(gray, canny, 10, 30);
    dilate(canny, canny, Mat(), Point(-1, -1), 1);

    //find contours
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    findContours(canny, contours, CV_RETR_TREE, CV_CHAIN_APPROX_NONE);
    Mat result = src.clone();
    for (size_t i = 0; i < contours.size(); i++)
    drawContours(src, contours, i, Scalar(0, 0, 0), 2);
    imshow("src", src);
    imshow("gray", gray);
    imshow("Canny", canny);
    imshow("result", result);
    waitKey(0);
    return 0;
}