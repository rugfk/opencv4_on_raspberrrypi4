// Failed on Ubuntu

#include <opencv2/opencv.hpp>
#include <vector>
using namespace cv;
using namespace std;

int main(){
    Mat M = imread("./images/Fig06_lenna.tif", 0);
    
    int zero_cntB = 0;
    int zero_cntG = 0;
    int zero_cntR = 0;

    Mat_<Vec3b> Mv3 = M;

    for( int i = 0; i < M.rows; ++i)
        for( int j = 0; j < M.cols; ++j ) {
            zero_cntB += Mv3.at(i,j)[0] < 50?1:0;
            zero_cntG += Mv3.at(i,j)[1] < 50?1:0;
            zero_cntR += Mv3.at(i,j)[2] < 50?1:0;
        }
        cout << "Blue=" <<zero_cntB << " Green= " << zero_cntG << " Red= " << zero_cntR; /* << end; */
}

// Output:
// Blue=101356 Green= 101357 Red= 101359