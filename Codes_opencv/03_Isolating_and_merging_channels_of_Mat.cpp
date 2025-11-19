#include <opencv2/opencv.hpp>
#include <vector>
using namespace cv;
using namespace std;
int main(){
    const char* name = "./images/Fig06_lenna.tif";
    Mat img = imread(name, IMREAD_COLOR);
    resize(img, img, Size(200, 200.0 * img.rows / img.cols));
    imshow("org", img);
    vector<Mat> channel;
    split(img, channel);
    char wname[10];
    for (int i = 0; i < img.channels(); i++) {
        sprintf(wname, "ch%d", i);
        imshow(wname, channel[i]); }
    Mat merged;
    channel[0] = channel[0]/2;
    channel[1] = channel[1]/2;
    merge(channel, merged);
    imshow("mrg", merged);
    
    waitKey(0);
    return 0;
}