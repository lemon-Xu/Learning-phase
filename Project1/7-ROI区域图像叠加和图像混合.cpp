#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>

using namespace cv;

//	����Ȥ����ROI
/*
	��ͼ�����������ǳ�����Ҫ���ø���Ȥ����ROI, region of interest������רע���߼򻯹�������Ҳ���Ǵ�ͼ����ѡ��һ��ͼ������
���������ͼ���������ע���ص㡣����Ȧ����������Ա���н�һ���������ң�ʹ��ROIָ��������Ŀ�꣬���Լ��ٴ���ʱ�䣬���Ӿ��ȣ���ͼ���������С�ı�����
	����ROI���������ַ�������һ����ʹ�ñ�ʾ���������Rect����ָ�����ε����Ͻ����꣨���캯����ǰ�����������;��εĳ������캯���ĺ������������Զ���һ����������
	imageROI = image(Rect(500, 250, logo.cols, logo.rows));
	��һ�ֶ���ROI�ķ�����ָ������Ȥ�л��еķ�Χ��Range����Range��ָ����ʼ��������ֹ��������������ֹ��������һ�����������С�cRange������������Range�����ʹ��Range������ROI����ôǰ���ж���ROI�Ĵ��������дΪ��
	imageROI = image(Range(250, 250 + logoImage.rows), Range(200,200+logoIamge.cols));
*/

//	1-����ROI��һ��ͼ�ӵ���һ��ͼ��ָ��λ��
/*
	����ͨ��һ��ͼ����ģ��mask����ֱ�ӽ����봦����������λlogoͼ�������ֵ������Ч����ܱ���.
	mask����λͼ������ѡ���ĸ��������������ĸ����ز������������mask���ص�ֵ�Ƿ�0�ģ��ҾͿ����������򲻿�����
*/
bool ROI_AddImage()
{
	Mat srcImage1 = imread("700-700����1.jpeg");
	Mat logoImage = imread("200-200����1.jpeg");
	
	if (!srcImage1.data) { printf("��ȡsrcImage1 ����~! \n"); return false; }
	if (!logoImage.data) { printf("��ȡlogoImage����~!  \n"); return false; }

	//// ����һ��Mat���Ͳ������趨ROI����
	Mat imageROI = srcImage1(  Rect(200, 250, logoImage.cols, logoImage.rows) ); 
	
	// ������ģ�������ǻҶ�ͼ��
	Mat mask = imread("200-200����1.jpeg", 0);
	
	// ����ģ���Ƶ�ROI
	logoImage.copyTo(imageROI, mask);

	namedWindow("<1>����ROIʵ��ͼ�����ʾ������");
	imshow("<1>����ROIʵ��ͼ�����ʾ������", srcImage1);
	waitKey(0);

	return true;
}

// 2-���Ի�ϲ���
/*
	���Ի�ϲ�����һ�ֵ��͵Ķ�Ԫ���������룩�����ز������������۹�ʽ���£�
		g(x) = (1-a) fa(x) + af3(x)
	����ͨ���ڷ�Χ0��1֮��ı�alphaֵ����������ͼ�� f0(x) �� f1(x) ����������Ƶ��ͬ��Ϊ f0(x) �� f1(x)������ʱ���ϵĽ����ܽ�(cross-dissolve)Ч��������õ�Ƭ�͵�Ӱ�����е�������Ҳ�����ڻõ�Ƭ��ҳʱ���õ�ǰ��ҳ�������ȵ���Ч�����Լ���Ӱ��ڹ���ʱ�������ֵĻ������Ч����
	ʵ�ַ��棬��Ҫ������OpenCV��addWeighted����
	dst = src1[I]*alpha + src2[I]*beta + gamma;
	����I�Ƕ�ά����Ԫ�ص�����ֵ�����ң���������ͨ�������ʱ��ÿ��ͨ������Ҫ�����ؽ��д���������Ҫע����ǣ��������������ΪCV_32Sʱ����������Ͳ������ˣ���ʱ��ͻ��ڴ������������Ľ��ѹ�����ӡ�
*/
bool LinearBlending()
{
	// ����һЩ�ֲ�����
	double alphaValue = 0.5;
	double betaValue;
	Mat srcImage2, srcImage3, dstImage;

	// ��ȡͼ������ͼƬ��Ϊͬ�������ͺͳߴ磩
	srcImage2 = imread("700-700����1.jpeg");
	srcImage3 = imread("700-700����2.jpeg");

	if (srcImage2.empty()) { printf("��ȡsrcImage2����~! \n"); return false; }
	if (srcImage3.empty()) { printf("��ȡsrcImage3����~! \n"); return false; }

	// ��ͼ���ϼ�Ȩ����
	betaValue = (1.0 - alphaValue);
	addWeighted(srcImage2, alphaValue, srcImage3, betaValue, 0.0, dstImage);

	// ��������ʾԭͼ����
	namedWindow("<2>���Ի��ʾ������[ԭͼ]", 1);
	imshow("<2>���Ի��ʾ������[ԭͼ]", srcImage2);

	namedWindow("<3>���Ի��ʾ������[Ч��ͼ]",1);
	imshow("<3>���Ի��ʾ������[Ч��ͼ]", dstImage);

	waitKey(0);
	return true;

	/*
		��������Ҫע�����,��Ϊ�����Ƕ�srcImage1��srcImage2���,�������Ǳ���Ҫ����ͬ�ĳߴ�(��Ⱥ͸߶�)������,��Ȼ����Ĳ���û�ж�Ӧ��"��",�϶��������.
	*/
}


// 3-����ͼ����
/*
	��ָ��ROI,����addWeighted������ָ����ROI�����ͼ����л�ϲ���.���ǽ����װ����һ����ΪROI_LinearBlending�ĺ�����
*/
bool ROI_LinearBlending()
{
	Mat srcImage4 = imread("img/700-700����1.jpeg",1);
	Mat srcImage5 = imread("img/200-200����1.jpeg");
	Mat mask = imread("img/200-200����1.jpeg");
	Mat dstImage;

	if (srcImage4.empty()) { printf("��ȡsrcImage4����\n"); return false; }
	if (srcImage5.empty()) { printf("��ȡsrcImage5����\n"); return false; }

	Mat imageROI;
	imageROI = srcImage4(Rect(200, 250, srcImage5.cols, srcImage5.rows));

	
	// ������
//  imageROI = srcImage4(Range(250, 250+srcImage5.rows), Range(200, 200+srcImage5.cols));

	addWeighted(imageROI, 0.5, srcImage5, 0.3, 0.0, dstImage);
	dstImage.copyTo(imageROI, mask);

	namedWindow("<4>��������ͼ����ʾ������");
	imshow("<4>��������ͼ����ʾ������",srcImage4);

	waitKey(0);
	return true;
}



int main()
{
	ROI_LinearBlending();
	
	return 0;
}