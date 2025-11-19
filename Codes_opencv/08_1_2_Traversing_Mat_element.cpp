#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main(){
    Mat M = imread("./images/Fig06_lenna.tif",0);
    int num_cols = M.cols;
    int num_rows = M.rows * M.channels();
    if (M.isContinuous( )) {
        num_cols = num_cols * num_rows;
        num_rows = 1; }
    int dark_cnt = 0;;
    for(int i = 0; i < num_rows; i++) {
        uchar *row_ptr = M.ptr<uchar>(i);
        for (int j = 0; j < num_cols; j++)
            dark_cnt += (row_ptr[j] < 50)? 1: 0;
    }
    cout << dark_cnt << " Dark pixels" << endl;
}

// Output:
// 100920 Dark pixels