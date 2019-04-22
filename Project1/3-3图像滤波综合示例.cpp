#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

Mat
g_srcImage, g_dstImage1, g_dstImage2, g_dstImage3, g_dstImage4, g_dstImage5;
int g_nBoxFilterValue = 6; // �����˲��ں�ֵ
int g_nMeanBlurValue = 10; // ��ֵ�˲��ں�ֵ
int g_nGaussianBlurValue = 6; // ��˹�˲��ں�ֵ
int g_nMedianBlurValue = 10; // ��ֵ�˲�����ֵ
int g_nBilateralFilterValue = 10; // ˫���˲�����ֵ
char g_windowName[] = "�ں�ֵ";


// �켣���ص�����
static void on_BoxFilter(int, void *); // �����˲�
static void on_MeanBlur(int, void *); // ��ֵ�˲���
static void on_GaussianBlur(int, void *); // ��˹�˲���
static void on_MedianBlur(int, void *); // ��ֵ�˲���
static void on_BilateralFilter(int, void *); // ˫���˲���

int main()
{
	system("color 5E");

	g_srcImage = imread("img/700-700����1.jpeg", 1);
	if (g_srcImage.empty()) { printf("��ȡsrcImage���� ~!"); return false; }

	g_dstImage1 = g_srcImage.clone();
	g_dstImage2 = g_srcImage.clone();
	g_dstImage3 = g_srcImage.clone();
	g_dstImage4 = g_srcImage.clone();
	g_dstImage5 = g_srcImage.clone();

	imshow("ԭͼ", g_srcImage);

	namedWindow("�����˲�", 1);
	createTrackbar(g_windowName, "�����˲�", &g_nBoxFilterValue, 50, on_BoxFilter);
	on_BoxFilter(g_nBoxFilterValue, 0);


	namedWindow("��ֵ�˲�", 1);
	createTrackbar(g_windowName, "��ֵ�˲�", &g_nMeanBlurValue, 50, on_MeanBlur);
	on_MeanBlur(g_nMeanBlurValue, 0);

	namedWindow("��˹�˲�", 1);
	createTrackbar(g_windowName, "��˹�˲�", &g_nGaussianBlurValue, 50, on_GaussianBlur);
	on_GaussianBlur(g_nGaussianBlurValue, 0);

	namedWindow("��ֵ�˲�", 1);
	createTrackbar(g_windowName, "��ֵ�˲�", &g_nMedianBlurValue, 50, on_MedianBlur);
	on_MedianBlur(g_nMedianBlurValue, 0);

	namedWindow("˫���˲�", 1);
	createTrackbar(g_windowName, "˫���˲�", &g_nBilateralFilterValue, 50, on_BilateralFilter);
	on_BilateralFilter(g_nBilateralFilterValue, 0);
	while (char(waitKey(1) != 'q')) {}

	return 0;
}


static void on_BoxFilter(int, void *)
{
	boxFilter(g_srcImage, g_dstImage1, -1, Size(g_nBoxFilterValue+1, g_nBoxFilterValue+1));
	imshow("�����˲�", g_dstImage1);
}

static void on_MeanBlur(int, void *)
{
	blur(g_srcImage, g_dstImage2, Size(g_nMeanBlurValue + 1, g_nMeanBlurValue + 1), Point(-1, -1));
	imshow("��ֵ�˲�", g_dstImage2);
}

static void on_GaussianBlur(int, void *)
{
	GaussianBlur(g_srcImage, g_dstImage3,Size(g_nGaussianBlurValue*2+1, g_nGaussianBlurValue*2+1), 0, 0);
	imshow("��˹�˲�", g_dstImage3);
}

static void on_MedianBlur(int, void *)
{
	medianBlur(g_srcImage, g_dstImage4, g_nMeanBlurValue*2+1);
	imshow("��ֵ�˲�", g_dstImage4);
}

static void on_BilateralFilter(int, void *)
{
	bilateralFilter(g_srcImage, g_dstImage5, g_nBilateralFilterValue, g_nBilateralFilterValue * 2, g_nBilateralFilterValue / 2);
	imshow("˫���˲�", g_dstImage5);
}