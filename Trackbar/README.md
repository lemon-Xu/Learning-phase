Trackbar
==============================================
Threshold(Trackbar)
----------------------------------------------
* createTrackbar(window, img, isGray=False)
  * window：窗口名称，唯一
  * img：cv2.imread("srcImg")
  * isGray：对要处理的图片进行BGR2GRAY转换
  * return: void
  
* trackbar.getInfo()
 * return: [posA, posB, WAY]
  * posA: 阖值
  * posB：灰度值
  * WAY： 转换方式
  
* 示例
img = cv2.imread("img/1.jpg", 1)
cv2.namedWindow("window", cv2.WINDOW_NORMAL)
cv2.imshow("window", img)
trackbar = Threshold()
trackbar.createTrackbar("window", img)
cv2.waitKey(0)
cv2.destroyAllWindows()
print(trackbar.getInfo())
-------------------------------------------------
