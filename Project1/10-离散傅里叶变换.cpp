#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;

/*	��ɢ����Ҷ�任
	��ɢ����Ҷ�任��Discrete Fourier Transform, ��дΪDFT��,��ָ����Ҷ�任��ʱ���Ƶ���϶�������ɢ����ʽ����ʱ���źŵĲ����任Ϊ��ɢʱ�丵��Ҷ�任(DTFT)Ƶ��Ĳ�����
	����ʽ�ϣ��任���ˣ�ʱ���Ƶ���ϣ������������޳��ģ���ʵ�������������ж�Ӧ������Ϊ����ɢ�����źŵ���ֵ���С���ʹ�����޳�����ɢ�ź���DFT��ҲӦ�����侭�������ź��ڽ��б任��
	��ʵ��Ӧ���У�ͨ�����ÿ��ٸ���Ҷ�任����Ч����DFT��
*/

/*	��ɢ����Ҷ�任��ԭ��
	����˵����һ��ͼ��ʹ�ø���Ҷ�任���ǽ����ֽ�����Һ����������֣�Ҳ���ǽ�ͼ��ӿռ���spatial domain��ת����Ƶ��(frequency domain)��
	��һת�������ۻ���Ϊ����һ���������Ա�ʾ�����������Һ����Һ����ĺ͵���ʽ������Ҷ�任����һ�������������ֽ�Ĺ��ߡ�
	��άͼ��ĸ���Ҷ�任�������������ݹ�ʽ����ʾ��
	https://baike.baidu.com/item/%E5%BF%AB%E9%80%9F%E5%82%85%E9%87%8C%E5%8F%B6%E5%8F%98%E6%8D%A2/214957?fr=aladdin
	ʽ��f�ǿռ���spatial domain��ֵ��F��Ƶ��frequency domain��ֵ��ת��֮���Ƶ��ֵ�Ǹ�������ˣ���ʾ����Ҷ�任֮��Ľ����Ҫʹ��ʵ��ͼ��real iamge��������ͼ��(ccomplex image)��
���߷���ͼ��magitude image������λͼ��phase image������ʽ����ʵ�ʵ�ͼ��������У�����ʹ���˷���ͼ����Ϊ����ͼ�������ԭͼ��ļ�������������Ҫ�ļ�����Ϣ��
Ȼ���������ͨ���޸ķ���ͼ�������λͼ��ķ���������޸�ԭ�ռ�ͼ����Ҫʹ���渵��Ҷ�任�õ��޸ĺ�Ŀռ�ͼ�������ͱ���ͬʱ��������ͼ�����λͼ���ˡ�
	��Ƶ�����棬����һ��ͼ�񣬸�Ƶ���ִ�����ͼ���ϸ�ڡ�������Ϣ����Ƶ���ִ�����ͼ���������Ϣ�������һ����ϸ��ͼ��ʹ�õ�ͨ�˲�������ô�˲���Ľ����ֻʣ�������ˡ�
�����źŴ���Ļ���˼������ͨ�ġ����ͼ���ܵ�������ǡ��λ��ĳ���ض��ġ�Ƶ�ʡ���Χ�ڣ������ͨ���˲������ָ�ԭ����ͼ�񡣸���Ҷ�任��ͼ�����п�������ͼ����ǿ��ͼ��ȥ�롢ͼ��ָ�֮��Ե��⡢ͼ��������ȡ��ͼ��ѹ���ȡ�
*/

/*	1-dft()�������
	dft�����������Ƕ�һά���ά����������������������ɢ����Ҷ�任��
	c++: void dft(InputArray src, OutputArray dst, int flags=0, int nonzeroRows=0)
	����һ��������InputArray���͵�src��������󣬿���Ϊʵ������������
	���ڶ���������OutputArray���͵�dst���������ú�����������������ߴ������ȡ���ڱ�ʶ����Ҳ���ǵ���������flags��
	��������������int���͵�flags��ת���ı�ʶ������Ĭ��ֵ0��ȡֵ����Ϊ��
		DFT_INVERSE			��һά���ά�任����Ĭ�ϵ�����任
		DFT_SCALE			���ű�����ʶ��������Ľ��������1/N�������ţ�ͨ������DFT_INVERSEһ��ʹ��
		DFT_ROWS			����������ÿ�н����������ı任���˱�ʶ�������ڴ������ʸ����ʱ�����ڼ�С��Դ��������Щ����������ά���ά�任�ȸ��Ӳ���
		DFT_COMPLEX_OUTPUT	����һά���άʵ��������б任�������Ľ����Ȼ�Ǹ������У���ӵ�и����Ĺ���Գ��ԣ�CCS�������Կ���д��һ��ӵ��ͬ���ߴ��ʵ������
		DFT_REAL_OUTPUT		����һά���ά�������鷴�任�������Ľ��ͨ����һ����С��ͬ�ĸ������������ľ����и����Ĺ���Գ��ԣ�������һ������DFT_COMPLEX_OUTPUT��ʶ�������任�������������ʵ����.
	�����ĸ������� int���͵�nonzeroRows����Ĭ��ֵ0.���˲�����Ϊ����ʱ�������ȡֵΪ��Ҫ�������һ�е�ֵ������C.rows�������������ֻ���������ĵ�һ�������а�������Ԫ�أ�û������DFT_INVERSE��ʶ������
	��ֻ���������ĵ�һ�������а�������Ԫ��(������DET_INVERSE��ʶ��)�������Ļ��������Ϳɶ������н��и���Ч�Ĵ����Խ�ʡʱ�俪����������������ڲ���DFT���������ʱ�ǳ���Ч��
*/

/*	2-����DFT���ųߴ��С��getOptimalDFTSize()����
	getOptimalDFTSize�������ظ��������ߴ�ĸ���Ҷ���ųߴ��С��Ϊ�������ɢ����Ҷ�任�������ٶȣ���Ҫ����ͼ�񣬶�����������٣������������������ĵ���
	c++: int getOptimalDFTSize(int vecsize)
	�˺�����Ψһһ������Ϊint���͵�vecsize�������ߴ磬��ͼƬ��rows��cols��	
*/

/*	3-����ͼ��߽磺copyMakeBorder()����
	copyMakeBorder����������������ͼ��߽硣
	c++: void copyMakeBorder(InputArray src, OutputArray dst, int top, int bottom, int left, int right, int borderType, const Scalar&value=Scalar())
	���ڶ���������OutputArray���͵�dst�����ԴͼƬ��һ���ĳߴ�����ͣ���sizeӦ��ΪSize��src.cols+left+right, src.rows+top+bottom��.
	�����߸�������borderType���͵ģ��߽����ͣ�����ȡֵΪBORDER_CONSTANT���ɲο�borderInterpolate()�õ������ϸ�ڡ�
	���ڰ˸�������const Scalar&���͵�value����Ĭ��ֵScalar()���������ΪĬ��ֵΪ0.��borderTypeȡֵΪBORDER_CONSTANTʱ�����������ʾ�߽�ֵ.
*/

/*	4-�����άʸ���ķ�ֵ��magnitude()����
	magnitude()�������ڼ����άʸ���ķ�ֵ��
	c++: void magnitude(InputArray x, InputArray y, OutputArray magnitude)
	����һ��������InputArray���͵�x����ʾʸ���ĸ�����X����ֵ��Ҳ����ʵ����
	���ڶ���������InputArray���͵�y����ʾʸ���ĸ�����Y����ֵ��Ҳ�����鲿��
	��������������OutputArray���͵�magnitude������ķ�ֵ�����͵�һ������x����ͬ���ĳߴ�����͡�
	ԭ��dst(I) = (x(I)^2 + y(I)^2)^(1/2)

*/

/*	5-������Ȼ������log()����
	log()�����Ĺ����Ǽ���ÿ������Ԫ�ؾ���ֵ����Ȼ������
	c++: void log(InputArray src, OutputArray dst)
	��һ������Ϊ����ͼ�񣬵ڶ�������Ϊ�õ��Ķ���ֵ��
*/

/*	6-�����һ����normalize()����
	normalize()�������ǽ��о����һ����
	c++�� void normalize(InputArray src, OutputArray dst, double alpha=1, double beta=0, int norm_type=NORM_L2, int dtype=-1, InputArray mask=noArray())
	���������ͼ����һ���ĳߴ������
	��������������double���͵�alpha����һ��������ֵ����Ĭ��ֵ1.
	�����ĸ�������double���͵�beta����һ�������Сֵ����Ĭ��ֵ0.
	�������������int���͵�norm_type����һ�����ͣ���NORM_INF��NORM_L1��NORM_L2��NORM_MINMAX�Ȳ�����ѡ����Ĭ��ֵNORM_L2.
	��������������int���͵�dtype����Ĭ��ֵ-1.���˺���ȡ��ֵʱ����������src��ͬ�������ͣ����ߣ�����src��ͬ����ͨ�������Ҵ�ʱͼ�����ΪCV_MAT_DEPTH��dtype����
	�����߸�������InputArray���͵�mask����ѡ�Ĳ�����ģ����Ĭ��ֵnoArray().
*/

int main()
{
	Mat srcImage = imread("img/700-700����1.jpeg", 0);
	if (srcImage.empty()) { printf("ͼƬ��ȡʧ��"); return false; }
	imshow("ԭʼͼ��", srcImage);
	
	// �������ͼ����������ѵĳߴ磬�߽���0����
	int m = getOptimalDFTSize(srcImage.rows);
	int n = getOptimalDFTSize(srcImage.cols);


	// ����ӵ����س�ʼ��Ϊ0
	Mat padded;
	copyMakeBorder(srcImage, padded, 0, m - srcImage.rows, 0, n - srcImage.cols, BORDER_CONSTANT, Scalar::all(0));

	//Ϊ����Ҷ�任�Ľ����ʵ�����鲿������洢�ռ䡣
	//��planes������Ϻϲ���һ����ͨ��������complexI
	Mat planes[] = { Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F) };
	Mat complexI;
	merge(planes, 2, complexI);

	// ���о͵���ɢ����Ҷ�任
	dft(complexI, complexI);

	// ������ת��Ϊ��ֵ,��=>log(1+sqrt(Re(DFT(I)) ^ 2 + Im(DFT(I)) ^ 2))
	split(complexI, planes); // ����ͨ������complexI����ɼ�����ͨ�����顣
	// ʵ����planes[0] = Re(DFT(I), 
	// �鲿��planes[1] = Im(DFT(I))
	magnitude(planes[0], planes[1], planes[0]); // planes[0] = magnitude
	Mat magnitudeImage = planes[0];


	// ���ж����߶�(logarithmic scale)����	
	log(magnitudeImage, magnitudeImage); // ����Ȼ����
	

	// ���к��طֲ�����ͼ����
	// ���������л������У�����Ƶ�ײü�
	magnitudeImage = magnitudeImage(Rect(0, 0, magnitudeImage.cols & -2, magnitudeImage.rows & -2));

	// �������и���Ҷͼ���е�����,ʹ��ԭ��λ��ͼ������
	int cx = magnitudeImage.cols / 2;
	int cy = magnitudeImage.rows / 2;
	Mat q0(magnitudeImage, Rect(0, 0, cx, cy)); // ROI���������
	Mat q1(magnitudeImage, Rect(cx, 0, cx, cy)); // ROI���������
	Mat q2(magnitudeImage, Rect(cx, 0, cx, cy)); // ROI���������
	Mat q3(magnitudeImage, Rect(cx, cy, cx, cy)); // ROI���������

	//��������(���������½��н���)
	Mat tmp;
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);

	//��������(���������½��н���)
	q1.copyTo(tmp);
	q2.copyTo(q1);
	tmp.copyTo(q2);


	//��һ��,��0��1֮��ĸ���ֵ������任Ϊ���ӵ�ͼ���ʽ
	//�˾�����OpenCV2��Ϊ:
	//normalize(magnitudeImage, magnitudeImage, 0, 1, CV_MINMAX);
	normalize(magnitudeImage, magnitudeImage, 0, 1, NORM_MINMAX);

	//��ʾЧ��ͼ
	imshow("Ƶ�׷�ֵ", magnitudeImage);
	waitKey();

	return 2;

}	
