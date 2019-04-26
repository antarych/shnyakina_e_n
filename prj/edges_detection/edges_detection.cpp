#include <opencv2/core/core.hpp> 
#include <opencv2/highgui.hpp>
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <string>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

using namespace std;
using namespace cv;

int findBiggestContour(vector<vector<Point> >);

int main(int argc, char* argv[])
{
	const int n = 15;

	string fileNames[n];

	for (int i = 0; i < n; i++) {
		stringstream ss;
		ss << i + 1;
		fileNames[i] = ss.str() + ".jpg";
	}

	for (int i = 0; i < n; i++) {
		Mat image, hsv, gray, dst;
		const char* filename = fileNames[i].c_str();
		image = imread(filename);

		int y_size = 200;
		int x_size;
		if (image.rows >= y_size) {
			x_size = (int)(image.cols / ((double)image.rows / y_size));
		}
		else
		{
			x_size = (int)(image.cols * ((double)y_size / image.rows));
		}
		resize(image, image, Size(x_size, y_size));
		blur(image, image, Size(3, 3));
		cvtColor(image, hsv, CV_BGR2HSV);
		inRange(hsv, Scalar(0, 40, 80), Scalar(17, 170, 255), hsv);
		Mat canny_output;
		vector<vector<Point> > contours;
		vector<Vec4i> hierarchy;
		findContours(hsv, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
		int s = findBiggestContour(contours);
		Mat drawing = Mat::zeros(image.size(), CV_8UC1);
		drawContours(drawing, contours, s, Scalar(255), -1, 8, hierarchy, 0, Point());

		dilate(drawing, drawing, getStructuringElement(MORPH_ELLIPSE, Size(4, 4)));

		cvtColor(image, gray, CV_RGB2GRAY);

		Canny(gray, dst, 50, 130, 3);
		Mat filtered_edges;
		dst.copyTo(filtered_edges, drawing);

		Mat show_result(image.rows, image.cols * 3, CV_8UC1, Scalar(0, 0, 0));
		Rect roi(Rect(0, 0, image.cols, image.rows));
		gray.copyTo(show_result(roi));
		roi = Rect(image.cols, 0, image.cols, image.rows);
		drawing.copyTo(show_result(roi));
		roi = Rect(image.cols*2, 0, image.cols, image.rows);
		filtered_edges.copyTo(show_result(roi));

		imshow(fileNames[i], show_result);
	}

	cvWaitKey(10000000);
	return 0;
}

int findBiggestContour(vector<vector<Point> > contours) {
	int indexOfBiggestContour = -1;
	int sizeOfBiggestContour = 0;
	for (int i = 0; i < contours.size(); i++) {
		if (contours[i].size() > sizeOfBiggestContour) {
			sizeOfBiggestContour = contours[i].size();
			indexOfBiggestContour = i;
		}
	}
	return indexOfBiggestContour;
}
