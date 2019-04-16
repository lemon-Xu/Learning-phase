#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

bool ROI_AddImage();
bool LinearBlending();
bool ROI_LinearBlending();




/*
	Ϊ�˸��õع۲�һЩͼ����ϵ���������ʱ��Ҫ��RGB������ɫͨ���ķ������зֱ���ʾ�͵�����ͨ��OpenCV��split��merge�������Ժܷ���شﵽĿ�ġ�
*/

// 1-ͨ�����룺split��������
/*
	split�������ڽ�һ����ͨ���������ɼ�����ͨ�����顣�����array���ﾳ����Ϊ����������С�
	���split������C++�汾������ԭ�ͣ��ֱ��ǣ�
	* c++:void split(const Mat& src, Mat*mvbegin);
	* c++:void split(InputArray m, OutputArrayOfArrays mv);
	������������:
	* ��һ��������InputArray���͵�m����const Mat&���͵�src����������Ҫ���з���Ķ�ͨ������.
	* �ڶ���������OutputArrayOfArrays���͵�mv����������������������vector����.

	split�����ָ��ͨ������ת���ɶ����ĵ�ͨ�����飬��ʽ���£�
	mv[c](I) = src(I)c

*/
bool splitBGR() {
	
	Mat image = imread("img/700-700����1.jpeg", 1);

	Mat imageBlueChannel;
	Mat imageGreenChannel;
	Mat imageRedChannel;

	if (image.empty()) {
		printf("ͼƬ��ȡ����");
		return false;
	}

	vector<Mat> channels;
	// ��һ����ͨ��ͼ��ת��Ϊ������ͨ��ͼ��
	split(image, channels);
	// �ֱ���ʾ����ĵ�ͨ��ͼ��	
	imageBlueChannel = channels.at(0);
	imageGreenChannel = channels.at(1);
	imageRedChannel = channels.at(2);

	imshow("ԭͼ��", image);
	imshow("<1>��ɫͨ��ͼ��", imageBlueChannel);
	imshow("<2>��ɫͨ��ͼ��", imageGreenChannel);
	imshow("<3>��ɫͨ��ͼ��", imageRedChannel);

	waitKey(0);
	imwrite("img/700-700����1B.jpeg",imageBlueChannel);
	imwrite("img/700-700����1G.jpeg", imageGreenChannel);
	imwrite("img/700-700����1R.jpeg", imageRedChannel);

	return true;
}


// 2-ͨ���ϲ�:merge()����
/*
	merge()������split�����������������--���������ϲ���һ����ͨ�������顣��ͨ�����һЩ�����ĵ�ͨ�����飬����Щ�����ĵ�ͨ������ϲ���һ����ͨ�������飬�Ӷ�������һ���ɶ����ͨ��������ɵĶ�ͨ�����С�
	* c++:void merge(const Mat*mv, size_tcount, OutputArray dst)
	* c++:void merge(InputArrayOfArrays mv, OutputArray dst)

	�����������¡�
	* ��һ��������mv������Ҫ���ϲ�����������vector���������У����mv���������еľ����������һ���ĳߴ����ȡ�
	* �ڶ���������count����mvΪһ���հ׵�C����ʱ�������������ĸ��������������Ȼ�������1.
	* ������������dst����������󣬺�mv��0��ӵ��һ���ĳߴ����ȣ�����ͨ���������Ǿ��������е�ͨ����������

	merge�����Ĺ����ǽ�һЩ����ϲ���һ����ͨ�������顣������ϵ�ϸ�ڣ���������е�ÿ��Ԫ�ض������������Ĵ��ӡ����е�i�����������Ԫ�ر���Ϊmv��i����Cһ�������е�Mat::at����������ĳ��ͨ�����д�ȡ,Ҳ����������:channels.at(0)
	�����Mat::at()��������һ�����õ�ָ��������Ԫ��.ע��������,�൱�����ߵȼ�,Ҳ�����޸�����һ��,��һ��Ҳ����֮�ı�.
*/
bool mergeBGR()
{

	Mat imageB = imread("img/700-700����1B.jpeg", 1);
	Mat imageG = imread("img/700-700����1G.jpeg", 1);
	Mat imageR = imread("img/700-700����1R.jpeg", 1);

	Mat image;
	vector<Mat> channel;

	vector<Mat> channelB;
	vector<Mat> channelG;
	vector<Mat> channelR;

	split(imageB, channelB);
	split(imageG, channelG);
	split(imageR, channelR);

	// vertor.push_back()  ��һ��Ԫ����ӵ�vetorβ��
	channel.push_back(channelB.at(0));
	channel.push_back(channelG.at(1));
	channel.push_back(channelR.at(2));

	merge(channel, image);
	imshow("�ϲ����ͼ��", image);
	waitKey(0);

	return true;
}


int main()
{
	mergeBGR();

}