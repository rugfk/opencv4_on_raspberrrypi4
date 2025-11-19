#include <opencv2/opencv.hpp>
#include <vector>
using namespace cv;
using namespace std;

 
void show_hist(Mat &img, const char *wname)
{ 
    Mat hist;
    float range[] = {0, 255};
    const float *histRange = {range};
    const int histSize[] = {256};
    bool uniform = true, accum = false;
    const int channels[] = {0};
    calcHist(&img, 1, channels, Mat(), hist, 1, histSize, &histRange, uniform, accum);
    double maxVal = 0;
    minMaxLoc(hist, 0, &maxVal, 0, 0);
    int scale = 2;
    Mat histImg = Mat::zeros(256 * scale, 256 * scale, CV_8UC3);
    for (int v=0;v<256;v++){
        float binVal = hist.at<float>(v);
        int num = cvRound(binVal * 255.0/maxVal);
        rectangle(histImg, Point(v*scale, num*scale), Point((v+1)*scale-1, 0), Scalar(0, 0, 100), CV_FILLED);
    }
    flip(histImg, histImg, 0); imshow(wname, histImg);
}

void histogram_Test(const char *name)
{
    Mat img = imread(name,0); 
    Mat dst;
    imshow("org", img); 
    show_hist(img, "input hist");
    equalizeHist(img, dst);
    show_hist(dst, "dst hist"); 
    imshow("eqlaized", dst);
    
    waitKey(0); 
}

int main() 
{
    //histogram_Test("./images/Fig03_pollen2.tif");
    histogram_Test("./images/Fig02_EinStein.tif"); 
}