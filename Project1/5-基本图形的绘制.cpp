#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

#define WINDOW_WIDTH 600 // ���崰�ڴ�С�ĺ�
#define WINDOW_NAME1 "[����ͼ1]"
#define WINDOW_NAME2 "[����ͼ2]"
#define WINDOW_NAME3 "[����ͼ3]"



// �Զ���Ļ��ƺ���,ʵ���˻��Ʋ�ͬ�Ƕȡ���ͬ�ߴ����Բ
void DrawEllipse(Mat img, double angle)
{
	int thickness = 2;
	int lineType = 8;

	ellipse(img,
		Point(WINDOW_WIDTH / 2, WINDOW_WIDTH / 2), // ��Բ����
		Size(WINDOW_WIDTH/4, WINDOW_WIDTH/16), // ��Сλ�ھ�����
		angle, // ��ת�Ƕ�
		0, // ��չ���ȴ�0�ȵ�360��
		360,
		Scalar(255, 129, 0),
		thickness,
		lineType);
}



// �Զ���Ļ��ƺ�����ʵ����ʵ��Բ�Ļ���
void DrawFilledCircle(Mat img, Point center)
{
	int thickness = -1;
	int lineType = 8;

	circle(img,
		center, // Բ�ĵ�
		WINDOW_WIDTH / 32, // Բ�뾶
		Scalar(0, 0, 255), // ��ɫ��BGR�ĸ�ʽΪ��ɫ
		thickness, // �ߴ�-1�� ʵ��
		lineType
	);
}

// �Զ���Ļ��ƺ�����ʵ����͹����εĻ���
void DrawPolygon(Mat img)
{
	int lineType = 8;

	// ����һЩ��
}

// �Զ���Ļ��ƺ�����ʵ�����ߵĻ���
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
	// �����հ׵�Matͼ��
	Mat atomImage = Mat::zeros(WINDOW_WIDTH, WINDOW_WIDTH, CV_8UC3);
	Mat rookImage = Mat::zeros(WINDOW_WIDTH, WINDOW_WIDTH, CV_8UC3);

	// ���ƻ�ѧ�е�ԭ��ʾ��ͼ

	//[1.1]�Ȼ��Ƴ���Բ
	DrawEllipse(atomImage, 90);
	DrawEllipse(atomImage, 0);
	DrawEllipse(atomImage, 45);
	DrawEllipse(atomImage, -45);

	//[1.2]�ڻ���Բ��
	DrawFilledCircle(atomImage, Point(WINDOW_WIDTH / 2, WINDOW_WIDTH / 2));

	//�������ͼ
	//[2.1]�Ȼ��Ƴ����ͼ
	DrawPolygon(rookImage);

	//[2.2]���ƾ���
	rectangle(rookImage,
		Point(0, 7 * WINDOW_WIDTH / 8),
		Point(WINDOW_WIDTH, WINDOW_WIDTH),
		Scalar(0, 255, 255),
		-1,
		8);

	//[2.3]����һЩ�߶�
	DrawLine(rookImage, Point(0, 15 * WINDOW_WIDTH / 16),
		Point(WINDOW_WIDTH, 15 * WINDOW_WIDTH / 16));
	DrawLine(rookImage, Point(WINDOW_WIDTH / 4, 7 * WINDOW_WIDTH / 16),
		Point(WINDOW_WIDTH / 4, WINDOW_WIDTH));
	DrawLine(rookImage, Point(WINDOW_WIDTH/2, 7 * WINDOW_WIDTH / 16),
		Point(WINDOW_WIDTH/2, 15 * WINDOW_WIDTH));
	DrawLine(rookImage, Point(3*WINDOW_WIDTH/4, 7 * WINDOW_WIDTH / 16),
		Point(3*WINDOW_WIDTH/4, WINDOW_WIDTH / 16));

	// ��ʾ���Ƴ���ͼ��
	imshow(WINDOW_NAME1, atomImage);
	moveWindow(WINDOW_NAME1, 0, 200);
	imshow(WINDOW_NAME2, rookImage);
	moveWindow(WINDOW_NAME2, WINDOW_WIDTH, 200);

	waitKey(0);
	return(0);
}