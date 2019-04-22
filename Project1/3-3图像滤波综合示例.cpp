#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

Mat
g_srcImage, g_dstImage1, g_dstImage2, g_dstImage3, g_dstImage4, g_dstImage5;
int g_nBoxFilterValue = 6; // 方框滤波内核值
int g_nMeanBlurValue = 10; // 均值滤波内核值
int g_nGaussianBlurValue = 6; // 高斯滤波内核值
int g_nMedianBlurValue = 10; // 中值滤波参数值
int g_nBilateralFilterValue = 10; // 双边滤波参数值
char g_windowName[] = "内核值";


// 轨迹条回调函数
static void on_BoxFilter(int, void *); // 方框滤波
static void on_MeanBlur(int, void *); // 均值滤波器
static void on_GaussianBlur(int, void *); // 高斯滤波器
static void on_MedianBlur(int, void *); // 中值滤波器
static void on_BilateralFilter(int, void *); // 双边滤波器

int main()
{
	system("color 5E");

	g_srcImage = imread("img/700-700狂三1.jpeg", 1);
	if (g_srcImage.empty()) { printf("读取srcImage错误 ~!"); return false; }

	g_dstImage1 = g_srcImage.clone();
	g_dstImage2 = g_srcImage.clone();
	g_dstImage3 = g_srcImage.clone();
	g_dstImage4 = g_srcImage.clone();
	g_dstImage5 = g_srcImage.clone();

	imshow("原图", g_srcImage);

	namedWindow("方框滤波", 1);
	createTrackbar(g_windowName, "方框滤波", &g_nBoxFilterValue, 50, on_BoxFilter);
	on_BoxFilter(g_nBoxFilterValue, 0);


	namedWindow("均值滤波", 1);
	createTrackbar(g_windowName, "均值滤波", &g_nMeanBlurValue, 50, on_MeanBlur);
	on_MeanBlur(g_nMeanBlurValue, 0);

	namedWindow("高斯滤波", 1);
	createTrackbar(g_windowName, "高斯滤波", &g_nGaussianBlurValue, 50, on_GaussianBlur);
	on_GaussianBlur(g_nGaussianBlurValue, 0);

	namedWindow("中值滤波", 1);
	createTrackbar(g_windowName, "中值滤波", &g_nMedianBlurValue, 50, on_MedianBlur);
	on_MedianBlur(g_nMedianBlurValue, 0);

	namedWindow("双边滤波", 1);
	createTrackbar(g_windowName, "双边滤波", &g_nBilateralFilterValue, 50, on_BilateralFilter);
	on_BilateralFilter(g_nBilateralFilterValue, 0);
	while (char(waitKey(1) != 'q')) {}

	return 0;
}


static void on_BoxFilter(int, void *)
{
	boxFilter(g_srcImage, g_dstImage1, -1, Size(g_nBoxFilterValue+1, g_nBoxFilterValue+1));
	imshow("方框滤波", g_dstImage1);
}

static void on_MeanBlur(int, void *)
{
	blur(g_srcImage, g_dstImage2, Size(g_nMeanBlurValue + 1, g_nMeanBlurValue + 1), Point(-1, -1));
	imshow("均值滤波", g_dstImage2);
}

static void on_GaussianBlur(int, void *)
{
	GaussianBlur(g_srcImage, g_dstImage3,Size(g_nGaussianBlurValue*2+1, g_nGaussianBlurValue*2+1), 0, 0);
	imshow("高斯滤波", g_dstImage3);
}

static void on_MedianBlur(int, void *)
{
	medianBlur(g_srcImage, g_dstImage4, g_nMeanBlurValue*2+1);
	imshow("中值滤波", g_dstImage4);
}

static void on_BilateralFilter(int, void *)
{
	bilateralFilter(g_srcImage, g_dstImage5, g_nBilateralFilterValue, g_nBilateralFilterValue * 2, g_nBilateralFilterValue / 2);
	imshow("双边滤波", g_dstImage5);
}