// corner_detect.cpp : Defines the entry point for the console application.
//从实验的结果来看，如果输入的图比较大，则处理速度过慢的问题会很严重
//使用电脑自带摄像头可以解决这个问题，使用转角判断器的时候很容易被环境的光线影响
//并且必须要经过归一化和取绝对值才能获得可显示的图像

#include "stdafx.h"

int threhold = 200;
Mat gsrc;
int radius = 10;
//int main(int argc,char** argv)
//{
//	void corner_detect(int, void*);
//	string source = "C:\\Users\\11235\\Pictures\\Camera Roll\\IMG_20170916_182429.jpg";
//	if (argc > 1) {
//		source = argv[0];
//	}
//	Mat src = imread(source, IMREAD_COLOR);
//	if (src.empty()) {
//		return -1;
//	}
//	
//	namedWindow("src", WINDOW_NORMAL);
//	cvResizeWindow("src", 500, 500);
//	imshow("src", src);
//	moveWindow("src", 0, 150);
//
//	cvtColor(src, gsrc, COLOR_RGB2GRAY);
//	namedWindow("gsrc", WINDOW_NORMAL);
//	cvResizeWindow("gsrc", 500, 500);
//	imshow("gsrc", gsrc);
//	moveWindow("gsrc", 250, 150);
//
//	namedWindow("corner", WINDOW_NORMAL);
//	createTrackbar("threhold", "corner", &threhold, 255, corner_detect);
//	createTrackbar("radius", "corner", &radius, 20, corner_detect);
//	
//	corner_detect(0, 0);
//	waitKey(0);
//    return 0;
//}
//void corner_detect(int, void*)
//{
//	Mat dst, dst_norm, dst_scale;
//	dst = Mat::zeros(gsrc.size(), CV_32FC1);
//	int blocksize = 2; int aperturesize = 3;
//	double k = 0.04;
//	cornerHarris(gsrc, dst, blocksize, aperturesize, k, BORDER_DEFAULT);
//	normalize(dst, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
//	convertScaleAbs(dst_norm, dst_scale);
//
//	for (int i = 0; i < dst_norm.rows; i++)
//		for (int j = 0; j < dst_norm.cols; j++)
//			if ((int)dst_norm.at<float>(i, j) > threhold)
//				circle(dst_scale, Point(j, i), radius, Scalar(0), 2, 8, 0);
//
//	cvResizeWindow("corner", 500, 500);
//	imshow("corner", dst_scale);
//	moveWindow("corner", 500, 150);
//}

int main(int argc, char** argv)
{
	VideoCapture video;
	video.open(0);//打开电脑摄像头
	if (!video.isOpened())
	{
		return -1;
	}
	Mat frame,gray,dst,corner;
	namedWindow("corner_detect", WINDOW_NORMAL);
	for (;;)
	{
		video.read(frame);
		if(frame.empty())
		{
			break;
		}
		cvtColor(frame, gray, COLOR_RGB2GRAY);
		//blur(gray, gray, Size(3, 3));

		//Canny(gray, corner, 60, 180);
		//进行转角识别
		cornerHarris(gray, dst, 3, 3, 0.1, BORDER_DEFAULT);
		//必须要经过标准化才能正常显示
		normalize(dst, corner, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
		//转化为绝对值
		convertScaleAbs(corner, corner);
		imshow("corner_detect", corner);
		imshow("Camera", frame);
		moveWindow("Camera", 500, 150);
		if (waitKey((5)) > 0) {
			break;
		}
	}
	return 0;
}