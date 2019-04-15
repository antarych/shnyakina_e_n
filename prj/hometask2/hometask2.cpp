#include <opencv2\core\core.hpp> 
#include <opencv2\highgui.hpp>
#include "opencv2\opencv.hpp"
#include <string>
#include <iostream>
using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	Mat sourceImg = imread("imgGrayscale.jpg");

	namedWindow("Image", 1);
	int iSliderValue = 100;
	createTrackbar("Brightness", "Image", &iSliderValue, 200);
	while (true)
	{
		Mat resultImg;
		double brightness = iSliderValue - 100;
		sourceImg.convertTo(resultImg, -1, 1, brightness);

		int width = sourceImg.cols * 2;
		int height = sourceImg.rows;

		Mat inputAll = Mat(height, width, sourceImg.type());
		Rect rect = Rect(0, 0, sourceImg.cols, sourceImg.rows);
		sourceImg.copyTo(inputAll(rect));
		rect.x = sourceImg.cols;
		resultImg.copyTo(inputAll(rect));

		imshow("Image", inputAll);

		int iKey = waitKey(100);

		if (iKey == 27)
		{
			break;
		}
	}

	return 0;
}