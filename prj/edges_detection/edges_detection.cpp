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
		//filename = "1.jpg";
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
		Mat image_blured;
		medianBlur(image, image_blured, 5);
		cvtColor(image_blured, hsv, CV_BGR2HSV);
		inRange(hsv, Scalar(0, 30, 80), Scalar(17, 170, 255), hsv);
		Mat canny_output;
		vector<vector<Point> > contours;
		vector<Vec4i> hierarchy;
		findContours(hsv, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
		int s = findBiggestContour(contours);
		Mat drawing = Mat::zeros(image.size(), CV_8UC1);
		drawContours(drawing, contours, s, Scalar(255), -1, 8, hierarchy, 0, Point());

		dilate(drawing, drawing, getStructuringElement(MORPH_ELLIPSE, Size(4, 4)));

		cvtColor(image_blured, gray, CV_RGB2GRAY);

		Mat _img;
		double otsu_thresh_val = threshold(gray, _img, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);
		double sigma = 0.33;
		Canny(gray, dst, int(max(0, (int)(otsu_thresh_val*(1 - sigma)))), int(min(255, (int)(otsu_thresh_val*(1 + sigma)))), 3);
		Mat filtered_edges = Mat::zeros(image.size(), CV_8UC1);
		dst.copyTo(filtered_edges, drawing);

		Mat gr;
		cvtColor(image, gr, CV_RGB2GRAY);
		Mat show_result(image.rows, image.cols * 4, CV_8UC1, Scalar(0, 0, 0));
		Rect roi(Rect(0, 0, image.cols, image.rows));
		gr.copyTo(show_result(roi));
		roi = Rect(image.cols, 0, image.cols, image.rows);
		gray.copyTo(show_result(roi));
		roi = Rect(image.cols*2, 0, image.cols, image.rows);
		drawing.copyTo(show_result(roi));
		roi = Rect(image.cols * 3, 0, image.cols, image.rows);
		filtered_edges.copyTo(show_result(roi));

		imshow(fileNames[i], show_result);

		//Mat diff = Mat::zeros(filtered_edges.size(), CV_8UC1);
		//const char* filename_template = fileNames[i].c_str();
		//filename_template = "1_template.jpg";
		//Mat image_template = imread(filename_template);
		//int y_size_template = 200;
		//int x_size_template;
		//if (image_template.rows >= y_size) {
		//	x_size_template = (int)(image_template.cols / ((double)image_template.rows / y_size));
		//}
		//else
		//{
		//	x_size_template = (int)(image_template.cols * ((double)y_size / image_template.rows));
		//}
		//resize(image_template, image_template, Size(x_size_template, y_size_template));
		//imshow("a", image_template);
		//imshow("b", filtered_edges);
		//blur(filtered_edges, filtered_edges, Size(5, 5), Point(-1, -1), 4);
		//blur(image_template, image_template, Size(5, 5), Point(-1, -1), 4);
		//absdiff(image_template, filtered_edges, diff);
		//diff = image_template - filtered_edges_diff;
		//for (int j = 0; j < diff.cols; j++) {
		//	for (int i = 0; i < diff.rows; i++) {
		//		diff.at<uint8_t>(i, j) = abs(filtered_edges.at<uint8_t>(i, j) - image_template.at<uint8_t>(i, j));
		//	}
		//}
		//imshow("c", diff);

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
