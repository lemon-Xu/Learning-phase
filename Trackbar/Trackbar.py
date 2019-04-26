import cv2
import numpy as np


# 0-Trackbar
class Trackbar():
	title = "title"
	window = "window"
	
	def __init__(self):
		self.dstImg = ""
	
	def _callback(self, position):
		print("trackbar位置改变了:", position)
	
	def createTrackbar(self, title, window, start, end):
		cv2.createTrackbar(title, window, start, end, self.callback)
		self.window = window
		self.title = title
	
	def getInfo(self):
		pass
	
	def dst(self):
		return self.dstImg

# 1-ThersholdTrackbar
class Threshold(Trackbar):
	CV2_WAY = ['cv2.THRESH_BINARY', 'cv2.THRESH_BINARY_INV', 'cv2.THRESH_TRUNC', 'cv2.THRESH_TOZERO',
			   'cv2.THRESH_TOZERO_INV']
	
	
	def __init__(self):
		self.posA = 0
		self.posB = 0
		self.WAY = 0
		self.img = ""
		self.dstImg = ""
		self.gray = ""
	
	def createTrackbar(self, window, img, isGray=False):
		self.img = img
		self.dstImg = img
		self.window = window
		if isGray:
			self.gray = img
		else:
			self._cvtColor()
		cv2.createTrackbar("A", window, 0, 255, self._positionA)
		cv2.createTrackbar("B", window, 0, 255, self._positionB)
		cv2.createTrackbar("WAY", window, 0, 5, self._typeChange)
	
	def _positionA(self, position):
		self.posA = position
		self._callback()
	
	def _positionB(self, position):
		self.posB = position
		self._callback()
	
	def _typeChange(self, position):
		self.WAY = position
		self._callback()
	
	def _callback(self):
		ret, self.dstImg = cv2.threshold(self.gray, self.posA, self.posB, self.WAY)
		cv2.imshow(self.window, self.dstImg)
	
	def _cvtColor(self):
		self.gray = cv2.cvtColor(self.img, cv2.COLOR_BGR2GRAY)
	
	def setImg(self, img, isGray=False):
		self.img = img
		if isGray:
			self._cvtColor()
		else:
			self.gray = img
	
	def getInfo(self):
		return [self.posA, self.posB, self.WAY, self.CV2_WAY[self.WAY]]


# 3-GaussianBlur类
class GaussianBlur(Trackbar):
	
	
	def __init__(self):
		self.keinel = (0, 0)
		self.posB = 0
	
	def createTrackbar(self, window, img):
		self.window = window
		self.img = img
		self.dstImg = img
		cv2.createTrackbar("ksize", window, 0, 20, self._positionA)
		cv2.createTrackbar("poB", window, 0, 50, self._positionB)
	
	def _callback(self):
		self.dstImg = cv2.GaussianBlur(self.img, self.kernel, self.posB)
		cv2.imshow(self.window, self.dstImg)
	
	def _positionA(self, position):
		self.posA = position * 2 + 1
		self.kernel = (self.posA, self.posA)
		self._callback()
	
	def _positionB(self, position):
		self.posB = position
		self._callback()
	
	
	def getInfo(self):
		return [self.kernel, self.posB]
	
# 4-Canny类
class Canny(Trackbar):
	
	def __init__(self):
		self.threshold = 0
		self.ratio = 0
		self.minThreshold = 0
		self.maxThreshold = 0
		self.img = ""
		self.dstImg = ""
	
	def createTrackbar(self, window, img):
		self.window = window
		cv2.createTrackbar("threshold", window, 0, 500, self._positionThreshold)
		cv2.createTrackbar("threshold ratio", window, 1, 3, self._positionRatio)
		self.img = img
		
	def _positionThreshold(self, position):
		self.threshold = position
		self._changeValue()
		self._callback()
	
	def _positionRatio(self, position):
		self.ratio = position
		self._changeValue()
		self._callback()
	
	
	def _changeValue(self):
		self.minThreshold = self.threshold
		self.maxThreshold = self.threshold * self.ratio
	
	def _callback(self):
		self.dstImg = cv2.Canny(self.img, self.minThreshold, self.maxThreshold)
		cv2.imshow(self.window, self.dstImg)
	
	def getInfo(self):
		return [self.minThreshold, self.maxThreshold, self.ratio]
	
	
	
if __name__ == "__main__":
	i = 5
	
	if i == 0:
		# 测试Trackbar类
		img = cv2.imread("img/1.jpg", 1)
		
		cv2.imshow("window", img)
		trackbar = Trackbar()
		trackbar.createTrackbar("title", "window", 3, 5)
		cv2.waitKey(0)
	
	if i == 1:
		# 测试Threshold类
		img = cv2.imread("img/1.jpg", 1)
		cv2.namedWindow("threshold", cv2.WINDOW_NORMAL)
		cv2.imshow("threshold", img)
		threshold = Threshold()
		threshold.createTrackbar("threshold", img)
		cv2.waitKey(0)
		cv2.destroyAllWindows()
		print(threshold.getInfo())
	
	if i == 2:
		# 测试GaussianBlur类
		img = cv2.imread("img/1.jpg", 1)
		cv2.namedWindow("Gaussian", cv2.WINDOW_NORMAL)
		cv2.imshow("Gaussian", img)
		Gaussian = GaussianBlur()
		Gaussian.createTrackbar("Gaussian", img)
		cv2.waitKey(0)
		cv2.destroyAllWindows()
		print(Gaussian.getInfo())
		
	if i == 3:
		# 测试ThresholdTrackbar GaussianBlur类联动
		img = cv2.imread("img/1.jpg", 1)
		cv2.namedWindow("threshold", cv2.WINDOW_NORMAL)
		cv2.imshow("threshold", img)
		threshold = Threshold()
		threshold.createTrackbar("threshold", img)
		cv2.waitKey(0)
		cv2.destroyAllWindows()
		print(threshold.getInfo())
		
		cv2.namedWindow("Gaussian", cv2.WINDOW_NORMAL)
		cv2.imshow("Gaussian", threshold.dst())
		Gaussian = GaussianBlur()
		Gaussian.createTrackbar("Gaussian", threshold.dstImg)
		cv2.waitKey(0)
		cv2.destroyAllWindows()
		print(Gaussian.getInfo())
		
	if i == 4:
		# 测试 GaussianBlur类  ThresholdTrackbar联动
		img = cv2.imread("img/1.jpg", 0)
		cv2.namedWindow("GaussianBlur", cv2.WINDOW_NORMAL)
		cv2.imshow("GaussianBlur", img)
		Gaussian = GaussianBlur()
		Gaussian.createTrackbar("GaussianBlur", img)
		cv2.waitKey(0)
		cv2.destroyAllWindows()
		print(Gaussian.getInfo())
		
		cv2.namedWindow("threshold", cv2.WINDOW_NORMAL)
		cv2.imshow("threshold", img)
		threshold = Threshold()
		threshold.createTrackbar("threshold", Gaussian.dstImg, isGray=True)
		cv2.waitKey(0)
		cv2.destroyAllWindows()
		print(threshold.getInfo())
	
	if i == 5:
		# 测试 Canny类
		img = cv2.imread("img/1.jpg", 1)
		cv2.namedWindow("Canny", cv2.WINDOW_NORMAL)
		cv2.imshow("Canny", img)
		canny = Canny()
		canny.createTrackbar("Canny", img)
		cv2.waitKey(0)
		cv2.destroyAllWindows()
