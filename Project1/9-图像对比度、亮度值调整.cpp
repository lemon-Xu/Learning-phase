#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;

/* ��������
	�����˽�һ�����ӵĸ��һ���ͼ�������Ӷ���һ��������������һ����������ͼ�񣬲��������ͼ�����������ӵ�һ����ʽ��
		g(x) = h(f(x)) ���� g(x) = h(f0(x).......fn(x))
	�����������ͼ�����ȺͶԱȶȵĵ�����������ʵ����ͼ��������бȽϼ򵥵�һ�֡������(pointoperators)���������һ���ص㣺����������������ֵ����ʱ�ɼ���ĳЩȫ����Ϣ�����������������Ӧ���������ֵ���������Ӱ������ȣ�brightness���ͶԱȶ�(contrast)��������ɫУ��(colorcorrection)�ͱ任(transformations).
	������õĵ����(����˵������)�ǳ���һ����������Ӧ�Աȶȵĵ��ڣ��Լ�����һ����������Ӧ����ֵ�ĵ��ڣ�����˾����:
		g(x) = a * f(x) + b
			����f(x)��ʾԴͼ�����ء�
			����g(x)��ʾ���ͼ������
			����a(��Ҫ���� a>0 )����Ϊ����(gain),��������������ͼ��ĶԱȶȡ�
			����bͨ������Ϊƫ�ã�bias������������������ͼ������ȡ�
		���Ǹ�д���ʽ��:
			g(i,j) = a*f(i,j) + b
		����,i��j��ʾ����λ�ڵ�i�к͵�j�У����ʽ�ӿ���������Ϊ������OpenCV�п���ͼ������ȺͶԱȶȵ����۹�ʽ��
*/

/*	ʵ�ֶԱȶȺ����ȸı�
	��Ϊ�˷���ͼ���ÿһ�����أ�ʹ���������﷨��image.at<Vec3b>(y,x)[c].
		���У�y���������ڵ��У�x���������ڵ��У�c��R��G��B����Ӧ0��1��2������֮һ��
	����Ϊ���������ܻᳬ������ȡֵ��Χ����������������Ƿ�����������Ǹ������Ļ���������Ҫ��saturate_cast�Խ������ת������ȷ����λ��Чֵ��
	�������aҲ���ǶԱȶȣ�һ��Ϊ�˹۲��Ч��������ȡֵλ0.0��3.0�ĸ���ȶ�ֵ��nContrastValue������Ϊ0��300֮���������������ʽ���г���һ��0.01�����������˹켣����300����ͬȡֵ�ı仯�������Ϊʲô��ʽ���У�����saturate_cast<uchar>((g_cContrastValue*0.01)*(image.at<Vec3b>(y,x)[c])+g_nBrightValue)�е�g_nContrastValue*0.01)


*/

// ȫ�ֺ�������
static void on_ContrastAndBright(int, void *);
static void ShowHelpText();

// ȫ�ֱ�������
int g_nContrastValue; // �Աȶ�ֵ
int g_nBrightValue; // ����ֵ
Mat g_srcImage, g_dstImage;

int main()
{
	g_srcImage = imread("img/700-700����1.jpeg");
	if (g_srcImage.empty()) { printf("��ȡͼ��ʧ��"); return -1; }

	g_dstImage = Mat::zeros(g_srcImage.size(), g_srcImage.type());
	
	// �趨�ԱȶȺ����ȵĳ�ֵ
	g_nContrastValue = 80;
	g_nBrightValue = 80;

	namedWindow("��Ч��ͼ���ڡ�", 1);

	createTrackbar("�Աȶ�", "��Ч��ͼ���ڡ�", &g_nContrastValue, 300, on_ContrastAndBright);
	createTrackbar("��  ��","��Ч��ͼ���ڡ�", &g_nBrightValue, 200, on_ContrastAndBright);

	// ���лص�������ʼ��
	on_ContrastAndBright(g_nContrastValue, 0);
	on_ContrastAndBright(g_nBrightValue, 0);

	// ���¡�q����ʱ�������˳�
	while (char(waitKey(1)) != 'q') {}
	return 0;

}



//�ı�ͼ��ԱȶȺ�����ֵ�Ļص�����
static void on_ContrastAndBright(int, void*)
{
	// ��������
	namedWindow("��ԭʼͼ���ڡ�", 1);

	// ����forѭ����ִ������g_dstImage(i,j) = a*g_srcImage(i ,j) + b
	for (int y = 0; y < g_srcImage.rows; y++)
	{
		for (int x = 0; x < g_srcImage.cols; x++)
		{
			for (int c = 0; c < 3; c++)
			{
				g_dstImage.at<Vec3b>(y, x)[c] = saturate_cast<uchar>((g_nContrastValue * 0.01) * (g_srcImage.at<Vec3b>(y,x)[c] + g_nBrightValue));
			}
		}
	}
	
	// ��ʾͼ��
	imshow("��ԭʼͼ���ڡ�", g_srcImage);
	imshow("��Ч��ͼ���ڡ�", g_dstImage);

}