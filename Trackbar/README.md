Trackbar
==============================================
Threshold(Trackbar)
----------------------------------------------
* createTrackbar(window, img, isGray=False)
  * window：窗口名称
  * img：cv2.imread("srcImg")
  * isGray：对要处理的图片进行BGR2GRAY转换
  * return: void
  
* trackbar.getInfo()
  * return: [posA, posB, WAY]
  * posA: 阖值
  * posB：灰度值
  * WAY： 转换方式
  
示例
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
* createTrackbar(window, img):
 * window: 窗口名称
 * img： cv2.imread("srcImg")
 * return: void
 
* def getInfo(self):
 * return: [kernel, posB]
 * kernel: 核
 * posB: 标准差
 
示例
>测试GaussianBlur类
>img = cv2.imread("img/1.jpg", 1)
>cv2.namedWindow("Gaussian", cv2.WINDOW_NORMAL)
>cv2.imshow("Gaussian", img)
>Gaussian = GaussianBlur()
>Gaussian.createTrackbar("Gaussian", img)
>cv2.waitKey(0)
>cv2.destroyAllWindows()
>print(Gaussian.getInfo())

>测试 GaussianBlur类  ThresholdTrackbar联动
>img = cv2.imread("img/1.jpg", 0)
>cv2.namedWindow("GaussianBlur", cv2.WINDOW_NORMAL)
>cv2.imshow("GaussianBlur", img)
>Gaussian = GaussianBlur()
>Gaussian.createTrackbar("GaussianBlur", img)
>cv2.waitKey(0)
>cv2.destroyAllWindows()
>print(Gaussian.getInfo())
		
>cv2.namedWindow("threshold", cv2.WINDOW_NORMAL)
>cv2.imshow("threshold", img)
>threshold = Threshold()
>threshold.createTrackbar("threshold", Gaussian.dstImg, isGray=True)
>cv2.waitKey(0)
>cv2.destroyAllWindows()
>print(threshold.getInfo())
