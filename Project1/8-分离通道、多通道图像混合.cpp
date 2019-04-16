#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

bool ROI_AddImage();
bool LinearBlending();
bool ROI_LinearBlending();




/*
	为了更好地观察一些图像材料的特征，有时需要对RGB三个颜色通道的分量进行分别显示和调整。通过OpenCV的split和merge方法可以很方便地达到目的。
*/

// 1-通道分离：split（）函数
/*
	split函数用于将一个多通道数组分离成几个单通道数组。这里的array按语境翻译为数组或者阵列。
	这个split函数的C++版本有两个原型，分别是：
	* c++:void split(const Mat& src, Mat*mvbegin);
	* c++:void split(InputArray m, OutputArrayOfArrays mv);
	变量介绍如下:
	* 第一个参数，InputArray类型的m或者const Mat&类型的src，填我们需要进行分离的多通道数组.
	* 第二个参数，OutputArrayOfArrays类型的mv，填函数的输出数组或者输出的vector容器.

	split函数分割多通道数组转换成独立的单通道数组，公式如下：
	mv[c](I) = src(I)c

*/
bool splitBGR() {
	
	Mat image = imread("img/700-700狂三1.jpeg", 1);

	Mat imageBlueChannel;
	Mat imageGreenChannel;
	Mat imageRedChannel;

	if (image.empty()) {
		printf("图片读取错误");
		return false;
	}

	vector<Mat> channels;
	// 把一个三通道图像转化为三个单通道图像
	split(image, channels);
	// 分别显示分离的单通道图像	
	imageBlueChannel = channels.at(0);
	imageGreenChannel = channels.at(1);
	imageRedChannel = channels.at(2);

	imshow("原图像", image);
	imshow("<1>蓝色通道图像", imageBlueChannel);
	imshow("<2>绿色通道图像", imageGreenChannel);
	imshow("<3>红色通道图像", imageRedChannel);

	waitKey(0);
	imwrite("img/700-700狂三1B.jpeg",imageBlueChannel);
	imwrite("img/700-700狂三1G.jpeg", imageGreenChannel);
	imwrite("img/700-700狂三1R.jpeg", imageRedChannel);

	return true;
}


// 2-通道合并:merge()函数
/*
	merge()函数是split（）函数的逆向操作--将多个数组合并成一个多通道的数组。它通过组合一些给定的单通道数组，将这些孤立的单通道数组合并成一个多通道的数组，从而创建出一个由多个单通道阵列组成的多通道阵列。
	* c++:void merge(const Mat*mv, size_tcount, OutputArray dst)
	* c++:void merge(InputArrayOfArrays mv, OutputArray dst)

	变量介绍如下。
	* 第一个参数，mv。填需要被合并的输入矩阵或vector容器的阵列，这个mv参数中所有的矩阵必须有着一样的尺寸和深度。
	* 第二个参数，count。当mv为一个空白的C数组时，代表输入矩阵的个数，这个参数显然必须大于1.
	* 第三个参数，dst。即输出矩阵，和mv【0】拥有一样的尺寸和深度，并且通道的数量是矩阵阵列中的通道的总数。

	merge函数的功能是将一些数组合并成一个多通道的数组。关于组合的细节，输出矩阵中的每个元素都将是输出数组的串接。其中第i个输入数组的元素被视为mv【i】。C一般用其中的Mat::at（）方法对某个通道进行存取,也就是这样用:channels.at(0)
	这里的Mat::at()方法返回一个引用到指定的数组元素.注意是引用,相当于两者等价,也就是修改其中一个,另一个也会随之改变.
*/
bool mergeBGR()
{

	Mat imageB = imread("img/700-700狂三1B.jpeg", 1);
	Mat imageG = imread("img/700-700狂三1G.jpeg", 1);
	Mat imageR = imread("img/700-700狂三1R.jpeg", 1);

	Mat image;
	vector<Mat> channel;

	vector<Mat> channelB;
	vector<Mat> channelG;
	vector<Mat> channelR;

	split(imageB, channelB);
	split(imageG, channelG);
	split(imageR, channelR);

	// vertor.push_back()  将一个元素添加到vetor尾部
	channel.push_back(channelB.at(0));
	channel.push_back(channelG.at(1));
	channel.push_back(channelR.at(2));

	merge(channel, image);
	imshow("合并后的图像", image);
	waitKey(0);

	return true;
}


int main()
{
	mergeBGR();

}