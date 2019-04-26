Trackbar
==============================================
* createTrackbar(): 创建轨迹条
* getInfo(): 得到处理参数 
* dst(): 返回处理后的图片
* _callback(): 回调函数

Threshold(Trackbar)
----------------------------------------------
* createTrackbar(window, img, isGray=False)
  * window：窗口名称
  * img：cv2.imread("srcImg")
  * isGray：对要处理的图片进行BGR2GRAY转换
  * return: void
  
* getInfo()
  * return: [posA, posB, WAY]
  * posA: 阖值
  * posB：灰度值
  * WAY： 转换方式
  
示例
># 1 测试Threshold类
>img = cv2.imread("img/1.jpg", 1) <br>
>cv2.namedWindow("window", cv2.WINDOW_NORMAL) <br>
>cv2.imshow("window", img) <br>
>trackbar = Threshold() <br>
>trackbar.createTrackbar("window", img) <br>
>cv2.waitKey(0) <br>
>cv2.destroyAllWindows() <br>
>print(trackbar.getInfo()) <br>

GaussianBlur(Trackbar)
-----------------------------------------------
* createTrackbar(window, img)
	* window: 窗口名称
	* img： cv2.imread("srcImg")
	* return: void
 
* getInfo()
 	* return: [kernel, posB]
	* kernel: 核
	* posB: 标准差
 
示例
># 2 测试GaussianBlur类 <br>
>img = cv2.imread("img/1.jpg", 1) <br>
>cv2.namedWindow("Gaussian", cv2.WINDOW_NORMAL) <br>
>cv2.imshow("Gaussian", img) <br>
>Gaussian = GaussianBlur() <br>
>Gaussian.createTrackbar("Gaussian", img) <br>
>cv2.waitKey(0) <br>
>cv2.destroyAllWindows() <br>
>print(Gaussian.getInfo()) <br>

># 4 测试 GaussianBlur类  ThresholdTrackbar联动 <br>
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
># 5 测试 Canny类
>img = cv2.imread("img/1.jpg", 1) <br>
>cv2.namedWindow("Canny", cv2.WINDOW_NORMAL) <br>
>cv2.imshow("Canny", img) <br>
>canny = Canny() <br>
>canny.createTrackbar("Canny", img) <br>
>cv2.waitKey(0) <br>
>cv2.destroyAllWindows() <br>
