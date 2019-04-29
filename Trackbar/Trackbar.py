import cv2
import numpy as np
import random

# 0-Trackbar
class Trackbar():
	title = "title"
	window = "window"
	
	def __init__(self):
		self.dstImg = ""
		self.grayImg = ""
		
	def _callback(self):
		print("trackbar位置改变了:")
	
	def createTrackbar(self, title, window, start, end):
		cv2.createTrackbar(title, window, start, end, self.callback)
		self.window = window
		self.title = title
	
	def getInfo(self):
		pass
	
	def _cvtColor(self):
		pass
	
	def dst(self):
		return self.dstImg

# 1-ThersholdTrackbar
class Threshold(Trackbar):
	CV2_THRESH = ['cv2.THRESH_BINARY', 'cv2.THRESH_BINARY_INV', 'cv2.THRESH_TRUNC', 'cv2.THRESH_TOZERO',
			   'cv2.THRESH_TOZERO_INV']
	
	
	def __init__(self):
		self.posA = 0
		self.posB = 0
		self.THRESH = 0
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
		cv2.createTrackbar("THRESH", window, 0, 5, self._typeChange)
	
	def _positionA(self, position):
		self.posA = position
		self._callback()
	
	def _positionB(self, position):
		self.posB = position
		self._callback()
	
	def _typeChange(self, position):
		self.THRESH = position
		self._callback()
	
	def _callback(self):
		ret, self.dstImg = cv2.threshold(self.gray, self.posA, self.posB, self.THRESH)
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
		return [self.posA, self.posB, self.THRESH, self.CV2_THRESH[self.THRESH]]


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
		cv2.createTrackbar("ratio", window, 1, 3, self._positionRatio)
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
	
# 5-morphologyEx类
class morphologyEx(Trackbar):
	
	CV2_MORPH = [ "cv2.MORPH_ERODE", "cv2.MORPH_DILATE", "cv2.MORPH_OPEN", "cv2.MORPH_CLOSE", "cv2.MORPH_GRADIENT", "cv2.MORPH_TOPHAT", "cv2.MORPH_BLACKHAT" ]
	CV2_Structuring = ["cv2.MORPH_RECT", 'cv2.MORPH_CROSS', 'cv2.MORPH_ELLIPSE']
	
	
	def __init__(self):
		self.MORPH = 0
		self.structuring = 0
		self.ksize = 0
		self.kernel = (3, 3)
		self.img = ""
		self.gray = ""
		self.dstImg = ""
		

	def createTrackbar(self, window, img, isGray=False):
		self.window = window
		self.img = img
		if isGray:
			self.gray = img
		else:
			self._cvtColor()
		cv2.createTrackbar("ksize", self.window, 0, 20, self._positionA)
		cv2.createTrackbar("Structur", self.window, 0, len(self.CV2_Structuring) - 1, self._positionB)
		cv2.createTrackbar("MORPH", self.window, 0, len(self.CV2_MORPH)-1, self._positionC)

	def _positionA(self, position):
		# kernel = cv2.getStructuringElement(, (5, 5))
		if position != 0:
			self.ksize = position
			self.__changeValue()
			self._callback()
		
	def _positionB(self, position):
		self.structuring = position
		self._callback()
	
	def _positionC(self, position):
		self.MORPH = position
		self._callback()
	
	def _callback(self):
		kernel = cv2.getStructuringElement(self.structuring, self.kernel)
		self.dstImg = cv2.morphologyEx(self.gray, self.MORPH, kernel)
		cv2.imshow(self.window, self.dstImg)
	
	def __changeValue(self):
		value = self.ksize * 2 + 1
		self.kernel = (value, value)
	
	def _cvtColor(self):
		self.gray = cv2.cvtColor(self.img, cv2.COLOR_BGR2GRAY)
	
	def getInfo(self):
		return [self.CV2_MORPH[self.MORPH], self.CV2_Structuring[self.structuring], self.kernel]
	
	def dst(self):
		return self.dstImg
	
	
# 6 findContours类
class findContours(Trackbar):
	
	CV2_RETR = ['cv2.RETR_EXTERNAL', 'cv2.RETR_LIST', 'cv2.RETR_CCOMP', 'cv2.RETR_TREE']
	
	# 由于cv2.CHAIN_AOOROX以1开始，所以调用时要+1
	CV2_CHAIN_APPROX = ['cv2.CHAIN_APPROX_NONE', 'cv2.CHAIN_APPROX_SIMPLE', 'cv2.CHAIN_APPROX_TC89_L1',
						'cv2.CHAIN_APPROX_TC89_KCOS']
	
	
	def __init__(self):
		self.img = ''
		self.dstImg = ''
		self.gray = ''
		self.RETR = 0
		self.CHAIN_APPROX = 0
		self.window = ''
		self.point = (0, 0)
		
		
		
	def createTrackbar(self, window, img, isGray=False):
		self.window = window
		self.img = img
		self.dstImg = np.zeros(np.shape(img), dtype=np.uint8)
		if isGray:
			self.gray = img
		else:
			self._cvtColor()
		
		cv2.createTrackbar('RETR', self.window, 0, len(self.CV2_RETR) - 1, self.positionA)
		cv2.createTrackbar('CHAIN_APPROX', self.window, 0, len(self.CV2_CHAIN_APPROX) - 1, self.positionB)
		
	
	def positionA(self, position):
		self.RETR = position
		self._callback()
	
	def positionB(self, position):
		self.CHAIN_APPROX = position
		self._callback()
	
	def _callback(self):
		contours, heriachy = cv2.findContours(self.gray.copy(), self.RETR, self.CHAIN_APPROX + 1)
		for contour in enumerate(contours):
			cv2.drawContours(self.dstImg, contour, 1, (255, 255, 255), 2)
		cv2.imshow(self.window, self.dstImg)
	
	def _color(self):
		return random.randint(0, 255)
	
	def _cvtColor(self):
		self.gray = cv2.cvtColor(self.img, cv2.COLOR_BGR2GRAY)
	
	def getInfo(self):
		return (self.CV2_RETR[self.RETR], self.CV2_CHAIN_APPROX[self.CHAIN_APPROX])
	
	def dst(self):
		return self.dstImg
	
	
	
	
	
if __name__ == "__main__":
	i = 7
	
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
		img = cv2.imread("img/1.jpg", 0)
		cv2.namedWindow("threshold", cv2.WINDOW_NORMAL)
		cv2.imshow("threshold", img)
		threshold = Threshold()
		threshold.createTrackbar("threshold", img, True)
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
		
	
	
	if i == 6:
		#6 测试 morphologyEx类
		# CV2_MORPH = [cv2.MORPH_ERODE, cv2.MORPH_DILATE, cv2.MORPH_OPEN, cv2.MORPH_CLOSE, cv2.MORPH_GRADIENT,
		# 			 cv2.MORPH_TOPHAT, cv2.MORPH_BLACKHAT]
		# print(CV2_MORPH[  len(CV2_MORPH) - 1  ])
		#
		# print(cv2.MORPH_RECT, cv2.MORPH_CROSS, cv2.MORPH_ELLIPSE)
		
		img = cv2.imread('img/1.jpg')
		cv2.namedWindow('morph', cv2.WINDOW_NORMAL)
		cv2.imshow('morph', img)
		morph = morphologyEx()
		morph.createTrackbar('morph', img)
		cv2.waitKey(0)
		cv2.destroyAllWindows()
		print(morph.getInfo())
		
		
	if i == 7:
		#7 测试findContours类 与 threshold类联动
		# CV2_RETR = [cv2.RETR_EXTERNAL, cv2.RETR_LIST, cv2.RETR_CCOMP, cv2.RETR_TREE]
		# CV2_CHAIN_APPROX = [cv2.CHAIN_APPROX_NONE, cv2.CHAIN_APPROX_SIMPLE, cv2.CHAIN_APPROX_TC89_L1, cv2.CHAIN_APPROX_TC89_KCOS]
		# print(CV2_RETR)
		# print(CV2_CHAIN_APPROX)
		
		img = cv2.imread("img/1.jpg", 0)
		cv2.namedWindow("threshold", cv2.WINDOW_NORMAL)
		cv2.imshow("threshold", img)
		threshold = Threshold()
		threshold.createTrackbar("threshold", img, True)
		cv2.waitKey(0)
		cv2.destroyAllWindows()
		print(threshold.getInfo())
		
		
		cv2.namedWindow('findContours', cv2.WINDOW_NORMAL)
		cv2.imshow('findContours', threshold.dst())
		fc = findContours()
		fc.createTrackbar('findContours', threshold.dst(), True)
		cv2.waitKey(0)
		cv2.destroyAllWindows()
		print(fc.getInfo())
		
