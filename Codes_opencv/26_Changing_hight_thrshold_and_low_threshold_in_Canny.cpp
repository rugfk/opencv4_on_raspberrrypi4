#include <opencv2/opencv.hpp>
#include <vector>
using namespace cv;
using namespace std;

static Mat input_img, edge_img; 
static char win_name[] = "Canny"; 
static int lowTh, highTh;

void CannyThr(int, void*){ // Callback function
    Canny(input_img, edge_img, lowTh, highTh, 3);
    imshow(win_name, edge_img);
}

void Canny_test_thresholds(const char *name) {
    input_img = imread(name, 0);
    edge_img.create(input_img.size(), input_img.type()); 
    namedWindow(win_name, CV_WINDOW_AUTOSIZE); 
    createTrackbar("Threshold1", win_name, &lowTh,200, CannyThr); 
    createTrackbar("Threshold2", win_name, &highTh,255,CannyThr); 
    
    waitKey(0);
}

int main(){
    //Canny_test_thresholds("/home/ubuntu/Documents/03_Computer_Vision/02_eBook_Computer_Vision/07_OpenCV_SeoulIoTWorkshop/codes/images/Fig04_house.tif");
    Canny_test_thresholds("./images/Fig04_house.tif");
}