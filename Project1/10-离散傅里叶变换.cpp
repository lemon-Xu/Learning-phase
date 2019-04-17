#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;

/*	离散傅里叶变换
	离散傅里叶变换（Discrete Fourier Transform, 缩写为DFT）,是指傅里叶变换在时域或频域上都呈现离散的形式，将时域信号的采样变换为离散时间傅里叶变换(DTFT)频域的采样。
	在形式上，变换两端（时域或频域上）的序列是有限长的，而实际上这两组序列都应道被认为是离散周期信号的主值序列。即使对有限长的离散信号做DFT，也应当对其经过周期信号在进行变换。
	在实际应用中，通常采用快速傅里叶变换来高效计算DFT。
*/

/*	离散傅里叶变换的原理
	简单来说，对一张图像使用傅里叶变换就是将它分解成正弦和余弦两部分，也就是将图像从空间域（spatial domain）转换到频域(frequency domain)。
	这一转换的理论基础为：任一函数都可以表示成无数个正弦和余弦函数的和的形式。傅里叶变换就是一个用来将函数分解的工具。
	二维图像的傅里叶变换可以用以下数据公式来表示。
	https://baike.baidu.com/item/%E5%BF%AB%E9%80%9F%E5%82%85%E9%87%8C%E5%8F%B6%E5%8F%98%E6%8D%A2/214957?fr=aladdin
	式中f是空间域（spatial domain）值，F是频域（frequency domain）值。转换之后的频域值是复数，因此，显示傅里叶变换之后的结果需要使用实数图像（real iamge）加虚数图像(ccomplex image)，
或者幅度图像（magitude image）加相位图像（phase image）的形式。在实际的图像处理过程中，仅仅使用了幅度图像，因为幅度图像包含了原图像的几乎所有我们需要的几何信息。
然而，如果像通过修改幅度图像或者相位图像的方法来间接修改原空间图像，需要使用逆傅里叶变换得到修改后的空间图像，这样就必须同时保留幅度图像和相位图像了。
	在频域里面，对于一副图像，高频部分代表了图像的细节、纹理信息；低频部分代表了图像的轮廓信息。如果对一副精细的图像使用低通滤波器，那么滤波后的结果就只剩下轮廓了。
这与信号处理的基本思想是相通的。如果图像受到的噪声恰好位于某个特定的“频率”范围内，则可以通过滤波器来恢复原来的图像。傅里叶变换在图像处理中可以做到图像增强与图像去噪、图像分割之边缘检测、图像特性提取、图像压缩等。
*/

/*	1-dft()函数详解
	dft函数的作用是对一维或二维浮点数数组进行正向或反向离散傅里叶变换。
	c++: void dft(InputArray src, OutputArray dst, int flags=0, int nonzeroRows=0)
	·第一个参数，InputArray类型的src。输入矩阵，可以为实数或者虚数。
	·第二个参数，OutputArray类型的dst。函数调用后的运算结果存在这里，其尺寸和类型取决于标识符，也就是第三个参数flags。
	·第三个参数，int类型的flags。转换的标识符，有默认值0，取值可以为：
		DFT_INVERSE			用一维或二维变换代替默认的正向变换
		DFT_SCALE			缩放比例标识符，输出的结果都会以1/N进行缩放，通常会结合DFT_INVERSE一起使用
		DFT_ROWS			对输入矩阵的每行进行正向或反向的变换，此标识符可以在处理多种矢量的时候用于减小资源开销，这些处理常常是三维或高维变换等复杂操作
		DFT_COMPLEX_OUTPUT	进行一维或二维实数数组进行变换。这样的结果虽然是复数阵列，但拥有复数的共轭对称性（CCS），所以可以写成一个拥有同样尺寸的实数矩阵。
		DFT_REAL_OUTPUT		进行一维或二维复数数组反变换。这样的结果通常是一个大小相同的复矩阵。如果输入的矩阵有复数的共轭对称性（比如是一个带有DFT_COMPLEX_OUTPUT标识符的正变换结果），便会输出实矩阵.
	·第四个参数， int类型的nonzeroRows，有默认值0.当此参数设为非零时（最好是取值为想要处理的那一行的值，比如C.rows），函数会假设只有输入矩阵的第一个非零行包括非零元素（没有设置DFT_INVERSE标识符），
	或只有输入矩阵的第一个非零行包含非零元素(设置了DET_INVERSE标识符)。这样的话，函数就可对其他行进行更高效的处理，以节省时间开销。这项技术尤其是在采用DFT计算矩阵卷积时非常有效。
*/

/*	2-返回DFT最优尺寸大小：getOptimalDFTSize()函数
	getOptimalDFTSize函数返回给定向量尺寸的傅里叶最优尺寸大小。为了提高离散傅里叶变换的运行速度，需要扩充图像，而具体扩充多少，就有这个函数来计算的到。
	c++: int getOptimalDFTSize(int vecsize)
	此函数的唯一一个参数为int类型的vecsize，向量尺寸，即图片的rows、cols。	
*/

/*	3-扩充图像边界：copyMakeBorder()函数
	copyMakeBorder函数的作用是扩充图像边界。
	c++: void copyMakeBorder(InputArray src, OutputArray dst, int top, int bottom, int left, int right, int borderType, const Scalar&value=Scalar())
	·第二个参数，OutputArray类型的dst，需和源图片有一样的尺寸和类型，且size应该为Size（src.cols+left+right, src.rows+top+bottom）.
	·第七个参数，borderType类型的，边界类型，常见取值为BORDER_CONSTANT，可参考borderInterpolate()得到更多的细节。
	·第八个参数，const Scalar&类型的value，有默认值Scalar()，可以理解为默认值为0.当borderType取值为BORDER_CONSTANT时，这个参数表示边界值.
*/

/*	4-计算二维矢量的幅值：magnitude()函数
	magnitude()函数用于计算二维矢量的幅值。
	c++: void magnitude(InputArray x, InputArray y, OutputArray magnitude)
	·第一个参数，InputArray类型的x，表示矢量的浮点型X坐标值，也就是实部。
	·第二个参数，InputArray类型的y，表示矢量的浮点型Y坐标值，也就是虚部。
	·第三个参数，OutputArray类型的magnitude，输出的幅值，它和第一个参数x有着同样的尺寸和类型。
	原理：dst(I) = (x(I)^2 + y(I)^2)^(1/2)

*/

/*	5-计算自然对数：log()函数
	log()函数的功能是计算每个数组元素绝对值的自然对数。
	c++: void log(InputArray src, OutputArray dst)
	第一个参数为输入图像，第二个参数为得到的对数值。
*/

/*	6-矩阵归一化：normalize()函数
	normalize()的作用是进行矩阵归一化。
	c++： void normalize(InputArray src, OutputArray dst, double alpha=1, double beta=0, int norm_type=NORM_L2, int dtype=-1, InputArray mask=noArray())
	·输入输出图像有一样的尺寸和类型
	·第三个参数，double类型的alpha。归一化后的最大值，有默认值1.
	·第四个参数，double类型的beta。归一化后的最小值，有默认值0.
	·第五个参数，int类型的norm_type。归一化类型，有NORM_INF、NORM_L1、NORM_L2和NORM_MINMAX等参数可选，有默认值NORM_L2.
	·第六个参数，int类型的dtype，有默认值-1.当此函数取负值时，输出矩阵和src有同样的类型，否者，它和src有同样的通道数，且此时图像深度为CV_MAT_DEPTH（dtype）。
	·第七个参数，InputArray类型的mask，可选的操作掩模，有默认值noArray().
*/

int main()
{
	Mat srcImage = imread("img/700-700狂三1.jpeg", 0);
	if (srcImage.empty()) { printf("图片读取失败"); return false; }
	imshow("原始图像", srcImage);
	
	// 将输入的图像延扩到最佳的尺寸，边界用0补充
	int m = getOptimalDFTSize(srcImage.rows);
	int n = getOptimalDFTSize(srcImage.cols);


	// 将添加的像素初始化为0
	Mat padded;
	copyMakeBorder(srcImage, padded, 0, m - srcImage.rows, 0, n - srcImage.cols, BORDER_CONSTANT, Scalar::all(0));

	//为傅里叶变换的结果（实部和虚部）分配存储空间。
	//将planes数组组合合并成一个多通道的数组complexI
	Mat planes[] = { Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F) };
	Mat complexI;
	merge(planes, 2, complexI);

	// 进行就地离散傅里叶变换
	dft(complexI, complexI);

	// 将复数转换为幅值,即=>log(1+sqrt(Re(DFT(I)) ^ 2 + Im(DFT(I)) ^ 2))
	split(complexI, planes); // 将多通道数组complexI分离成几个单通道数组。
	// 实部：planes[0] = Re(DFT(I), 
	// 虚部：planes[1] = Im(DFT(I))
	magnitude(planes[0], planes[1], planes[0]); // planes[0] = magnitude
	Mat magnitudeImage = planes[0];


	// 进行对数尺度(logarithmic scale)缩放	
	log(magnitudeImage, magnitudeImage); // 求自然对数
	

	// 剪切和重分布幅度图像限
	// 若有奇数行或奇数列，进行频谱裁剪
	magnitudeImage = magnitudeImage(Rect(0, 0, magnitudeImage.cols & -2, magnitudeImage.rows & -2));

	// 重新排列傅里叶图像中的象限,使得原点位于图像中心
	int cx = magnitudeImage.cols / 2;
	int cy = magnitudeImage.rows / 2;
	Mat q0(magnitudeImage, Rect(0, 0, cx, cy)); // ROI区域的左上
	Mat q1(magnitudeImage, Rect(cx, 0, cx, cy)); // ROI区域的右上
	Mat q2(magnitudeImage, Rect(cx, 0, cx, cy)); // ROI区域的左下
	Mat q3(magnitudeImage, Rect(cx, cy, cx, cy)); // ROI区域的右下

	//交换象限(左上与右下进行交换)
	Mat tmp;
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);

	//交换象限(右上与左下进行交换)
	q1.copyTo(tmp);
	q2.copyTo(q1);
	tmp.copyTo(q2);


	//归一化,用0到1之间的浮点值将矩阵变换为可视的图像格式
	//此句代码的OpenCV2版为:
	//normalize(magnitudeImage, magnitudeImage, 0, 1, CV_MINMAX);
	normalize(magnitudeImage, magnitudeImage, 0, 1, NORM_MINMAX);

	//显示效果图
	imshow("频谱幅值", magnitudeImage);
	waitKey();

	return 2;

}	
