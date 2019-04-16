#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;

/* 理论依据
	首先了解一下算子的概念。一般的图像处理算子都是一个函数，它接受一个或多个输入图像，并产生输出图像。下面是算子的一般形式。
		g(x) = h(f(x)) 或者 g(x) = h(f0(x).......fn(x))
	本节所讲解的图像亮度和对比度的调整操作，其实属于图像处理操作中比较简单的一种—点操作(pointoperators)。点操作有一个特点：仅仅根据输入像素值（有时可加上某些全局信息或参数），来计算相应的输出像素值。这类算子包括亮度（brightness）和对比度(contrast)调整、颜色校正(colorcorrection)和变换(transformations).
	两种最常用的点操作(或者说点算子)是乘上一个常数（对应对比度的调节）以及加上一个常数（对应亮度值的调节）。公司如下:
		g(x) = a * f(x) + b
			参数f(x)表示源图像像素。
			参数g(x)表示输出图像像素
			参数a(需要满足 a>0 )被称为增益(gain),常常被用来控制图像的对比度。
			参数b通常被称为偏置（bias），常常被用来控制图像的亮度。
		我们改写这个式子:
			g(i,j) = a*f(i,j) + b
		其中,i和j表示像素位于第i行和第j列，这个式子可以用来作为我们在OpenCV中控制图像的亮度和对比度的理论公式。
*/

/*	实现对比度和亮度改变
	·为了访问图像的每一个像素，使用这样的语法：image.at<Vec3b>(y,x)[c].
		其中，y是像素所在的行，x是像素所在的列，c是R、G、B（对应0、1、2）其中之一。
	·因为运算结果可能会超出像素取值范围（溢出），还可能是非整数（如果是浮点数的话），所以要用saturate_cast对结果进行转换，以确保它位有效值。
	·这里的a也就是对比度，一般为了观察的效果，它的取值位0.0到3.0的浮点比度值的nContrastValue参数设为0到300之间的整数，在最后的式子中乘以一个0.01，这里就完成了轨迹条中300个不同取值的变化。这就是为什么在式子中，会有saturate_cast<uchar>((g_cContrastValue*0.01)*(image.at<Vec3b>(y,x)[c])+g_nBrightValue)中的g_nContrastValue*0.01)


*/

// 全局函数声明
static void on_ContrastAndBright(int, void *);
static void ShowHelpText();

// 全局变量声明
int g_nContrastValue; // 对比度值
int g_nBrightValue; // 亮度值
Mat g_srcImage, g_dstImage;

int main()
{
	g_srcImage = imread("img/700-700狂三1.jpeg");
	if (g_srcImage.empty()) { printf("读取图像失败"); return -1; }

	g_dstImage = Mat::zeros(g_srcImage.size(), g_srcImage.type());
	
	// 设定对比度和亮度的初值
	g_nContrastValue = 80;
	g_nBrightValue = 80;

	namedWindow("【效果图窗口】", 1);

	createTrackbar("对比度", "【效果图窗口】", &g_nContrastValue, 300, on_ContrastAndBright);
	createTrackbar("亮  度","【效果图窗口】", &g_nBrightValue, 200, on_ContrastAndBright);

	// 进行回调函数初始化
	on_ContrastAndBright(g_nContrastValue, 0);
	on_ContrastAndBright(g_nBrightValue, 0);

	// 按下“q”键时，程序退出
	while (char(waitKey(1)) != 'q') {}
	return 0;

}



//改变图像对比度和亮度值的回调函数
static void on_ContrastAndBright(int, void*)
{
	// 创建窗口
	namedWindow("【原始图窗口】", 1);

	// 三个for循环，执行运算g_dstImage(i,j) = a*g_srcImage(i ,j) + b
	for (int y = 0; y < g_srcImage.rows; y++)
	{
		for (int x = 0; x < g_srcImage.cols; x++)
		{
			for (int c = 0; c < 3; c++)
			{
				g_dstImage.at<Vec3b>(y, x)[c] = saturate_cast<uchar>((g_nContrastValue * 0.01) * (g_srcImage.at<Vec3b>(y,x)[c] + g_nBrightValue));
			}
		}
	}
	
	// 显示图像
	imshow("【原始图窗口】", g_srcImage);
	imshow("【效果图窗口】", g_dstImage);

}