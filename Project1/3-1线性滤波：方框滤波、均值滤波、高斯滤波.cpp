#include <opencv2/opencv.hpp>
using namespace cv;

/*	平滑处理
	平滑处理(smoothing)也称模糊处理(bluring), 是一种简单且使用频率很高的图像处理方法。
平滑处理的用途有很多，最常见的是用来减少图像上的噪点或者失真。在涉及到降低图像分辨率时，平滑处理是非常好用的方法。
*/

/*	图像滤波与滤波器
	图像滤波，指在尽量保留图像细节特征的条件下对目标图像的噪声进行抑制，是图像预处理中不可缺少的操作，其处理效果的好坏
将直接影响到后续图像处理和分析的有效性和可靠性。
	消除图像中的噪声成分叫作图像的平滑化或滤波操作。信号或图像的能量大部分集中在幅度谱的低频和中频段，而在较高频段，有用
的信息或图像的能量大部分集中在幅度谱的低频和中频段，而在较高频段，有用的信息经常被噪声经常被噪声淹没。因此一个能降低高频成分幅度的滤波器就能够减弱噪声的影响。
	图像滤波的目的有两个：一个是抽出对象的特征作为图像识别的特征模式；另一个是为适应图像处理的要求，消除图像数字化时所混入的噪声。
	而对滤波器处理的要求也有两条：一是不能损坏图像的轮廓以及边缘等重要信息；二是使图像清洗视觉效果好。
	平滑滤波是低频增强的空间域滤波技术。它的目的有两类：一类是模糊；另一类是消除噪音。
	空间域的平滑滤波一般采用简单平均法进行，就是求邻近像元点的平均亮度值。领域的大小与平滑的效果直接相关，领域越大平滑的效果越好，但领域过大，平滑也会使边缘信息损失的越大，从而使输出的图像变得模糊，因此需合理选择领域的大小。
	关于滤波器，一种形象的比喻是：可以把滤波器想象成一个包含加权系数的窗口，当使用这个滤波器平滑处理图像时，就把这个窗口放到图像之上，透过这个窗口来看我们得到的图像。
	滤波器的种类有很多，在新版的OpenCV中，提供了如下5中常用的图像平滑处理操作方法：
		·方框滤波—BoxBlue函数
		·均值滤波（领域平局滤波）—Blur函数
		·高斯滤波—GaussianBlur函数
		·中值滤波—medianBlur函数
		·双边滤波—bilateralFilter函数
		本节要讲解的是作为线性滤波的方框滤波、均值滤波和高斯滤波。其他两种非线性滤波操作—中值滤波和双边滤波，我们留待下节讲解。
*/

/*	线性滤波器的简介
	线性滤波器：线性滤波器经常用于剔除输入信号中不想要的频率或者从许多频率中选择一个想要的频率。
	几种常见的线性滤波器如下。
		·低通滤波器：允许低频率通过；
		·高通滤波器：允许高频率通过；
		·带通滤波器：允许一定范围频率通过；
		·全通滤波器：阻止一定范围频率通过并且允许其他频率通过；
		·陷波滤波器（Band-Stop Filter）:阻止一个狭窄频率范围通过，是一种特殊带阻滤波器。
*/


/*	滤波和模糊
	滤波可分低通滤波和高通滤波器两种：高斯滤波是指用高斯函数作为滤波函数的滤波操作。
	低通是模糊，高通是锐化。
*/

/*	领域算子与线性领域滤波
	领域算子（局部算子）是利用给定像素周围的像素值的决定此像素的最终输出值的一种算子。而线性领域滤波就是一种常用的领域算子，像素的输出值取决于输入像素的加权和。
	领域算子除了用于局部色调调整以外，还可以用于图像滤波，以实现图像的平滑和锐化，图像边缘增强或者图像噪声的去除。本节我们介绍的主角是线性领域滤波算子，即用不同的权重去结合一个小领域内的像素，来得到应有的处理效果。
	领域滤波（卷积）—左边图像与中间图像的卷积产生右边图像。
	线性滤波处理的输出像素值g(i,j)是输入像素值f（i+k， j+I）的加权和
		g（i，j） = f(i+k, j+I)h(k,I)
		其中的h(k,I)，我们称其为“kernel”，是滤波器的加权系数，即滤波器的“滤波器系数”。
*/

/*	方框滤波（box Filter）
	方框滤波（box Filter）被封装在一个名为boxblur的函数中，即boxblur函数的作用是使用方框滤波器（box filter）来模糊一张图片.
		c++: void boxFilter(InputArray src, OutputArray dst, int ddepth, Size ksize, Point anchor=Point(-1, -1), boolnormalize=true, int borderType=BORDER_DEFAULT)
		·5：Point类型的anchor，表示锚点（即被平滑的那个点）。注意它有默认值Point(-1, -1)。如果这个点坐标是负值的话，就表示取核的中心为锚点，所以默认值Point（-1， -1）表示这个描点在核的中心。
		·6：bool类型的normalize，默认值为true，一个标识符，表示内核是否被其区域归一化了
		·7：int类型的borderType，用于推断图像外部像素的某种边界模式。有默认值BORDER_DEFAULT。
*/

/*	均值滤波
	均值滤波，输出图像的每一个像素是核窗口内输入图像对应像素的平均值（所有像素加权系数相等），是归一化后的方框滤波。

	1.均值滤波的理论简析
	均值滤波是典型的线性滤波算法，主要方法为领域平均法，即用一片图像区域的各个像素的均值来代替原图像中的各个像素值。一般需要在图像上对目标像素给出一个模板（内核），该模板包括了其周围的临近像素（比如以目标像素为中心的周围8（3×3-1）个像素，构成一个滤波模板，即去掉目标像素本身）。
再用模板中的全体像素的平均值来代替原本像素值。即对待处理的当前像素点（x，y），选择一个模板，该模板由其邻近的若干像素组成，求模板中说有像素的当前像素点（x，y），选择一个模板，该模板尤其邻近的若干像素组成，求模板中所有像素的均值，再把该均值赋予当前像素点（x，y），作为处理后图像在
该点上的灰度点g（x，y），即g（x，y） = 1 / m 和f(x,y)，其中m为该模板中包含像素在内的像素总个数。
	2.均值滤波的缺陷
	均值滤波本身存在着固有的缺陷，即它不能很好地保护图像细节，在图像去噪的同时也破坏了图像的细节部分，从而使图像变得模糊，不能很好地去除噪声点。
	3.在OpenCV中使用均值滤波—blur函数
	blur函数的作用是：对输入的图像src进行均值滤波后用dst输出。
	blur函数在OpenCV官方文档中，给出的其核是这样的：
		K = 1 / (ksize.width * ksize.height) * [[1,1,1,1]....[1,1,1,1]]
	这个内核一看就明了，就是在求均值，即blur函数封装的就是均值滤波。
	blur函数的原型如下：
		c++: void blur(InputArray src, OutputArray dst, Size ksize, Point anchor=Point(-1,-1), int borderType=BORDER_DEFAULT)
		·3：Size类型（对Size类型稍后有讲解）的ksize，内核的大小。
		·4：Point类型的anchor，表示锚点（即被平滑的那个点），注意他有默认值Point（-1，-1）.如果这个点坐标是负值，就表示取核的中心为锚点，所以默认值Point（-1，-1）表示这个锚点在核的中心。
		·5：int类型的borderType，用于推断图像外部像素的某种边界模式。有默认值BORDER_DEFAULT，我们一般不去管它。
*/



/*	高斯滤波
	1.高斯滤波的理论简析
	高斯滤波是一种线性平滑滤波，可以消除高斯噪声，广泛应用于图像处理的减噪过程。通俗地讲，高斯滤波就是对整幅图像进行加权平均的过程，每一个像素点的值，都有其本身和领域内的其他像素值经过加权平均后得到。高斯滤波的具体操作是：用一个模板（或称卷积、掩模）扫描图像中的每一个像素，用模板确定的领域内像素的加权平均灰度值去替代模板中心像素点的值。
	大家常说高斯滤波是最有用的滤波操作，虽然它用起来效率往往不是最高的。高斯模糊技术生成的图像，其视觉效果就像是经过一个半透明屏幕在观察图像，其视觉效果就像是经过一个半透明屏幕在观察图像，这与镜头焦外成像效果散景以及普通照明阴影中的效果都明显不同。高斯平滑在用于计算机视觉算法中的预先处理阶段，以增强图像在不同比例大小下的图像效果（参见尺度空间表示以及尺度空间实现）。从数学的角度来看，图像的高斯模糊过程就是图像与正态分布做卷积。由于正太分布又叫作高斯分布，所以这项技术就叫作高斯模糊。
	高斯滤波器是一类根据高斯函数的形状来选择权值的线性平滑滤波器。高斯平滑滤波器对于抑制服从正太分布的噪声非常有效。一维零均高斯函数如下。
		G（x） = exp( -x^2/(2sigma^2))
		其中，高斯分布参数Sigma决定了高斯函数的宽度。对于图像处理来说，常用二维零均值高斯函数作平滑滤波器。
		G0（x， y） = Ae（-（x-ux）^2/ 2(fanx^2))/ + -(y-uy)^2/ 2(fany^2)
	2.高斯滤波：GaussianBlur函数
	GaussianBlur函数的作用是用高斯滤波器来模糊一张图片，对输入的图像src进行高斯滤波后用dst输出。它将源图像和指定的高斯核函数做卷积运算，并且支持就地过滤（In-placefiltering)
		c++: void GaussianBlur(InputArray src, OutputArray dst, Size ksize, double sigmaX, double sigmaY=0, intborderType= BORDER_DEFAULT)
		·3：Size类型的ksize高斯内核的大小。其中ksize.width和ksize.height可以不同，但它们都必须为正数和奇数，或者是零，这都由sigma计算而来。
		·4：double类型的sigmaX，表示高斯核函数在X方向的标准偏差。
		·5：double类型的sigmaY，表示高斯核函数在Y方向的标准偏差。若sigmaY为零，就将它设为sigmaX；如果都是0那么就由ksize.width和ksize.height计算出来。
		·6：int类型的borderType，一般不去管他。
*/

#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int blurT()
{

	Mat image = imread("img/700-700狂三1.jpeg");

	namedWindow("均值滤波【原图】");
	namedWindow("均值滤波【效果图】");

	imshow("均值滤波【原图】",image);


	Mat out;
	boxFilter(image, out, -1, Size(5, 5));

	imshow("均值滤波【效果图】",out);




	Mat Gauss;
	GaussianBlur(image, Gauss, Size(3, 3), 0, 0);
	imshow("高斯滤波", Gauss);
	waitKey(0);
	return 0;
}

Mat g_srcImage, g_dstImage1, g_dstImage2, g_dstImage3; // 存储图片的Mat类型
int g_nBoxFilterValue = 3; // 方框滤波参数值
int g_nMeanBlurValue = 3; // 均值滤波参数值
int g_nGaussianBlurValue = 3; // 高斯滤波参数值


static void on_BoxFilter(int, void*); // 方框滤波
static void on_MeanBlur(int, void*); // 均值滤波
static void on_GaussianBlur(int, void*); // 高斯滤波



int main()
{
	// 改变console字体颜色
	system("color5E");

	g_srcImage = imread("img/700-700狂三1.jpeg");

	g_dstImage1 = g_srcImage.clone();
	g_dstImage2 = g_srcImage.clone();
	g_dstImage3 = g_srcImage.clone();


	imshow("原图窗口", g_srcImage);

	// 方框滤波
	namedWindow("方框滤波",1);
	// 创建轨迹条
	createTrackbar("内核值：", "方框滤波", &g_nBoxFilterValue, 40, on_BoxFilter);
	on_BoxFilter(g_nBoxFilterValue, 0);
	


	// 均值滤波
	namedWindow("均值滤波",1);
	createTrackbar("内核值:", "均值滤波", &g_nMeanBlurValue, 40, on_MeanBlur);
	on_MeanBlur(g_nMeanBlurValue, 0);
	

	// 高斯滤波
	namedWindow("高斯滤波",1);
	createTrackbar("内核值", "高斯滤波", &g_nGaussianBlurValue, 40, on_GaussianBlur);
	on_GaussianBlur(g_nGaussianBlurValue, 0);



	while (char(waitKey(1) != 'q')) {}
	return 0;
}


static void on_BoxFilter(int, void *)
{
	boxFilter(g_srcImage, g_dstImage1, -1, Size(g_nBoxFilterValue + 1, g_nBoxFilterValue + 1));
	imshow("方框滤波", g_dstImage1);
}

static void on_MeanBlur(int, void *)
{
	blur(g_srcImage, g_dstImage2, Size(g_nMeanBlurValue + 1, g_nMeanBlurValue + 1), Point(-1, -1));
	imshow("均值滤波", g_dstImage2);
}

static void on_GaussianBlur(int, void *)
{
	GaussianBlur(g_srcImage, g_dstImage3, Size(g_nGaussianBlurValue*2+1, g_nBoxFilterValue*2+1), 0, 0);
	imshow("高斯滤波", g_dstImage3);
}