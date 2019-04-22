#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

Mat g_srcImage, g_dstImage; // ԭʼͼ��Ч��ͼ
int g_nTrackbarNumer = 0; // 0��ʾ��ʴerode�� 1��ʾ����dilate
int g_nStructElemnetSize = 3; // �ṹԪ�أ��ں˾��󣩵ĳߴ�



void Process(); // ���ͺ͸�ʴ�Ĵ�����
void on_TrackbarNumChange(int, void *); // �ص�����
void on_ElementSizeChange(int, void *); // �ص�����


int main()
{
	system("color 5E");

	g_srcImage = imread("img/700-700����1.jpeg", 1);
	if (g_srcImage.empty()) { printf("��ȡsrcImage����~!"); return false; }

	imshow("ԭʼͼ", g_srcImage);
	imshow("��Ч��ͼ��", g_srcImage);
	// �����켣��
	createTrackbar("��ʴ/����","��Ч��ͼ��",&g_nTrackbarNumer,1,on_TrackbarNumChange);
	createTrackbar("�ں˳ߴ�","��Ч��ͼ��", &g_nStructElemnetSize, 21, on_ElementSizeChange);

	// ��ѯ��ȡ������Ϣ������q���������˳�
	while (char(waitKey(1) != 'q' )) {}
	return 0;
}


void Process()
{
	Mat element = getStructuringElement(MORPH_RECT, Size(2 * g_nStructElemnetSize + 1, 2 * g_nStructElemnetSize + 1), Point(g_nStructElemnetSize, g_nStructElemnetSize));

	if (g_nTrackbarNumer == 0) {
		erode(g_srcImage, g_dstImage, element);
	}
	else {
		dilate(g_srcImage, g_dstImage, element);
	}

	imshow("��Ч��ͼ��", g_dstImage);
}


void on_TrackbarNumChange(int, void *)
{
	// ��ʴ������֮��Ч���Ѿ��л����ص��������������һ��Process������ʹ�ı���Ч��������Ч����ʾ����
	Process();
}

void on_ElementSizeChange(int, void *)
{
	Process();
}