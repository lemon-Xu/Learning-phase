#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>

using namespace cv;

//	感兴趣区域ROI
/*
	在图像处理领域，我们常常需要设置感兴趣区域（ROI, region of interest），来专注或者简化工作区域。也就是从图像中选择一个图像区域，
这个区域是图像分析所关注的重点。我们圈定这个区域，以便进行进一步处理。而且，使用ROI指定想读入的目标，可以减少处理时间，增加精度，给图像处理带来不小的便利。
	定义ROI区域有两种方法：第一种是使用表示矩形区域的Rect。它指定矩形的左上角坐标（构造函数的前两个参数）和矩形的长宽（构造函数的后两个参数）以定义一个矩形区域。
	imageROI = image(Rect(500, 250, logo.cols, logo.rows));
	另一种定义ROI的方法是指定感兴趣行或列的范围（Range）。Range是指从起始索引到终止索引（不包括终止索引）的一连段连续序列。cRange可以用来定义Range。如果使用Range来定义ROI，那么前例中定义ROI的代码可以重写为：
	imageROI = image(Range(250, 250 + logoImage.rows), Range(200,200+logoIamge.cols));
*/

//	1-利用ROI将一幅图加到另一幅图的指定位置
/*
	我们通过一个图像掩模（mask），直接将插入处的像素设置位logo图像的像素值，这样效果会很逼真.
	mask就是位图啊，来选择哪个像素允许拷贝，哪个像素不允许拷贝。如果mask像素的值是非0的，我就拷贝它，否则不拷贝。
*/
bool ROI_AddImage()
{
	Mat srcImage1 = imread("700-700狂三1.jpeg");
	Mat logoImage = imread("200-200狂三1.jpeg");
	
	if (!srcImage1.data) { printf("读取srcImage1 错误~! \n"); return false; }
	if (!logoImage.data) { printf("读取logoImage错误~!  \n"); return false; }

	//// 定义一个Mat类型并给其设定ROI区域
	Mat imageROI = srcImage1(  Rect(200, 250, logoImage.cols, logoImage.rows) ); 
	
	// 加载掩模（必须是灰度图）
	Mat mask = imread("200-200狂三1.jpeg", 0);
	
	// 将掩模复制到ROI
	logoImage.copyTo(imageROI, mask);

	namedWindow("<1>利用ROI实现图像叠加示例窗口");
	imshow("<1>利用ROI实现图像叠加示例窗口", srcImage1);
	waitKey(0);

	return true;
}

// 2-线性混合操作
/*
	线性混合操作是一种典型的二元（两个输入）的像素操作，它的理论公式如下：
		g(x) = (1-a) fa(x) + af3(x)
	我们通过在范围0到1之间改变alpha值，来对两幅图像（ f0(x) 和 f1(x) ）或两段视频（同样为 f0(x) 和 f1(x)）产生时间上的交叉溶解(cross-dissolve)效果，就像幻灯片和电影制作中的那样，也就是在幻灯片翻页时设置的前后页缓慢过度叠加效果，以及电影情节过度时经常出现的画面叠加效果。
	实现方面，主要运用了OpenCV中addWeighted函数
	dst = src1[I]*alpha + src2[I]*beta + gamma;
	其中I是多维数组元素的索引值。而且，在遇到多通道数组的时候，每个通道都需要独立地进行处理。另外需要注意的是，当输出数组的深度为CV_32S时，这个函数就不适用了，这时候就会内存溢出或者算出的结果压根部队。
*/
bool LinearBlending()
{
	// 定义一些局部变量
	double alphaValue = 0.5;
	double betaValue;
	Mat srcImage2, srcImage3, dstImage;

	// 读取图像（两幅图片需为同样的类型和尺寸）
	srcImage2 = imread("700-700狂三1.jpeg");
	srcImage3 = imread("700-700狂三2.jpeg");

	if (srcImage2.empty()) { printf("读取srcImage2错误~! \n"); return false; }
	if (srcImage3.empty()) { printf("读取srcImage3错误~! \n"); return false; }

	// 做图像混合加权操作
	betaValue = (1.0 - alphaValue);
	addWeighted(srcImage2, alphaValue, srcImage3, betaValue, 0.0, dstImage);

	// 创建并显示原图窗口
	namedWindow("<2>线性混合示例窗口[原图]", 1);
	imshow("<2>线性混合示例窗口[原图]", srcImage2);

	namedWindow("<3>线性混合示例窗口[效果图]",1);
	imshow("<3>线性混合示例窗口[效果图]", dstImage);

	waitKey(0);
	return true;

	/*
		在这里需要注意的是,因为我们是对srcImage1和srcImage2求和,所以它们必须要有相同的尺寸(宽度和高度)和类型,不然多余的部分没有对应的"伴",肯定会出问题.
	*/
}


// 3-初级图像混合
/*
	先指定ROI,再用addWeighted函数对指定的ROI区域的图像进行混合操作.我们将其封装在了一个名为ROI_LinearBlending的函数中
*/
bool ROI_LinearBlending()
{
	Mat srcImage4 = imread("img/700-700狂三1.jpeg",1);
	Mat srcImage5 = imread("img/200-200狂三1.jpeg");
	Mat mask = imread("img/200-200狂三1.jpeg");
	Mat dstImage;

	if (srcImage4.empty()) { printf("读取srcImage4错误\n"); return false; }
	if (srcImage5.empty()) { printf("读取srcImage5错误\n"); return false; }

	Mat imageROI;
	imageROI = srcImage4(Rect(200, 250, srcImage5.cols, srcImage5.rows));

	
	// 方法二
//  imageROI = srcImage4(Range(250, 250+srcImage5.rows), Range(200, 200+srcImage5.cols));

	addWeighted(imageROI, 0.5, srcImage5, 0.3, 0.0, dstImage);
	dstImage.copyTo(imageROI, mask);

	namedWindow("<4>区域线性图像混合示例窗口");
	imshow("<4>区域线性图像混合示例窗口",srcImage4);

	waitKey(0);
	return true;
}



int main()
{
	ROI_LinearBlending();
	
	return 0;
}