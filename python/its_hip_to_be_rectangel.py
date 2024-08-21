from sys import exit as sysExit

class Rectangle2D():
    def __init__(self):
        self._x = 0
        self._y = 0
        self._width = 0
        self._height = 0

    @property
    def x(self) -> float:
        return self._x
    @x.setter
    def x(self, x: float):
        try: float(x)
        except ValueError: print("x must be a float or integer")
        else: self._x = x
    @property
    def y(self) -> float:
        return self._y
    @y.setter
    def y(self, y: float):
        try: float(y)
        except ValueError: print("y must ba a float or integer")
        else: self._y = y

    @property
    def width(self) -> float:
        return self._width
    @width.setter
    def width(self, width: float):
        try: float(width)
        except ValueError: print("width must be a float or integer")
        else: self._width = width
    @property
    def height(self) -> float:
        return self._height
    @height.setter
    def height(self, height: float):
        try: float(height)
        except ValueError: print("width must be a float or integer")
        else: self._height = height

    def getArea(self) -> float:
        return self._width * self._height

    def getPerimeter(self) -> float:
        return self._width * 2 + self._height * 2

    def containsPoint(self, x:float, y:float) -> bool:
        try:
            float(x)
            float(y)
        except: print("both x and y must be float or int")
        else:
            if x > self._x and x < self._x + self._width and y > self._y and y < self._y + self._height: return True
            else: return False

    def contains(self, rectangle) -> bool:
        if self.containsPoint(rectangle.x,rectangle.y) and self.containsPoint(rectangle.x + rectangle.width,rectangle.y + rectangle.height):return True
        else: return False

    def overlaps(self, rectangle) -> bool:
        if self.containsPoint(rectangle.x,rectangle.y) or self.containsPoint(rectangle.x + rectangle.width,rectangle.y + rectangle.height):return True 
        else: return False

if __name__ == "__main__":
    r = Rectangle2D()
    r.x = 2
    r.y = 3
    r.width = 5
    r.height = 8
    t = Rectangle2D()
    t.x = 1
    t.y = 2
    t.width = 4
    t.height = 3
    y = Rectangle2D()
    y.x = 4
    y.y = 4
    y.width = 2
    y.height = 2
    
    print(r.containsPoint(3,4),r.containsPoint(0,0),r.containsPoint(1,4),r.containsPoint(3,1),r.containsPoint(10,10)) 
    print(r.contains(t),r.contains(y))
    print(r.overlaps(t),r.overlaps(y))