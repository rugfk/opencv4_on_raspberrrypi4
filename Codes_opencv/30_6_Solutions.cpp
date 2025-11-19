#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

Mat get_HorizDerivKernel();
Mat get_VertDerivKernel();
double getDistance(const Point& p1, const Point& p2) {

	double distance;

	// pow(x,2)= x*x,  sqrt(x) = squre root of x
	distance = sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));

	return distance;
}

int checkPoly(vector<Point>& poly, float margin)
{
	vector<float> lines;

	//calculate distances between vertices
	for (int i = 0; i < poly.size(); i++) {
		lines.push_back(getDistance(poly[i], poly[(i + 1) % poly.size()]));
	}
	sort(lines.begin(), lines.end());	//sort by ascending order

	vector<float>sideLenRatio;
	for (int i = 0; i < lines.size(); i++) {
		sideLenRatio.push_back(lines[i] / lines[0]);
	}

	if (lines.size() == 3) {
		if (((sideLenRatio[0] >= (1 - margin)) && (sideLenRatio[0] <= (1 + margin))) &&
			((sideLenRatio[1] >= (1 - margin)) && (sideLenRatio[1] <= (1 + margin))) &&
			((sideLenRatio[2] >= (1.4 - margin)) && (sideLenRatio[2] <= (1.4 + margin))))
			return 3; 	//�����ﰢ�� - 1:1:1.4
		else return -1;
	}
	else if (lines.size() == 4) {
		if (((sideLenRatio[0] >= (1 - margin)) && (sideLenRatio[0] <= (1 + margin))) &&
			((sideLenRatio[1] >= (1 - margin)) && (sideLenRatio[1] <= (1 + margin))) &&
			((sideLenRatio[2] >= (1 - margin)) && (sideLenRatio[2] <= (1 + margin))) &&
			((sideLenRatio[3] >= (1 - margin)) && (sideLenRatio[3] <= (1 + margin))))
			return 4; //���簢�� - 1:1:1:1

		else if (((sideLenRatio[0] >= (1 - margin)) && (sideLenRatio[0] <= (1 + margin))) &&
			((sideLenRatio[1] >= (1 - margin)) && (sideLenRatio[1] <= (1 + margin))) &&
			((sideLenRatio[2] >= (1.4 - margin)) && (sideLenRatio[2] <= (1.4 + margin))) &&
			((sideLenRatio[3] >= (1.4 - margin)) && (sideLenRatio[3] <= (1.4 + margin))))
			return 5; //����纯 - 1:1:1.4:1.4

		else
			return -1;
	}
	else return -1;
}

void sol_problem_6(char *name) {
	Mat img = imread(name, 1);
	if (img.empty())
		return;
	Mat canny;

	//cvtColor(img, img, COLOR_BGR2GRAY);
	Canny(img, canny, 10, 30); // use color information for edge detection
	dilate(canny, canny, Mat(), Point(-1, -1), 1);
	imshow("canny", canny);

	//find contours
	Mat edges = canny.clone();
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	findContours(edges, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);

	int size = contours.size();
	cout << size << " contours" << endl;
	char text[20];

	vector<vector<Point> > polygon_pts(size);
	vector<Scalar> color(size);
	Mat draw = img.clone();
	for (int i = 0; i < size; i++) {
		//drawContours(draw, contours, i, Scalar(70, 70, 70), 10);
		approxPolyDP(contours[i], polygon_pts[i], 20, true);
		color[i] = Scalar((rand()) % 255, (rand()) % 255, (rand()) % 255);
		polylines(draw, polygon_pts[i], true, color[i], 2);
	}

	for (int i = 0; i < size; i++) {
		RotatedRect minrect = minAreaRect(polygon_pts[i]);
		if (minrect.size.area() < 900)
			continue;
		Moments mu = moments(polygon_pts[i], false);
		Point2f center(mu.m10 / mu.m00, mu.m01 / mu.m00);
		char *type;
		switch (checkPoly(polygon_pts[i], 0.1)) {
		case 3: type = "T";
			break;
		case 4: type = "SR";
			break;
		case 5: type = "PR";
			break;
		default:
			type = "ERR";
		}
		sprintf(text, "%s(%d)", type, i);
		putText(draw, text, center, FONT_HERSHEY_PLAIN, 1.5, color[i], 2);
	}
	imshow("draw", draw);
	waitKey(0);
	destroyAllWindows();
}
void sol_problem_5(char *name) {
	Mat img = imread(name, 1);
	if (img.empty())
		return;

	Mat mask, dst, res;

	Mat kernel_x = getGaussianKernel(img.cols, 80); // column vector with x coord size
	Mat kernel_y = getGaussianKernel(img.rows, 80); // column vector with y coord size
	Mat kernel_x_transpose;

	transpose(kernel_x, kernel_x_transpose); // make row vector by transposing column vector of x size
	Mat kernel = kernel_y * kernel_x_transpose; // make 2D kernel
	normalize(kernel, kernel, 0, 1, NORM_MINMAX); // normalize the kernel [0..1]

	vector<Mat> channels(3);
	split(img, channels);

	for (int i = 0; i < 3; i++)
	{
		channels[i].convertTo(dst, CV_64F); // CV_8U -> CV_64F
		multiply(kernel, dst, dst); // dst = mask * dst
		convertScaleAbs(dst, dst); // CV_64F -> CV_8U
		channels[i] = dst;
	}

	merge(channels, res);
	imshow("kernel", kernel);
	imshow("res", res);

	waitKey(0);

}

void sol_problem_4(char *name) {
	VideoCapture cap(name);
	if (cap.isOpened() == false)
		return;
	Mat frame, hsv, gray, bin, bin2, mask;
	vector<Mat> channels(3);
	bool stop = false;

	while (1) {
		if (!stop) {
			cap >> frame;
			if (frame.empty())
				break;
			resize(frame, frame, Size(0, 0), 0.8, 0.8);
			cvtColor(frame, hsv, COLOR_BGR2HSV);
			cvtColor(frame, gray, COLOR_BGR2GRAY);
			split(hsv, channels);
			inRange(hsv, Scalar(0, 70, 80), Scalar(10, 255, 255), bin);
			inRange(hsv, Scalar(170, 70, 80), Scalar(180, 255, 255), bin2);
			bitwise_or(bin, bin2, mask); // RED MASK
			bitwise_and(gray, ~mask, gray); // GRAY range
			cvtColor(gray, gray, COLOR_GRAY2BGR); // change # of channel to 3
			cvtColor(mask, mask, COLOR_GRAY2BGR); // change # of channel to 3
			bitwise_and(frame, mask, frame);
			bitwise_or(frame, gray, frame);
		}
		imshow("result", frame);
		imshow("red", mask);
		int key = waitKey(30);
		if (key == 27)
			break;
		else if (key == ' ')
			stop = !stop;
	}
}

void sol_problem_3(char *name)
{
	VideoCapture cap(name);
	if (cap.isOpened() == false)
		return;

	Mat frame, prev, dst;
	cap >> prev;
	cvtColor(prev, prev, COLOR_BGR2GRAY);
	while (1) {
		cap >> frame;
		if (frame.empty())
			break;
		cvtColor(frame, frame, COLOR_BGR2GRAY);
		imshow("live", frame);
		absdiff(frame, prev, dst);
		threshold(dst, dst, 10, 255, THRESH_BINARY);
		imshow("diff", dst);
		prev = frame.clone();
		int key = waitKey(33);
		if (key == 27)
			break;
	}
}

void sol_problem_2(char *name) {
	VideoCapture cap(name);
	Mat frame, display;
	bool stop = false;
	bool graymode = false;

	while (1) {
		if (!stop) {
			cap >> frame;
			if (frame.empty())
				break;
		}

		if (graymode == true)
			cvtColor(frame, display, COLOR_BGR2GRAY);
		else
			display = frame;
		imshow("display", display);

		int key = waitKey(30);
		if (key == 27)
			break;
		else if (key == ' ')
			stop = !stop;
		else if (key == '0')
			graymode = true;
		else if (key == '1')
			graymode = false;
	}
}

void sol_problem_1(char *name) {
	Mat img = imread(name);
	Mat hsv;
	vector<Mat> colors(7);
	cvtColor(img, hsv, COLOR_BGR2HSV);
	inRange(hsv, Scalar(0, 200, 0), Scalar(5, 255, 255), colors[0]); //red  (0)
	inRange(hsv, Scalar(10, 200, 0), Scalar(20, 255, 255), colors[1]); // orange (15)
	inRange(hsv, Scalar(20, 200, 0), Scalar(30, 255, 255), colors[2]); // yellow (27.75)
	inRange(hsv, Scalar(50, 200, 0), Scalar(65, 255, 255), colors[3]); // green (60)
	inRange(hsv, Scalar(80, 200, 0), Scalar(100, 255, 255), colors[4]);//  light blue (99.75)
	inRange(hsv, Scalar(105, 200, 0), Scalar(125, 255, 255), colors[5]); // blue (109.5)
	inRange(hsv, Scalar(130, 200, 0), Scalar(150, 255, 255), colors[6]); //purple (133.5)

	imshow("src", img);
	char cname[20];
	//for (int i = 0; i < colors.size(); i++)
	//{
	//	if (!colors[i].empty()) {
	//		sprintf(cname, "color-%d", i);
	//		imshow(cname, colors[i]);
	//	}
	//}

	Mat eroded, dilated;
	Mat merged(img.size(), CV_8UC1, Scalar(0));
	for (int i = 0; i < colors.size(); i++) {
		if (colors[i].empty())
			continue;
		erode(colors[i], eroded, Mat(), Point(-1, -1), 2);
		dilate(colors[i], dilated, Mat(), Point(-1, -1), 2);
		colors[i] = dilated - eroded;
		//sprintf(cname, "contour-%d", i);
		//imshow(cname, colors[i]);
		bitwise_or(merged, colors[i], merged);
	}

	bitwise_not(merged, merged);
	imshow("merged", merged);
	cvtColor(merged, merged, COLOR_GRAY2BGR);
	bitwise_and(merged, img, img);

	imshow("result", img);
	waitKey(0);
}
int main() {

	sol_problem_1("./images/Tangram/bird_warp.jpg");
	//sol_problem_2("./images/Tangram/bird_nohand.mp4");
	//sol_problem_3("./images/road/road1.mkv");
	//sol_problem_4("./images/Tangram/bird_nohand.mp4");
	//sol_problem_5("./images/flower.png");
	//sol_problem_6("./images/Tangram/bird.png");
	system("pause");
}

Mat get_HorizDerivKernel()
{
	Mat kernel = (Mat_<float>(3, 3) << -1, 0, 1, -1, 0, 1, -1, 0, 1);
	kernel = kernel / 3.0; return kernel;
}

Mat get_VertDerivKernel() {
	Mat kernel = (Mat_<float>(3, 3) << -1, -1, -1, 0, 0, 0, 1, 1, 1);
	kernel = kernel / 3.0; return kernel;
}
