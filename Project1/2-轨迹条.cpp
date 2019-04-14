#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>
using namespace cv;


#define WINDOW_NAME "�����Ի��ʾ����" //Ϊ���ڱ��ⶨ��ĺ�

//ȫ�ֱ�������
const int g_nMaxAlphaValue = 100; // Alphaֵ�����ֵ
int g_nAlphaValueSlider; // ��������Ӧ�ı���
double g_dAlphaValue;
double g_dBetaValue;

// �����洢ͼ��ı���
Mat g_srcImage1;
Mat g_srcImage2;
Mat g_dstImage;

// ----------��on_Trackbar()������---------
// ��������Ӧ�������Ļص������� �ı�ͼƬAlphaͨ����ֵ
//addWeighted() ���Ի�Ϻ�������Ȩ����
/*
	����һ��mat     src1 ��һ��ͼ��������
	��������double  alpha ��һ��ͼ��Ȩ��  
	��������mat		src2 �ڶ���ͼ�������� 
	�����ģ�double  beta �ڶ���ͼ��Ȩ��   
	�����壺double  gamma ���ȱ�׼ƫ����ڱ�ʾ��ʾ�����ػҶȵľ��ȳ̶ȣ�������ѧ���磬��ֵԽС˵�����ػҶȷֲ�Խ���У�Խ��˵�����ػҶȷֲ�Խ��ɢ��
	��������mat      ���ڴ������ͼ��������

	������ʽ������
	dst = src1 * alpha + src2 * beta + gamma;
*/
void on_Trackbar(int, void*)
{
	//�����ǰalphaֵ�൱�����ֵ�ı���
	g_dAlphaValue = (double)g_nAlphaValueSlider / g_nMaxAlphaValue;
	//��betaֵΪ1��ȥalpha��ֵ
	g_dBetaValue = (1.0 - g_dAlphaValue);

	//����alpha��betaֵ�������Ի��
	addWeighted(g_srcImage1, g_dAlphaValue, g_srcImage2, g_dBetaValue,100 , g_dstImage);
	printf("g_dAlphaValue: %f\n", g_dAlphaValue);
	// ��ʾЧ��ͼ
	imshow(WINDOW_NAME, g_dstImage);
}




// ����������
/*
	createTrackbar�������ڴ���һ�����Ե�����ֵ�Ļ�����������Ҳ�������켣�������������������ӵ�ָ���Ĵ����ϣ�ʹ�������ܷ��㡣��Ҫ��ס�����������һ���ص������������ʹ�á�
	�ȿ������ĺ���ԭ�ͣ����¡�
	c++: int createTrackbar(conststring& trackbarname, conststring& winname,
	                        int* value, int count, TrackbarCallback onChange=0, void* userdata=0);
	*��һ��������const string&���͵�trackbarname,�켣�������֣������������Ǵ����Ĺ켣����
	*�ڶ���������const string&���͵�winname,���ڵ����֣���ʾ����켣�����������Ǹ������ϣ�����ӦnamedWindow������������ʱ���ĳһ����������
	*������������int* ���͵�value��һ��ָ�����͵�ָ�룬��ʾ�����λ�á��ڴ���ʱ������ĳ�ʼλ�þ��Ǹñ�����ǰ��ֵ��
	*���ĸ�������int ���͵�count����ʾ������Դﵽ�����λ�õ�ֵ���������Сλ��ʼ��Ϊ0.
	*�����������TrackbarCallback���͵�onChange������Ĭ��ֵ0.��ʱһ��ָ��ص�������ָ�룬ÿ�λ���λ�øı�ʱ������������ἰ���лص����������������ԭ�ͱ���Ϊvoid XXXX(int�� void*)����
					���е�һ�������ǹ켣����λ�ã��ڶ����������û����ݣ�������ĵ�����������������ص���NULLָ�룬���ʾû�лص������ĵ��ã�������������value�б仯��
	*������������void*���͵�userdata��Ҳ��Ĭ��ֵ0������������û������ص����������ݣ���������켣���¼������ʹ�õĵ���������valueʵ����ȫ�ֱ����Ļ�����ȫ���Բ�ȥ�����userdata������
*/
int main2()
{
	//����ͼ����ͼ��ĳߴ�����ͬ��
	g_srcImage1 = imread("700-700����1.jpeg");
	g_srcImage2 = imread("700-700����2.jpeg");

	if (!g_srcImage1.data) { printf("��ȡ��һ��ͼƬ������ȷ��Ŀ¼���Ƿ���imread����ָ��ͼƬ���ڣ�\n"); return -1; }
	if (!g_srcImage2.data) { printf("��ȡ�ڶ���ͼƬ������ȷ��Ŀ¼���Ƿ���imread����ָ��ͼƬ���ڣ�\n"); return -1; }


	// ���û�������ֵΪ70
	g_nAlphaValueSlider = 70;

	//��������
	namedWindow(WINDOW_NAME, WINDOW_NORMAL);

	
	//�ڴ����Ĵ����д���һ���������ؼ�
	createTrackbar("͸����", WINDOW_NAME, &g_nAlphaValueSlider, g_nMaxAlphaValue, on_Trackbar);

	////����ڻص���������ʾ
	on_Trackbar(g_nAlphaValueSlider, 0);

	// ��ȡ��ǰ�켣����λ�ã�getTrackbarPos()����
	printf("��ǰ�켣��λ��%d", getTrackbarPos("͸����", WINDOW_NAME));

	//���������
	waitKey(0);

	return 0;
}