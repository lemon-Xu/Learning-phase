#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>
using namespace cv;
using namespace std;

// ��ʴ����
int a(cv::Mat srcImage)
{
	// Mat srcImage = imread("1.jpg", 0);
	imshow("[ԭͼ]��ʴ����", srcImage);
	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
	Mat dstImage;
	erode(srcImage, dstImage, element);
	//namedWindow("[Ч��ͼ]��ʴ����", WINDOW_NORMAL);
	imwrite("Scanny��ʴ.jpg", dstImage);
	//imshow("[Ч��ͼ]��ʴ����", dstImage);
	//waitKey(2000);

	return 0;
}

// ͼ��ģ��
int b()
{
	Mat srcImage = imread("1.jpg", 0);

	Mat dstImage;
	blur(srcImage, dstImage, Size(15, 15));

	namedWindow("��ֵ�˲�", WINDOW_NORMAL);
	imshow("��ֵ�˲�", dstImage);
	waitKey(0);
}

// Canny��Ե���
cv::Mat c()
{
	Mat srcImage = imread("1.jpg");

	Mat dstImage, edge, grayImage; // ��������
	// ������srcͬ���ͺʹ�С�ľ���(dst)
	dstImage.create(srcImage.size(), srcImage.type());

	// ��ԭͼ��ת��Ϊ�Ҷ�ͼ��
	cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);

	// ��ʹ��3��3�ں�������
	blur(grayImage, edge, Size(3, 3));

	// ����Canny����
	Canny(edge, edge, 3, 9, 3);


	namedWindow("Canny��Ե���", WINDOW_NORMAL);
	imshow("Canny��Ե���", edge);
	waitKey(2000);
	return edge;
}

// ��ȡ��ǰ֡
int readVideoFrame()
{
	VideoCapture capture("΢��Ƶ.wmv");
	// ѭ����ʾÿһ֡
	while (1)
	{
		Mat frame;
		capture >> frame; // ��ȡ��ǰ֡
		imshow("��ȡ��Ƶ", frame); // ��ʾ��ǰ֡
		waitKey(1); // �ӳ�30ms
	}
	return 0;
}

// ��������ͷ�ɼ�ͼ��
int readCamera()
{
	VideoCapture capture(0);

	while (1)
	{
		Mat frame;
		capture >> frame;
		imshow("��ȡ��Ƶ", frame);
		waitKey(30);
	}

	return 0;
}

// ��������ͷ�ɼ�ͼ�񣬻��canny��Ե��Ⲣ��˹ģ��
int videoCannyGuss()
{
	VideoCapture capture;
	capture.open(0);
	Mat edges;

	while (1)
	{
		Mat frame;
		capture >> frame;
		// ��ԭͼ��ת��Ϊ�Ҷ�ͼ��
		cvtColor(frame, edges, COLOR_BGR2GRAY); // ת��BGR��ɫͼΪ�Ҷ�ͼ
		// ʹ��3��3�ں�������(2��3+1=7)
		blur(edges, edges, Size(7, 7)); // ����ģ��
		// ����canny��Ե��Ⲣ��ʾ
		Canny(edges, edges, 0, 30, 3);
		imshow("��canny�����Ƶ", edges); // ��ʾ���������ĵ�ǰ֡
		if (waitKey(30) >= 0) break; // ��ʱ30ms
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
	// ������Alphaͨ����Mat
	Mat mat(480, 640, CV_8UC4);
	setAlphaMat(mat);

	vector<int>compression_params;
	//�˾�����OpenCV2��Ϊ��
	//compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION)��
	//�˾�����OpenCV3��Ϊ:
	compression_params.push_back(IMWRITE_PNG_COMPRESSION);
	compression_params.push_back(9);

	try {
		imwrite("͸��Alphaֵͼ.png", mat, compression_params);
		imshow("���ɵ�PNGͼ", mat);
		fprintf(stdout, "PNGͼƬ�ļ�֧�ֵ�alpha���ݱ������~\n�����ڹ���Ŀ¼�²鿴��imwrite�������ɵ�ͼƬ\n");
		waitKey(0);
	}
	catch (runtime_error& ex) {
		fprintf(stderr, "ͼ��ת����PNG��ʽ�������� %s\n", ex.what());
		return 1;
	}

	return 0;
}


int main1()
{
	//------------��һ��ͼ����������ʾ��----------------
	Mat girl = imread("girl.jpg");
	namedWindow("��1������");
	imshow("��1������",girl);

	//------------����������ͼ���ϡ�---------------------
	Mat image = imread("dota.jpg", 199);
	Mat logo = imread("dota_loge.jpg");

	//���������ʾ
	namedWindow("��2��ԭ��ͼ");
	imshow("��2��ԭ��ͼ", image);

	namedWindow("��3��logoͼ");
	imshow("��3��logoͼ", logo);

	// ����һ��Mat���ͣ����ڴ�ţ�ͼ���ROI
	Mat imageROI;
	// ����һ
	//imageROI = image(Rect(800, 350, logo.cols, logo.rows));
	//������
	imageROI = image(Range(350,350+logo.rows), Range(800, 800+logo.cols));

	//��logo�ӵ�ԭͼ��
	addWeighted(imageROI, 0.5, logo, 0.3, 0., imageROI);

	//��ʾ���
	namedWindow("��4��ԭ��+logoͼ");
	imshow("��4��ԭ��+logoͼ", image);


	//---------------������ͼ��������---------------------
	imwrite("��imWrite���ɵ�ͼƬ.jpg", image);
	waitKey();

	return 0;




}