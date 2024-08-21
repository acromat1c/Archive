class mystic_number():
    def __init__(self):
         self.number = 0
    def mn(self,n):
        return n*(3*n-1)//2
    def __iter__(self):
        return self
    def __next__(self):
        self.number += 1
        return self.mn(self.number)

obj = mystic_number()
for i in range(1000):
    print(next(obj), "      ", end="")
    if (i-4)%5==0:print()