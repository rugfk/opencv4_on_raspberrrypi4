#include <opencv2/opencv.hpp>
#include <vector>
using namespace cv;
using namespace std;

int main(){
    Mat M = imread("./images/Fig06_lenna.tif", 0);
    
    int zero_cntB = 0;
    int zero_cntG = 0;
    int zero_cntR = 0;
    for( int i = 0; i < M.rows; ++i)
        for( int j = 0; j < M.cols; ++j ) {
            zero_cntB += M.at<Vec3b>(i,j)[0] < 50?1:0;
            zero_cntG += M.at<Vec3b>(i,j)[1] < 50?1:0;
            zero_cntR += M.at<Vec3b>(i,j)[2] < 50?1:0;
        }
        cout << "Blue=" <<zero_cntB << " Green= " << zero_cntG << " Red= " << zero_cntR; /* << end; */
}

// Output:
// Blue=101356 Green= 101357 Red= 101359