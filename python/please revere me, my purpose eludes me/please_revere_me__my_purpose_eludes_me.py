from math import sqrt





class Triangle():
    def __init__(self):
        self._side1=1.0
        self._side2=1.0
        self._side3=1.0
    
    @property
    def side1(self) -> float:
        return self._side1
    @side1.setter
    def side1(self,i:float or int) -> None:
        try: 
            float(i)
            if i <= 0:raise
        except: pass
        else: self._side1 = i
    
    @property
    def side2(self) -> float:
        return self._side2
    @side2.setter
    def side2(self,i:float or int) -> None:
        try: 
            float(i)
            if i <= 0:raise
        except: pass
        else: self._side2 = i
    
    @property
    def side3(self) -> float:
        return self._side3
    @side3.setter
    def side3(self,i:float or int) -> None:
        try: 
            float(i)
            if i <= 0:raise
        except: pass
        else: self._side3 = i
    
    def getArea(self) -> float:
        s = (self._side1 + self._side2 + self._side3)/2
        self.area = sqrt(s*(s-self._side1)*(s-self._side2)*(s-self._side3))
        return self.area
    
    def getPerimeter(self) -> float:
        self.parimeter = self._side1 + self._side2 + self._side3
        return self.parimeter
    
    def __str__(self) -> str:
        return "Triangle: side1 = " + str(self._side1) + " side2 = " + str(self._side2) + " side3 = " + str(self._side3)
    




if __name__ == "__main__":
    t = Triangle()
    try:
        t.side1 = float(input("side 1 (float): "))
        t.side2 = float(input("side 2 (float): "))
        t.side3 = float(input("side 3 (float): "))
        t.getArea()
        color = input("color (str): ")
        fill = bool(input("fill (bool): "))
    except: print("user error. self destruct timer started! please do not shut down your computer")
    else: print("\nThe area is",t.getArea(),"\nThe perimeter is",t.getPerimeter(),"\nColor is",color,"\nFilled is",fill,"\n")