#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <vector>

using namespace cv;

// 1-Mat类(最基本的数据结构)
/*
	1.Mat不仅仅是一个图像容器类,同时也是一个通用的矩阵类.
	2.不必再手动为其开辟空间,也不必在不需要的时候立即将他的空间释放
	3.Mat是一个类,由两个数据部分组成:
		1.矩阵头:矩阵尺寸,存储方法,存储地址等等所有相关信息(矩阵头的尺寸是常数值)
		2.指向存储所有像素值数据块的指针.
	4.赋值运算符和复制构造函数只会复制信息头和只想数据块指针的值,但是不会完整的复制一个矩阵
		(为了性能和避免内存溢出考虑).所以有多个对象采用同一个值矩阵,改变其中一个对象有改变其他的对象的可能.
	5.使用clone()或者copyTo()来深层复制一副图像的矩阵.
	6.前面已经知道一个矩阵可以被多个Mat对象引用,那么最后一个使用这个矩阵的对象,负责清理矩阵.
		通过引用计数机制来实现.我们无论什么时候复制一个Mat对象的信息头,都会增加矩阵的引用次数.
		反之,当一个头被释放之后,这个计数被减一;当计数值为零,矩阵会被清理.
*/
int Mat3()
{
	// 1-Mat的初始化和输出
	Mat pic(10, 3, CV_8SC3, Scalar(0, 0, 1));

	std::cout << "leonardo" << std::endl;
	std::cout << cv::format(pic, cv::Formatter::FMT_C) << std::endl;
	cv::imshow("Test", pic);
	cv::waitKey();
	// getchar():


	// 2-赋值信息头
	Mat A, C; // 仅创建信息头部分
	A = imread("700-700狂三1.jpeg",1); // 这里为矩阵开辟内存
	if (A.empty())
		return -2;
	imshow("内存开辟的图像A", A);
	Mat B(A); // 使用拷贝构造函数
	imshow("拷贝构造函数B", B);
	C = A; // 赋值运算符
	imshow("赋值运算的图像C", C);

	// 3-我们可以创建只引用部分数据的信息头,比如想要创建一个感兴趣区域(ROI)只需要创建包含边界信息的信息头
	Mat D(A, Rect(10, 10, 100, 100)  ); // 使用矩形界定
	//Mat E = A(Range:all(), Range(1, 3)); // 用行和列来界定
	imshow("边界界定D", D);

	//4-深拷贝
	Mat F = A.clone();
	Mat G;
	A.copyTo(G);

	//5-empty()函数 判断是否Mat是空的元素
	Mat E;
	printf("E是空的,E.empty():%d", E.empty());

	//6-channels()函数 返回一个Mat对象的通道
	Mat H = imread("700-700狂三1.jpeg", 0);
	printf("\nA(彩色)的通道数:A.channels():%d\nH(灰色)的通道数:H.channels():%d", A.channels(), H.channels());
	
	//7-Scalar类(颜色表示)
	/*
		1.Scalar类源头为scalar_类,typedef Scalar_<double> cv::Scalar后称为scalar类
		2.Scalar表示具有4个元素的数组,一般在OpenCV中被用来传递像素值
		一般的用法就是Scalar(a,b,c)表示一个颜色对象.注意:顺序分别是蓝,绿,红.
	*/
	waitKey(0);
	return 0;
}


// 2-输出其他常用数据结构
int main4()
{
	// 1.定义和输出二维点
	Point2f p(6, 2);
	std::cout << "[二维点] p = " << p << ";\n" << std::endl;

	// 2.定义和输出三维点
	Point3f p3f(8, 2, 0);
	std::cout << "[三维点] p3f = " << p3f << ";\n" << std::endl;

	// 3.定义和输出基于Mat的std::vector
	std::vector<float> v;
	v.push_back(3);
	v.push_back(5);
	v.push_back(7);

	std::cout << "[基于Mat的vector] shortvec = " << Mat(v) << ";\n" << std::endl;

	// 4.定义和输出std::vector点
	std::vector<Point2f> points(20);
	for (size_t i =0; i < points.size(); ++i)
	{
		points[i] = Point2f((float)(i * 5), (float)(i % 7));
	}
	std::cout << "[二维点向量]points = " << points << ";";

	// 5.矩阵的表示:Rect类

	// 6.颜色空间转换:cvtColor()函数

	return 0;
}