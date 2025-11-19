#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main(){
    Mat M = imread("./images/Fig06_lenna.tif",0);
    int num_cols = M.cols;
    int num_rows = M.rows * M.channels();
    int dark_cnt = 0;
    if( M.isContinuous()) {
        uchar *p = M.data;
        for(int i = 0; i < num_rows * num_cols; i++)
            dark_cnt += (*p++ < 50)?1:0; } else {
                for(int i = 0; i < num_rows; i++) { uchar *row_ptr = M.ptr<uchar>(i);
                    for (int j = 0; j < num_cols; j++)
                    dark_cnt += (row_ptr[j] < 50)? 1: 0; }
            }
    cout << dark_cnt << " Dark pixels" << endl;
}

// Output:
// 100920 Dark pixels