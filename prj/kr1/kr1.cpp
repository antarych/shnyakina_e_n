#include "opencv2\opencv.hpp"
#include "opencv2\highgui.hpp"
#include <iostream>   

using namespace std;
using namespace cv;

int main()
{
	Mat image = Mat::zeros(500, 700, CV_8UC3);
	rectangle(image, Point(50, 50), Point(250, 250), Scalar(0, 0, 0), -1, 8, 0);
	rectangle(image, Point(50, 250), Point(250, 450), Scalar(127, 127, 127), -1, 8, 0);
	rectangle(image, Point(250, 50), Point(450, 250), Scalar(255, 255, 255), -1, 8, 0);
	rectangle(image, Point(250, 250), Point(450, 450), Scalar(0, 0, 0), -1, 8, 0);
	rectangle(image, Point(450, 50), Point(650, 250), Scalar(127, 127, 127), -1, 8, 0);
	rectangle(image, Point(450, 250), Point(650, 450), Scalar(255, 255, 255), -1, 8, 0);
	circle(image, Point(150, 150), 70, Scalar(127, 127, 127), -1, 8);
	circle(image, Point(150, 350), 70, Scalar(0, 0,0), -1, 8);
	circle(image, Point(350, 150), 70, Scalar(127, 127, 127), -1, 8);
	circle(image, Point(350, 350), 70, Scalar(255, 255, 255), -1, 8);
	circle(image, Point(550, 150), 70, Scalar(255, 255, 255), -1, 8);
	circle(image, Point(550, 350), 70, Scalar(0, 0, 0), -1, 8);

	const float kernel2[] = { 1, 0,
							  0, -1 };
	const float kernel3[] = { -1, -2, -1,
								0, 0, 0,
								1, 2, 1 };
	const Mat kernel0(2, 2, CV_32FC1, (float *)kernel2);
	const Mat kernel(3, 3, CV_32FC1, (float *)kernel3);
	Mat result2, result3;

	filter2D(image, result2, -1, kernel0, Point(-1, -1), 127, BORDER_REPLICATE);
	filter2D(image, result3, -1, kernel, Point(-1, -1), 127, BORDER_REPLICATE);
	imshow("Original", image);
	imshow("2x2", result2);
	imshow("3x3", result3);
	waitKey(0);
	return 0;
}