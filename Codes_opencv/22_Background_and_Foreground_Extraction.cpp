#include <opencv2/opencv.hpp>
#include <vector>
using namespace cv;
using namespace std;

int main(){
    VideoCapture cap("./images/surveillance.avi");
    Mat frame, fgMOG2;
    Ptr<BackgroundSubtractorMOG2> pMOG2;
    pMOG2 = createBackgroundSubtractorMOG2(30, 20.0, true);

    while(1){
    cap >> frame;
    if(frame.empty())
        break;
    pMOG2->apply(frame, fgMOG2, 0.1);
    //get the frame number and write it on the current frame imshow("Frame", frame);
    imshow("FG MOG2", fgMOG2);
    }
}