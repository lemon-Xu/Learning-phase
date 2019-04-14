#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <vector>

using namespace cv;

// 1-Mat��(����������ݽṹ)
/*
	1.Mat��������һ��ͼ��������,ͬʱҲ��һ��ͨ�õľ�����.
	2.�������ֶ�Ϊ�俪�ٿռ�,Ҳ�����ڲ���Ҫ��ʱ�����������Ŀռ��ͷ�
	3.Mat��һ����,���������ݲ������:
		1.����ͷ:����ߴ�,�洢����,�洢��ַ�ȵ����������Ϣ(����ͷ�ĳߴ��ǳ���ֵ)
		2.ָ��洢��������ֵ���ݿ��ָ��.
	4.��ֵ������͸��ƹ��캯��ֻ�Ḵ����Ϣͷ��ֻ�����ݿ�ָ���ֵ,���ǲ��������ĸ���һ������
		(Ϊ�����ܺͱ����ڴ��������).�����ж���������ͬһ��ֵ����,�ı�����һ�������иı������Ķ���Ŀ���.
	5.ʹ��clone()����copyTo()����㸴��һ��ͼ��ľ���.
	6.ǰ���Ѿ�֪��һ��������Ա����Mat��������,��ô���һ��ʹ���������Ķ���,�����������.
		ͨ�����ü���������ʵ��.��������ʲôʱ����һ��Mat�������Ϣͷ,�������Ӿ�������ô���.
		��֮,��һ��ͷ���ͷ�֮��,�����������һ;������ֵΪ��,����ᱻ����.
*/
int Mat3()
{
	// 1-Mat�ĳ�ʼ�������
	Mat pic(10, 3, CV_8SC3, Scalar(0, 0, 1));

	std::cout << "leonardo" << std::endl;
	std::cout << cv::format(pic, cv::Formatter::FMT_C) << std::endl;
	cv::imshow("Test", pic);
	cv::waitKey();
	// getchar():


	// 2-��ֵ��Ϣͷ
	Mat A, C; // ��������Ϣͷ����
	A = imread("700-700����1.jpeg",1); // ����Ϊ���󿪱��ڴ�
	if (A.empty())
		return -2;
	imshow("�ڴ濪�ٵ�ͼ��A", A);
	Mat B(A); // ʹ�ÿ������캯��
	imshow("�������캯��B", B);
	C = A; // ��ֵ�����
	imshow("��ֵ�����ͼ��C", C);

	// 3-���ǿ��Դ���ֻ���ò������ݵ���Ϣͷ,������Ҫ����һ������Ȥ����(ROI)ֻ��Ҫ���������߽���Ϣ����Ϣͷ
	Mat D(A, Rect(10, 10, 100, 100)  ); // ʹ�þ��ν綨
	//Mat E = A(Range:all(), Range(1, 3)); // ���к������綨
	imshow("�߽�綨D", D);

	//4-���
	Mat F = A.clone();
	Mat G;
	A.copyTo(G);

	//5-empty()���� �ж��Ƿ�Mat�ǿյ�Ԫ��
	Mat E;
	printf("E�ǿյ�,E.empty():%d", E.empty());

	//6-channels()���� ����һ��Mat�����ͨ��
	Mat H = imread("700-700����1.jpeg", 0);
	printf("\nA(��ɫ)��ͨ����:A.channels():%d\nH(��ɫ)��ͨ����:H.channels():%d", A.channels(), H.channels());
	
	//7-Scalar��(��ɫ��ʾ)
	/*
		1.Scalar��ԴͷΪscalar_��,typedef Scalar_<double> cv::Scalar���Ϊscalar��
		2.Scalar��ʾ����4��Ԫ�ص�����,һ����OpenCV�б�������������ֵ
		һ����÷�����Scalar(a,b,c)��ʾһ����ɫ����.ע��:˳��ֱ�����,��,��.
	*/
	waitKey(0);
	return 0;
}


// 2-��������������ݽṹ
int main4()
{
	// 1.����������ά��
	Point2f p(6, 2);
	std::cout << "[��ά��] p = " << p << ";\n" << std::endl;

	// 2.����������ά��
	Point3f p3f(8, 2, 0);
	std::cout << "[��ά��] p3f = " << p3f << ";\n" << std::endl;

	// 3.������������Mat��std::vector
	std::vector<float> v;
	v.push_back(3);
	v.push_back(5);
	v.push_back(7);

	std::cout << "[����Mat��vector] shortvec = " << Mat(v) << ";\n" << std::endl;

	// 4.��������std::vector��
	std::vector<Point2f> points(20);
	for (size_t i =0; i < points.size(); ++i)
	{
		points[i] = Point2f((float)(i * 5), (float)(i % 7));
	}
	std::cout << "[��ά������]points = " << points << ";";

	// 5.����ı�ʾ:Rect��

	// 6.��ɫ�ռ�ת��:cvtColor()����

	return 0;
}