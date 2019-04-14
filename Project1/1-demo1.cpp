#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>
using namespace cv;
using namespace std;

// 腐蚀操作
int a(cv::Mat srcImage)
{
	// Mat srcImage = imread("1.jpg", 0);
	imshow("[原图]腐蚀操作", srcImage);
	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
	Mat dstImage;
	erode(srcImage, dstImage, element);
	//namedWindow("[效果图]腐蚀操作", WINDOW_NORMAL);
	imwrite("Scanny腐蚀.jpg", dstImage);
	//imshow("[效果图]腐蚀操作", dstImage);
	//waitKey(2000);

	return 0;
}

// 图像模糊
int b()
{
	Mat srcImage = imread("1.jpg", 0);

	Mat dstImage;
	blur(srcImage, dstImage, Size(15, 15));

	namedWindow("均值滤波", WINDOW_NORMAL);
	imshow("均值滤波", dstImage);
	waitKey(0);
}

// Canny边缘检测
cv::Mat c()
{
	Mat srcImage = imread("1.jpg");

	Mat dstImage, edge, grayImage; // 参数定义
	// 创建与src同类型和大小的矩阵(dst)
	dstImage.create(srcImage.size(), srcImage.type());

	// 将原图像转换为灰度图像
	cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);

	// 先使用3×3内核来降噪
	blur(grayImage, edge, Size(3, 3));

	// 运行Canny算子
	Canny(edge, edge, 3, 9, 3);


	namedWindow("Canny边缘检测", WINDOW_NORMAL);
	imshow("Canny边缘检测", edge);
	waitKey(2000);
	return edge;
}

// 读取当前帧
int readVideoFrame()
{
	VideoCapture capture("微视频.wmv");
	// 循环显示每一帧
	while (1)
	{
		Mat frame;
		capture >> frame; // 读取当前帧
		imshow("读取视频", frame); // 显示当前帧
		waitKey(1); // 延迟30ms
	}
	return 0;
}

// 调用摄像头采集图像
int readCamera()
{
	VideoCapture capture(0);

	while (1)
	{
		Mat frame;
		capture >> frame;
		imshow("读取视频", frame);
		waitKey(30);
	}

	return 0;
}

// 调用摄像头采集图像，获得canny边缘检测并高斯模糊
int videoCannyGuss()
{
	VideoCapture capture;
	capture.open(0);
	Mat edges;

	while (1)
	{
		Mat frame;
		capture >> frame;
		// 将原图像转换为灰度图像
		cvtColor(frame, edges, COLOR_BGR2GRAY); // 转化BGR彩色图为灰度图
		// 使用3×3内核来降噪(2×3+1=7)
		blur(edges, edges, Size(7, 7)); // 进行模糊
		// 进行canny边缘检测并显示
		Canny(edges, edges, 0, 30, 3);
		imshow("被canny后的视频", edges); // 显示经过处理后的当前帧
		if (waitKey(30) >= 0) break; // 延时30ms
	}

	return 0;
}

// 
void setAlphaMat(Mat &mat)
{
	for (int i = 0; i < mat.rows; ++i) {
		for (int j = 0; j < mat.cols; ++j) {
			Vec4b&rgba = mat.at<Vec4b>(i, j);
			rgba[0] = UCHAR_MAX;
			rgba[1] = saturate_cast<uchar>(( float(mat.cols - j)) / ((float)mat.cols) *UCHAR_MAX);
			rgba[2] = saturate_cast<uchar>(( float(mat.rows - i)) / ((float)mat.rows) *UCHAR_MAX);
			rgba[3] = saturate_cast<uchar>(0.5 * (rgba[1] + rgba[2]));
		}
	}
}

int createAlphaMat()
{
	// 创建带Alpha通道的Mat
	Mat mat(480, 640, CV_8UC4);
	setAlphaMat(mat);

	vector<int>compression_params;
	//此句代码的OpenCV2版为：
	//compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION)；
	//此句代码的OpenCV3版为:
	compression_params.push_back(IMWRITE_PNG_COMPRESSION);
	compression_params.push_back(9);

	try {
		imwrite("透明Alpha值图.png", mat, compression_params);
		imshow("生成的PNG图", mat);
		fprintf(stdout, "PNG图片文件支持的alpha数据保存完毕~\n可以在工程目录下查看由imwrite函数生成的图片\n");
		waitKey(0);
	}
	catch (runtime_error& ex) {
		fprintf(stderr, "图像转换成PNG格式发生错误： %s\n", ex.what());
		return 1;
	}

	return 0;
}


int main1()
{
	//------------【一、图像的载入和显示】----------------
	Mat girl = imread("girl.jpg");
	namedWindow("【1】初音");
	imshow("【1】初音",girl);

	//------------【二、初级图像混合】---------------------
	Mat image = imread("dota.jpg", 199);
	Mat logo = imread("dota_loge.jpg");

	//载入后先显示
	namedWindow("【2】原画图");
	imshow("【2】原画图", image);

	namedWindow("【3】logo图");
	imshow("【3】logo图", logo);

	// 定义一个Mat类型，用于存放，图像的ROI
	Mat imageROI;
	// 方法一
	//imageROI = image(Rect(800, 350, logo.cols, logo.rows));
	//方法二
	imageROI = image(Range(350,350+logo.rows), Range(800, 800+logo.cols));

	//将logo加到原图上
	addWeighted(imageROI, 0.5, logo, 0.3, 0., imageROI);

	//显示结果
	namedWindow("【4】原画+logo图");
	imshow("【4】原画+logo图", image);


	//---------------【三、图像的输出】---------------------
	imwrite("由imWrite生成的图片.jpg", image);
	waitKey();

	return 0;




}