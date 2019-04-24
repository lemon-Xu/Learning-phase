Trackbar
==============================================
Threshold(Trackbar)
----------------------------------------------
*createTrackbar(window, img, isGray=False)
  *window：窗口名称，唯一
  *img：cv2.imread("srcImg")
  *isGray：对要处理的图片进行BGR2GRAY转换
  *return: void
  
*trackbar.getInfo()
  *return: [posA, posB, WAY]
  *posA: 阖值
  *posB：灰度值
  *WAY： 转换方式
  
示例
img = cv2.imread("img/1.jpg", 1) \<br>
cv2.namedWindow("window", cv2.WINDOW_NORMAL) \<br>
cv2.imshow("window", img) \<br>
trackbar = Threshold() \<br>
trackbar.createTrackbar("window", img) \<br>
cv2.waitKey(0) \<br>
cv2.destroyAllWindows() \<br>
print(trackbar.getInfo()) \<br>
-------------------------------------------------
