/*	形态学概述
	形态学（morphology）一词通常表示生物学的一个分支，该分支主要研究动植物的形态和结构。而我们图像处理中的形态学，往往指的是数学形态学。
	数学形态学（Mathematical morphology）是一门建立在格伦和拓扑学基础之上的图像分析学科，是数学形态学图像处理的基本理论。其基本的运算包括：二值腐蚀和膨胀、二值开闭运算、骨骼抽取、极限腐蚀、击中击不中变换、形态学梯度、Top-hat变换、颗粒分析、流域变换、灰值腐蚀和膨胀、灰值开闭运算、灰值形态学梯度等。
	简单来讲，形态学操作就是基于形态的一系列图像处理操作。OpenCV为进行图像的形态学操作有两种，分别是膨胀（dilate）与腐蚀（erode）。
	膨胀与腐蚀能实现多种多样的功能，主要如下。
	·消除噪声：
	·分割（isolate）出独立的图像元素，在图像中连接（join）相邻的元素；
	·寻找图像中的明显的极大值区域或极小值区域；
	·求出图像的梯度；
	腐蚀和膨胀是对白色部分（高亮部分）而言的，不是黑色部分。膨胀是图像中的高亮部分进行膨胀，类似于“领域扩张”，效果图拥有比原图更大的高亮区域；腐蚀是原图中的高亮部分被腐蚀，类似于“领域被蚕食”，效果图拥有比原图更小的高亮区域。
*/


/*	膨胀
	膨胀（dilate）就是求局部最大值的操作。从数学角度来说，膨胀或者腐蚀操作就是讲图像（或图像的一部分区域，称之为A）与核（称之为B）进行卷积。
	核可以是任何型状和大小，它拥有一个单独定义出来的参考点，我们称其为锚点（anchorpoint）。多数情况下，核是一个小的，中间带有参考点和实心正方形或者圆盘。其实，可以把核视为模板或者掩码。
	而膨胀就是求局部最大值的操作。核B与图形卷积，即计算核B覆盖的区域的像素点的最大值，并把这个最大值赋值给参考点指定的像素。这样就会使图像中的高亮区域逐渐增长。
	腐蚀
	腐蚀（erode）是相反的一对操作，所以腐蚀就是求局部最小值的操作。
*/

#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

int main()
{
	Mat image = imread("img/700-700狂三1.jpeg");
	imshow("原图", image);

	// 获取自定义核
	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
	Mat out;

	dilate(image, out, element);
	imshow("膨胀", out);

	// 获取自定义核
	Mat element2 = getStructuringElement(MORPH_RECT, Size(15, 15));
	Mat imgErode;
	erode(image, imgErode, element2);
	imshow("腐蚀", imgErode);

	waitKey(0);
	return 0;
}	