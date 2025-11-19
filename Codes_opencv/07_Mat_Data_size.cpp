#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main(){
    cv::Mat M (10, 15, CV_8UC3);
    int imagesize = M.cols * M.rows * M.channels() * M.elemSize1(); 
    std::cout << "total size =" << imagesize << " bits" << std::endl;
    
    waitKey(0);
    return(0);
}

// Output: 
// total size =450 bits