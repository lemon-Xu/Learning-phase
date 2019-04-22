#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

Mat g_srcImage, g_dstImage; // 原始图和效果图
int g_nTrackbarNumer = 0; // 0表示腐蚀erode， 1表示膨胀dilate
int g_nStructElemnetSize = 3; // 结构元素（内核矩阵）的尺寸



void Process(); // 膨胀和腐蚀的处理函数
void on_TrackbarNumChange(int, void *); // 回调函数
void on_ElementSizeChange(int, void *); // 回调函数


int main()
{
	system("color 5E");

	g_srcImage = imread("img/700-700狂三1.jpeg", 1);
	if (g_srcImage.empty()) { printf("读取srcImage错误~!"); return false; }

	imshow("原始图", g_srcImage);
	imshow("【效果图】", g_srcImage);
	// 创建轨迹条
	createTrackbar("腐蚀/膨胀","【效果图】",&g_nTrackbarNumer,1,on_TrackbarNumChange);
	createTrackbar("内核尺寸","【效果图】", &g_nStructElemnetSize, 21, on_ElementSizeChange);

	// 轮询获取按键信息，按下q键，程序退出
	while (char(waitKey(1) != 'q' )) {}
	return 0;
}


void Process()
{
	Mat element = getStructuringElement(MORPH_RECT, Size(2 * g_nStructElemnetSize + 1, 2 * g_nStructElemnetSize + 1), Point(g_nStructElemnetSize, g_nStructElemnetSize));

	if (g_nTrackbarNumer == 0) {
		erode(g_srcImage, g_dstImage, element);
	}
	else {
		dilate(g_srcImage, g_dstImage, element);
	}

	imshow("【效果图】", g_dstImage);
}


void on_TrackbarNumChange(int, void *)
{
	// 腐蚀和膨胀之间效果已经切换，回调函数体内需调用一次Process函数，使改变后的效果立即生效并显示出来
	Process();
}

void on_ElementSizeChange(int, void *)
{
	Process();
}