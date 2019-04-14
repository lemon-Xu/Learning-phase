#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void colorReduce1(Mat& inputImage, Mat& outputImage, int div);
void colorReduce2(Mat& inputImage, Mat& outputImage, int div);
void colorReduce3(Mat& inputImage, Mat& outputImage, int div);

// 1-颜色空间缩减
/*
	仅用颜色中具有代表性的很小的部分,就足以达到同样的效果,却不会对算法造成严重影响.
	做法:将现有颜色空间值除以(截余)某个输入值,以获得较少的颜色数.
	将计算后的值,保存在表中,只要只需要读取操作,不需要计算可以提高性能.
*/

// 2-LUT函数:Look up table操作
/*
	对于上文提到的Look up table操作,OpenCV官方文档中强烈推荐我们使用一个原型为operationsOnArrays:LUT()<lut>的函数进行.
	它用于批量进行图像元素查找、扫描与操作图像。
*/
int main()
{
	//创建原始图并显示
	Mat srcImage = imread("700-700狂三1.jpeg");
	imshow("原始图像", srcImage);

	//按原始图的参数规格来创建效果图
	Mat dstImage;
	dstImage.create(srcImage.rows, srcImage.cols, srcImage.type()); // 效果图的大小、类型与原图片相同

	//记录起始时间
	double time0 = static_cast<double>(getTickCount());
	
	//调用颜色空间缩减函数
	colorReduce3(srcImage, dstImage, 32);

	//计算运行时间并输出
	time0 = ((double)getTickCount() - time0) / getTickFrequency();
	cout << "此方法运算时间为: " << time0 << "秒" << endl; //输出运行时间

	//显示效果图
	imshow("效果图", dstImage);
	waitKey(0);

}


//【方法一】用指针访问像素  0.0483416秒 0.00205177秒  0.00208915秒
/*
	1.每行的像素值由以下语句得到：
		列数×通道数 = 每一行元素的个数
	2.为了简化指针运算，Mat类提供了ptr函数可以得到图像任意行的首地址。ptr是一个模板函数，它返回第i行的首地址：
		uchar* data = outputImage.ptr<uchar>(i); // 获取第i行的首地址
	3.而双层循环内部的那句处理像素的代码，我们可以等效地使用指针运算从一列移动到下一列。
		*data++ = *data / div * div + div / 2;
*/
void colorReduce1(Mat& inputImage, Mat& outputImage, int div)
{
	// 参数准备
	outputImage = inputImage.clone(); // 复制实参到临时变量
	int rowNumber = outputImage.rows; // 行数
	int colNumber = outputImage.cols * outputImage.channels(); //列数×通道数=每一行元素的个数

	//双重循环，遍历所有的像素值
	for (int i = 0; i < rowNumber; i++)
	{
		uchar* data = outputImage.ptr<uchar>(i); // 获取第i行的首地址
		for (int j = 0;j < colNumber;j++)
		{
			data[j] = data[j] / div * div + div / 2;
		}
	}
}
//【方法二】用迭代器操作像素  0.00271518秒 0.00282128秒  0.00292172秒
/*
	在迭代器中，我们所需要做的仅仅是获得图像矩阵的begin和end，然后增加迭代直至从begin到end。
	将*操作符添加在迭代指针前，即可访问当前指向的内容。相比用指针直接访问可能出现越界问题，迭代器绝对是非常安全的方法。
*/
void colorReduce2(Mat& inputImage, Mat& outputImage, int div)
{
	//参数准备
	outputImage = inputImage.clone();
	//获取迭代器
	Mat_<Vec3b>::iterator it = outputImage.begin<Vec3b>(); //初始位置的迭代器
	Mat_<Vec3b>::iterator itend = outputImage.end<Vec3b>(); //终止位置的迭代器

	//存取彩色图像像素
	for (;it != itend; ++it)
	{
		//开始处理每个像素
		(*it)[0] = (*it)[0] / div * div + div / 2;
		(*it)[1] = (*it)[1] / div * div + div / 2;
		(*it)[2] = (*it)[2] / div * div + div / 2;

	}


}


//【方法三】动态地址计算  0.0033986秒 0.00321698秒  0.00337179秒
/*
	第三种方法为用动态地址计算来操作像素。下面使用动态地址运算配合at方法的colorReduce函数的代码。
	1.成员函数at(int y, int x)可以用来存取图像元素，但是必须在编译期知道图像的数据类型，at方法本身不会对任何数据类型进行转换.
	2.对于一个包含彩色图像的Mat，会返回一个由三个8位数组成的向量。OpenCV将此类型的向量定义位Vec3b，即由三个unsigned char组成的向量
	image.at<Vec3b>(row ,col)[channel] = value
*/
void colorReduce3(Mat& inputImage, Mat& outputImage, int div)
{
	//参数准备
	outputImage = inputImage.clone();
	int rowNumber = outputImage.rows;
	int colNumber = outputImage.cols;

	//存取彩色图像像素
	for (int i = 0; i < rowNumber; i++)
	{
		for (int j = 0; j < colNumber; j++)
		{
			outputImage.at<Vec3b>(i, j)[0] = outputImage.at<Vec3b>(i, j)[0] / div * div + div / 2; //蓝色通道
			outputImage.at<Vec3b>(i, j)[1] = outputImage.at<Vec3b>(i, j)[1] / div * div + div / 2; //绿色通道
			outputImage.at<Vec3b>(i, j)[2] = outputImage.at<Vec3b>(i, j)[2] / div * div + div / 2; //红色通道
		}
	}
}