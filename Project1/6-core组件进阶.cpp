#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void colorReduce1(Mat& inputImage, Mat& outputImage, int div);
void colorReduce2(Mat& inputImage, Mat& outputImage, int div);
void colorReduce3(Mat& inputImage, Mat& outputImage, int div);

// 1-��ɫ�ռ�����
/*
	������ɫ�о��д����Եĺ�С�Ĳ���,�����Դﵽͬ����Ч��,ȴ������㷨�������Ӱ��.
	����:��������ɫ�ռ�ֵ����(����)ĳ������ֵ,�Ի�ý��ٵ���ɫ��.
	��������ֵ,�����ڱ���,ֻҪֻ��Ҫ��ȡ����,����Ҫ��������������.
*/

// 2-LUT����:Look up table����
/*
	���������ᵽ��Look up table����,OpenCV�ٷ��ĵ���ǿ���Ƽ�����ʹ��һ��ԭ��ΪoperationsOnArrays:LUT()<lut>�ĺ�������.
	��������������ͼ��Ԫ�ز��ҡ�ɨ�������ͼ��
*/
int main()
{
	//����ԭʼͼ����ʾ
	Mat srcImage = imread("700-700����1.jpeg");
	imshow("ԭʼͼ��", srcImage);

	//��ԭʼͼ�Ĳ������������Ч��ͼ
	Mat dstImage;
	dstImage.create(srcImage.rows, srcImage.cols, srcImage.type()); // Ч��ͼ�Ĵ�С��������ԭͼƬ��ͬ

	//��¼��ʼʱ��
	double time0 = static_cast<double>(getTickCount());
	
	//������ɫ�ռ���������
	colorReduce3(srcImage, dstImage, 32);

	//��������ʱ�䲢���
	time0 = ((double)getTickCount() - time0) / getTickFrequency();
	cout << "�˷�������ʱ��Ϊ: " << time0 << "��" << endl; //�������ʱ��

	//��ʾЧ��ͼ
	imshow("Ч��ͼ", dstImage);
	waitKey(0);

}


//������һ����ָ���������  0.0483416�� 0.00205177��  0.00208915��
/*
	1.ÿ�е�����ֵ���������õ���
		������ͨ���� = ÿһ��Ԫ�صĸ���
	2.Ϊ�˼�ָ�����㣬Mat���ṩ��ptr�������Եõ�ͼ�������е��׵�ַ��ptr��һ��ģ�庯���������ص�i�е��׵�ַ��
		uchar* data = outputImage.ptr<uchar>(i); // ��ȡ��i�е��׵�ַ
	3.��˫��ѭ���ڲ����Ǿ䴦�����صĴ��룬���ǿ��Ե�Ч��ʹ��ָ�������һ���ƶ�����һ�С�
		*data++ = *data / div * div + div / 2;
*/
void colorReduce1(Mat& inputImage, Mat& outputImage, int div)
{
	// ����׼��
	outputImage = inputImage.clone(); // ����ʵ�ε���ʱ����
	int rowNumber = outputImage.rows; // ����
	int colNumber = outputImage.cols * outputImage.channels(); //������ͨ����=ÿһ��Ԫ�صĸ���

	//˫��ѭ�����������е�����ֵ
	for (int i = 0; i < rowNumber; i++)
	{
		uchar* data = outputImage.ptr<uchar>(i); // ��ȡ��i�е��׵�ַ
		for (int j = 0;j < colNumber;j++)
		{
			data[j] = data[j] / div * div + div / 2;
		}
	}
}
//�����������õ�������������  0.00271518�� 0.00282128��  0.00292172��
/*
	�ڵ������У���������Ҫ���Ľ����ǻ��ͼ������begin��end��Ȼ�����ӵ���ֱ����begin��end��
	��*����������ڵ���ָ��ǰ�����ɷ��ʵ�ǰָ������ݡ������ָ��ֱ�ӷ��ʿ��ܳ���Խ�����⣬�����������Ƿǳ���ȫ�ķ�����
*/
void colorReduce2(Mat& inputImage, Mat& outputImage, int div)
{
	//����׼��
	outputImage = inputImage.clone();
	//��ȡ������
	Mat_<Vec3b>::iterator it = outputImage.begin<Vec3b>(); //��ʼλ�õĵ�����
	Mat_<Vec3b>::iterator itend = outputImage.end<Vec3b>(); //��ֹλ�õĵ�����

	//��ȡ��ɫͼ������
	for (;it != itend; ++it)
	{
		//��ʼ����ÿ������
		(*it)[0] = (*it)[0] / div * div + div / 2;
		(*it)[1] = (*it)[1] / div * div + div / 2;
		(*it)[2] = (*it)[2] / div * div + div / 2;

	}


}


//������������̬��ַ����  0.0033986�� 0.00321698��  0.00337179��
/*
	�����ַ���Ϊ�ö�̬��ַ�������������ء�����ʹ�ö�̬��ַ�������at������colorReduce�����Ĵ��롣
	1.��Ա����at(int y, int x)����������ȡͼ��Ԫ�أ����Ǳ����ڱ�����֪��ͼ����������ͣ�at������������κ��������ͽ���ת��.
	2.����һ��������ɫͼ���Mat���᷵��һ��������8λ����ɵ�������OpenCV�������͵���������λVec3b����������unsigned char��ɵ�����
	image.at<Vec3b>(row ,col)[channel] = value
*/
void colorReduce3(Mat& inputImage, Mat& outputImage, int div)
{
	//����׼��
	outputImage = inputImage.clone();
	int rowNumber = outputImage.rows;
	int colNumber = outputImage.cols;

	//��ȡ��ɫͼ������
	for (int i = 0; i < rowNumber; i++)
	{
		for (int j = 0; j < colNumber; j++)
		{
			outputImage.at<Vec3b>(i, j)[0] = outputImage.at<Vec3b>(i, j)[0] / div * div + div / 2; //��ɫͨ��
			outputImage.at<Vec3b>(i, j)[1] = outputImage.at<Vec3b>(i, j)[1] / div * div + div / 2; //��ɫͨ��
			outputImage.at<Vec3b>(i, j)[2] = outputImage.at<Vec3b>(i, j)[2] / div * div + div / 2; //��ɫͨ��
		}
	}
}