欢迎来到Trackbar的文档！
--------------
Trackbar用于图像处理的手动调参，用Python3语法写成，依赖于cv2模块 <br>
Trackbar实现了OpenCV部分图像处理功能 <br>
Trackbar目前只能处理jpg格式的图片 <br>

目录
---------------
* Trackbar
	* [Threshold](#Threshold)
	* [GaussianBlur](#GaussianBlur)
	* [Canny](#Canny)
	* [morphologyEx](#morphologyEx)
	* [findContours](#findContours)
	
	
Trackbar
==============================================
* createTrackbar(): 创建轨迹条
* getInfo(): 得到处理参数 
* dst(): 返回处理后的图片
* _callback(): 回调函数


<span id = "Threshold"></span>
Threshold(Trackbar)
----------------------------------------------
* createTrackbar(window, img, isGray=False)
  * window: 窗口名称
  * img: cv2.imread("srcImg")
  * isGray: 对要处理的图片进行BGR2GRAY转换
  * return: void
  
* getInfo()
  * return: [posA, posB, WAY]
  * posA: 阈值
  * posB: 灰度值
  * WAY:  转换方式
  
示例
>#1 测试Threshold类
>img = cv2.imread("img/1.jpg", 1) <br>
>cv2.namedWindow("window", cv2.WINDOW_NORMAL) <br>
>cv2.imshow("window", img) <br>
>trackbar = Threshold() <br>
>trackbar.createTrackbar("window", img) <br>
>cv2.waitKey(0) <br>
>cv2.destroyAllWindows() <br>
>print(trackbar.getInfo()) <br>

<span id = "GaussianBlur"></span>
GaussianBlur(Trackbar)
-----------------------------------------------
* createTrackbar(window, img)
	* window: 窗口名称
	* img: cv2.imread("srcImg")
	* return: void
 
* getInfo()
 	* return: [kernel, posB]
	* kernel: 核
	* posB: 标准差
 
示例
>#2 测试GaussianBlur类 <br>
>img = cv2.imread("img/1.jpg", 1) <br>
>cv2.namedWindow("Gaussian", cv2.WINDOW_NORMAL) <br>
>cv2.imshow("Gaussian", img) <br>
>Gaussian = GaussianBlur() <br>
>Gaussian.createTrackbar("Gaussian", img) <br>
>cv2.waitKey(0) <br>
>cv2.destroyAllWindows() <br>
>print(Gaussian.getInfo()) <br>

>#4 测试 GaussianBlur类  ThresholdTrackbar联动 <br>
>img = cv2.imread("img/1.jpg", 0) <br>
>cv2.namedWindow("GaussianBlur", cv2.WINDOW_NORMAL) <br>
>cv2.imshow("GaussianBlur", img) <br>
>Gaussian = GaussianBlur() <br>
>Gaussian.createTrackbar("GaussianBlur", img) <br>
>cv2.waitKey(0) <br>
>cv2.destroyAllWindows() <br>
>print(Gaussian.getInfo()) <br>
><br>		
>cv2.namedWindow("threshold", cv2.WINDOW_NORMAL) <br>
>cv2.imshow("threshold", img) <br>
>threshold = Threshold() <br>
>threshold.createTrackbar("threshold", Gaussian.dstImg, isGray=True) <br>
>cv2.waitKey(0) <br>
>cv2.destroyAllWindows() <br>
>print(threshold.getInfo()) <br>

<span id = "Canny"></span>
Canny(Trackbar)
---------------------------------------
* createTrackbar(window, img)
	* window: 窗口名
	* img: cv2.imread("srcImg")
	* return: void
	
* getInfo()
	* return: [minThreshold, maxThreshold, ratio]
	* minThreshold: 最小阈值
	* maxThreshold: 最大阈值
	* ratio: 阈值比（最大阈值 / 最小阈值）

示例
>#5 测试 Canny类
>img = cv2.imread("img/1.jpg", 1) <br>
>cv2.namedWindow("Canny", cv2.WINDOW_NORMAL) <br>
>cv2.imshow("Canny", img) <br>
>canny = Canny() <br>
>canny.createTrackbar("Canny", img) <br>
>cv2.waitKey(0) <br>
>cv2.destroyAllWindows() <br>

<span id = "morphologyEx"></span>
morphologyEx(Trackbar)
------------------------------------------
* crreateTrackbar(window, img, isGray=Flase)
	* window: 窗口名
	* img: cv2.imread("srcImg")
	* isGray: 对要处理的图片进行BGR2GRAY格式转换
	* return: void
	
* getInfo()
	* return: MORPH, structuring, kernel]
	* MORPH: 形态学操作
	* structuring: 结构化方式
	* kernel: 核（width, height）

示例
>#6 测试 morphologyEx类 <br>
>img = cv2.imread('img/1.jpg', 1) <br>
>cv2.namedWindow('morph', cv2.WINDOW_NORMAL) <br>
>cv2.imshow('morph', img) <br>
>morph = morphologyEx() <br>
>morph.createTrackbar('morph', img) <br>
>cv2.waitKey(0) <br>
>cv2.destroyAllWindows() <br>
>print(morph.getInfo()) <br>

<span id = "findContours"></span>
findContours(Trackbar)
------------------------------------
* crreateTrackbar(window, img, isGray=Flase)
	* window: 窗口名
	* img: cv2.imread("srcImg")
	* isGray: 对要处理的图片进行BGR2GRAY格式转换
	* return: void
	
* getInfo()
	* return: [CV2_RETR, CV2_CHAIN_APPROX]
	* CV2_RETR: 轮廓检索模式
	* CV2_CHAIN_APPROX: 轮廓的近似方法
	
示例
>#7 测试findContours类 与 threshold类联动
>img = cv2.imread("img/1.jpg", 0) <br>
>cv2.namedWindow("threshold", cv2.WINDOW_NORMAL) <br>
>cv2.imshow("threshold", img) <br>
>threshold = Threshold() <br>
>threshold.createTrackbar("threshold", img, True) <br>
>cv2.waitKey(0) <br>
>cv2.destroyAllWindows() <br>
>print(threshold.getInfo()) <br>
>
>cv2.namedWindow('findContours', cv2.WINDOW_NORMAL) <br>
>cv2.imshow('findContours', threshold.dst()) <br>
>fc = findContours() <br>
>fc.createTrackbar('findContours', threshold.dst(), True) <br>
>cv2.waitKey(0) <br>
>cv2.destroyAllWindows() <br>
>print(fc.getInfo()) <br>
