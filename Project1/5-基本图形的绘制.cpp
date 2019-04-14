#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

#define WINDOW_WIDTH 600 // 定义窗口大小的宏
#define WINDOW_NAME1 "[绘制图1]"
#define WINDOW_NAME2 "[绘制图2]"
#define WINDOW_NAME3 "[绘制图3]"



// 自定义的绘制函数,实现了绘制不同角度、相同尺寸的椭圆
void DrawEllipse(Mat img, double angle)
{
	int thickness = 2;
	int lineType = 8;

	ellipse(img,
		Point(WINDOW_WIDTH / 2, WINDOW_WIDTH / 2), // 椭圆中心
		Size(WINDOW_WIDTH/4, WINDOW_WIDTH/16), // 大小位于矩形内
		angle, // 旋转角度
		0, // 扩展弧度从0度到360度
		360,
		Scalar(255, 129, 0),
		thickness,
		lineType);
}



// 自动义的绘制函数，实现了实心圆的绘制
void DrawFilledCircle(Mat img, Point center)
{
	int thickness = -1;
	int lineType = 8;

	circle(img,
		center, // 圆心点
		WINDOW_WIDTH / 32, // 圆半径
		Scalar(0, 0, 255), // 颜色按BGR的格式为红色
		thickness, // 线粗-1， 实心
		lineType
	);
}

// 自定义的绘制函数，实现了凸多边形的绘制
void DrawPolygon(Mat img)
{
	int lineType = 8;

	// 创建一些点
}

// 自定义的绘制函数，实现了线的绘制
void DrawLine(Mat img, Point start, Point end)
{
	int thickness = 2;
	int lineType = 8;
	line(img,
		start,
		end,
		Scalar(0, 0, 0),
		thickness,
		lineType);
}
int main5()
{
	// 创建空白的Mat图像
	Mat atomImage = Mat::zeros(WINDOW_WIDTH, WINDOW_WIDTH, CV_8UC3);
	Mat rookImage = Mat::zeros(WINDOW_WIDTH, WINDOW_WIDTH, CV_8UC3);

	// 绘制化学中的原子示例图

	//[1.1]先绘制出椭圆
	DrawEllipse(atomImage, 90);
	DrawEllipse(atomImage, 0);
	DrawEllipse(atomImage, 45);
	DrawEllipse(atomImage, -45);

	//[1.2]在绘制圆心
	DrawFilledCircle(atomImage, Point(WINDOW_WIDTH / 2, WINDOW_WIDTH / 2));

	//绘制组合图
	//[2.1]先绘制出组合图
	DrawPolygon(rookImage);

	//[2.2]绘制矩形
	rectangle(rookImage,
		Point(0, 7 * WINDOW_WIDTH / 8),
		Point(WINDOW_WIDTH, WINDOW_WIDTH),
		Scalar(0, 255, 255),
		-1,
		8);

	//[2.3]绘制一些线段
	DrawLine(rookImage, Point(0, 15 * WINDOW_WIDTH / 16),
		Point(WINDOW_WIDTH, 15 * WINDOW_WIDTH / 16));
	DrawLine(rookImage, Point(WINDOW_WIDTH / 4, 7 * WINDOW_WIDTH / 16),
		Point(WINDOW_WIDTH / 4, WINDOW_WIDTH));
	DrawLine(rookImage, Point(WINDOW_WIDTH/2, 7 * WINDOW_WIDTH / 16),
		Point(WINDOW_WIDTH/2, 15 * WINDOW_WIDTH));
	DrawLine(rookImage, Point(3*WINDOW_WIDTH/4, 7 * WINDOW_WIDTH / 16),
		Point(3*WINDOW_WIDTH/4, WINDOW_WIDTH / 16));

	// 显示绘制出的图像
	imshow(WINDOW_NAME1, atomImage);
	moveWindow(WINDOW_NAME1, 0, 200);
	imshow(WINDOW_NAME2, rookImage);
	moveWindow(WINDOW_NAME2, WINDOW_WIDTH, 200);

	waitKey(0);
	return(0);
}