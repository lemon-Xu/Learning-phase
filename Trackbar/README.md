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
  
  
-------------------------------------------------
