#include <opencv2/opencv.hpp>
#include <vector>
using namespace cv;
using namespace std;

void print_Gaussian(double size, double sigma) 
{
    Mat kernel = getGaussianKernel(size, sigma);
    int row = kernel.rows;
    int col = kernel.cols;
    for (int i = 0; i < row; i++){
        double *row_ptr = kernel.ptr<double>(i); 
            for (int j = 0; j < col; j++)
                cout << row_ptr[j] << "  ";
        cout << endl;
    } 
}

int main()
{
   print_Gaussian(7, 1.0);
   print_Gaussian(7, 2.0);
   print_Gaussian(7, 3.0);
}

/* OutPut:
0.00443305
0.0540056
0.242036
0.39905
0.242036
0.0540056
0.00443305
0.0701593
0.131075
0.190713
0.216106
0.190713
0.131075
0.0701593
0.106289
0.140321
0.16577
0.17524
0.16577
0.140321
0.106289
*/