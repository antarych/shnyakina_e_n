#include "opencv2\opencv.hpp"
#include "opencv2\highgui.hpp"
#include <iostream>   

using namespace std;
using namespace cv;

int main()
{
	Mat sourceImg = imread("imgRGB.jpg");
	imshow("Original", sourceImg);

	int histSize = 256;
	float range[] = { 0, histSize };
	const float* histRange = { range };

	bool uniform = true; 
	bool accumulate = false;

	Mat b_hist, g_hist, r_hist;

	vector<Mat> bgr_planes;
	split(sourceImg, bgr_planes);

	calcHist(&bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate);
	calcHist(&bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate);
	calcHist(&bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate);

	int hist_w = 512; 
	int hist_h = 400;
	int bin_w = cvRound((double)hist_w / histSize);
	Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));
	normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	for (int i = 1; i < histSize; i++)
	{
		line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(b_hist.at<float>(i - 1))),
			Point(bin_w*(i), hist_h - cvRound(b_hist.at<float>(i))),
			Scalar(255, 0, 0), 2, 8, 0);
		line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(g_hist.at<float>(i - 1))),
			Point(bin_w*(i), hist_h - cvRound(g_hist.at<float>(i))),
			Scalar(0, 255, 0), 2, 8, 0);
		line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(r_hist.at<float>(i - 1))),
			Point(bin_w*(i), hist_h - cvRound(r_hist.at<float>(i))),
			Scalar(0, 0, 255), 2, 8, 0);
	}

	Mat grayImg;
	cv::cvtColor(sourceImg, grayImg, cv::COLOR_BGR2GRAY);
	imshow("Gray", grayImg);

	const float* ranges[] = { range };
	int hist_w_g = 512;
	int hist_h_g = 400;
	int bin_w_g = cvRound((double)hist_w_g / histSize);

	Mat hist;
	calcHist(&grayImg, 1, 0, Mat(), hist, 1, &histSize, ranges, true, false);

	Mat histImageGray(hist_h_g, hist_w_g, CV_8UC1, Scalar(0, 0, 0));
	normalize(hist, hist, 0, histImageGray.rows, NORM_MINMAX, -1, Mat());

	for (int i = 1; i < histSize; i++)
	{
		line(histImageGray, Point(bin_w_g*(i - 1), hist_h_g - cvRound(hist.at<float>(i - 1))),
			Point(bin_w_g*(i), hist_h_g - cvRound(hist.at<float>(i))),
			Scalar(255, 0, 0), 2, 8, 0);
	}

	imshow("Garyscale hist", histImageGray);
	imshow("RGB hist", histImage);
	waitKey(0);

	return 0;
}