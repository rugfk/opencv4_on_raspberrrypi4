#include <opencv2/opencv.hpp>
#include <vector>
using namespace cv;
using namespace std;

Mat computeHistogram(Mat & input_img)
{   // bin_size=256, range={0,255}, dim=1
    Mat hist = Mat::zeros(256,1, CV_32S); 
    for(int i=0;i<input_img.rows;i++)
       for(int j=0;j<input_img.cols;j++){
           int binIdx = (int) input_img.at<uchar>(i,j);
           hist.at<int>(binIdx,0) += 1;
        }
return hist;
}

int main() 
{
    Mat input = imread("./images/Fig06_lenna.tif"); 
    Mat hist = computeHistogram(input);
    for(int i=0;i<hist.rows;i++)
        cout << i << " : " << hist.at<int>(i,0) << endl;
}

// Output:
/* 
0 : 43673
1 : 11372
2 : 10480
3 : 8584
.
.
.
250 : 39
251 : 41
252 : 23
253 : 31
254 : 24
255 : 405
*/