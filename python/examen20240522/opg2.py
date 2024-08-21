class AA:
	def __init__(self,x=0):
		self.x = x
	def doit(self,x):
		self.x=self.x+2

class BB(AA):
	def __init__(self,y=0):
		super().__init__(4)
		self.y=y
	def doit(self):
		self.y+=3

def main():
	obj=BB()
	obj.doit()
	print(obj.x,obj.y)

main()