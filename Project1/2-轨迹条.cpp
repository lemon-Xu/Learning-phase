#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>
using namespace cv;


#define WINDOW_NAME "【线性混合示例】" //为窗口标题定义的宏

//全局变量声明
const int g_nMaxAlphaValue = 100; // Alpha值的最大值
int g_nAlphaValueSlider; // 滑动条对应的变量
double g_dAlphaValue;
double g_dBetaValue;

// 声明存储图像的变量
Mat g_srcImage1;
Mat g_srcImage2;
Mat g_dstImage;

// ----------【on_Trackbar()函数】---------
// 描述：响应滑动条的回调函数， 改变图片Alpha通道的值
//addWeighted() 线性混合函数，加权函数
/*
	参数一：mat     src1 第一个图像像素组
	参数二：double  alpha 第一个图像权重  
	参数三：mat		src2 第二个图像像素组 
	参数四：double  beta 第二个图像权重   
	参数五：double  gamma 亮度标准偏差，用于表示显示器像素灰度的均匀程度，常用于学术界，该值越小说明像素灰度分布越集中，越大说明像素灰度分布越分散。
	参数六：mat      用于存放生成图像像素组

	矩阵表达式来代替
	dst = src1 * alpha + src2 * beta + gamma;
*/
void on_Trackbar(int, void*)
{
	//求出当前alpha值相当于最大值的比例
	g_dAlphaValue = (double)g_nAlphaValueSlider / g_nMaxAlphaValue;
	//则beta值为1减去alpha的值
	g_dBetaValue = (1.0 - g_dAlphaValue);

	//根据alpha和beta值进行线性混合
	addWeighted(g_srcImage1, g_dAlphaValue, g_srcImage2, g_dBetaValue,100 , g_dstImage);
	printf("g_dAlphaValue: %f\n", g_dAlphaValue);
	// 显示效果图
	imshow(WINDOW_NAME, g_dstImage);
}




// 创建滑动条
/*
	createTrackbar函数用于创建一个可以调整数值的滑动条（常常也被称作轨迹条），并将滑动条附加到指定的窗口上，使用起来很方便。需要记住，它往往会和一个回调函数配合起来使用。
	先看下它的函数原型，如下。
	c++: int createTrackbar(conststring& trackbarname, conststring& winname,
	                        int* value, int count, TrackbarCallback onChange=0, void* userdata=0);
	*第一个参数，const string&类型的trackbarname,轨迹条的名字，用来代表我们创建的轨迹条。
	*第二个参数，const string&类型的winname,窗口的名字，表示这个轨迹条会依附到那个窗口上，即对应namedWindow（）创建窗口时填的某一个窗口名。
	*第三个参数，int* 类型的value，一个指向整型的指针，表示滑块的位置。在创建时，滑块的初始位置就是该变量当前的值。
	*第四个参数，int 类型的count，表示滑块可以达到的最大位置的值。滑块的最小位置始终为0.
	*第五个参数，TrackbarCallback类型的onChange，它有默认值0.这时一个指向回调函数的指针，每次滑块位置改变时，这个函数都会及逆行回调。并且这个函数的原型必须为void XXXX(int， void*)；，
					其中第一个参数是轨迹条的位置，第二个参数是用户数据（看下面的第六个参数）。如果回调是NULL指针，则表示没有回调函数的调用，仅第三个参数value有变化。
	*第六个参数，void*类型的userdata，也有默认值0。这个参数是用户传给回调函数的数据，用来处理轨迹条事件。如果使用的第三个参数value实参是全局变量的话，完全可以不去管这个userdata参数。
*/
int main2()
{
	//加载图像（两图像的尺寸需相同）
	g_srcImage1 = imread("700-700狂三1.jpeg");
	g_srcImage2 = imread("700-700狂三2.jpeg");

	if (!g_srcImage1.data) { printf("读取第一幅图片错误，请确定目录下是否有imread函数指定图片存在！\n"); return -1; }
	if (!g_srcImage2.data) { printf("读取第二幅图片错误，请确定目录下是否有imread函数指定图片存在！\n"); return -1; }


	// 设置滑动条初值为70
	g_nAlphaValueSlider = 70;

	//创建窗体
	namedWindow(WINDOW_NAME, WINDOW_NORMAL);

	
	//在创建的窗体中创建一个滑动条控件
	createTrackbar("透明度", WINDOW_NAME, &g_nAlphaValueSlider, g_nMaxAlphaValue, on_Trackbar);

	////结果在回调函数中显示
	on_Trackbar(g_nAlphaValueSlider, 0);

	// 获取当前轨迹条的位置：getTrackbarPos()函数
	printf("当前轨迹条位置%d", getTrackbarPos("透明度", WINDOW_NAME));

	//按任意键退
	waitKey(0);

	return 0;
}