#include <opencv2/opencv.hpp>
#include <vector>

using namespace cv;
using namespace std;

int main(){
    Mat img = imread("./images/line.tif", IMREAD_COLOR);
    imshow("input", img);
    Mat src = img;

    //edge extraction
    Mat edge;
    Canny(src, edge, 80, 200,3);
    
    //Hough Transform
    vector<Vec4i> lines;
    HoughLinesP(edge, lines, 1, CV_PI / 180, 50, 10, 10);
    
    //draw lines
    for (size_t i = 0; i < lines.size(); i++)
    line(img, Point(lines[i][0], lines[i][1]),Point(lines[i][2], lines[i][3]), Scalar(0, 0, 255), 1);
    imshow("Lines", img);

    waitKey(0);
    return 0;
}