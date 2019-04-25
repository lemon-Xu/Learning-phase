import cv2
import numpy as np


# 0-Trackbar
class Trackbar():
	title = "title"
	window = "window"
	
	def __init__(self):
		pass
	
	def callback(self, position):
		print("trackbar位置改变了:", position)
	
	def createTrackbar(self, title, window, start, end):
		cv2.createTrackbar(title, window, start, end, self.callback)
		self.window = window
		self.title = title
	
	def getPos(self):
		return cv2.getTrackbarPos(self.title, self.window)


# 1-ThersholdTrackbar
class Threshold(Trackbar):
	CV2_WAY = ['cv2.THRESH_BINARY', 'cv2.THRESH_BINARY_INV', 'cv2.THRESH_TRUNC', 'cv2.THRESH_TOZERO',
			   'cv2.THRESH_TOZERO_INV']
	WAY = 0
	img = ""
	dstImg = ""
	gray = ""
	
	def __init__(self):
		self.posA = 0
		self.posB = 0
	
	def createTrackbar(self, window, img, isGray=False):
		self.img = img
		self.dstImg = img
		self.window = window
		if isGray:
			self.gray = img
		else:
			self.cvtColor()
		cv2.createTrackbar("A", window, 0, 255, self.positionA)
		cv2.createTrackbar("B", window, 0, 255, self.positionB)
		cv2.createTrackbar("WAY", window, 0, 3, self.typeChange)
	
	def positionA(self, position):
		self.posA = position
		self.callback()
	
	def positionB(self, position):
		self.posB = position
		self.callback()
	
	def typeChange(self, position):
		self.WAY = position
		self.callback()
	
	def callback(self):
		ret, self.dstImg = cv2.threshold(self.gray, self.posA, self.posB, self.WAY)
		cv2.imshow(self.window, self.dstImg)
	
	def cvtColor(self):
		self.gray = cv2.cvtColor(self.img, cv2.COLOR_BGR2GRAY)
	
	def setImg(self, img):
		self.img = img
		self.cvtColor()
	
	def dstImg(self):
		return self.dstImg
	
	def getInfo(self):
		return [self.posA, self.posB, self.WAY, self.CV2_WAY[self.WAY]]


# 3-GaussianBlur类
class GaussianBlur(Trackbar):
	keinel = (0, 0)
	posB = 0
	
	def __init__(self):
		pass
	
	def createTrackbar(self, window, img):
		self.window = window
		self.img = img
		self.dstImg = img
		cv2.createTrackbar("ksize", window, 0, 20, self.positionA)
		cv2.createTrackbar("poB", window, 0, 50, self.positionB)
	
	def callback(self):
		self.dstImg = cv2.GaussianBlur(self.img, self.kernel, self.posB)
		cv2.imshow(self.window, self.dstImg)
	
	def positionA(self, position):
		self.posA = position * 2 + 1
		self.kernel = (self.posA, self.posA)
		self.callback()
	
	def positionB(self, position):
		self.posB = position
		self.callback()
	
	def dstImg(self):
		return self.dstImg
	
	def getInfo(self):
		return [self.kernel, self.posB]
	
	
	
if __name__ == "__main__":
	i = 4
	
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
		cv2.imshow("Gaussian", threshold.dstImg)
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
