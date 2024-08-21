class Bin():  

    def packBin(*args:int) -> str:
        bins = [Bin()]
        optimalPairs = {}
        for item in args:
            if item <= 10:
                optimal = bins[len(bins)-1].maxWeight - item
                if item in optimalPairs: 
                    bins[optimalPairs[item]].addItem(item)
                    optimalPairs.pop(item)
                else:
                    bins[len(bins)-1].addItem(item)
                    optimalPairs[optimal] = len(bins)-1
                    bins.append(Bin())
        return bins[:-1]

    def __init__(self, maxWeight = 10):
        self.maxWeight = maxWeight
        self._totalWeight = 0
        self.objects = []
    
    @property
    def totalWeight(self):
        return self._totalWeight

    def addItem(self, weight):
        if self._totalWeight + weight <= self.maxWeight:
            self.objects.append(weight)
            self._totalWeight += weight
            return True
        else:
            return False
    
    def getNumberOfObjects(self):
        return len(self.objects)
    
    def __str__(self):
        output = ""        
        for e in self.objects:
            output += str(e) + " "

        return "|"+output.rstrip()+"|"

if __name__ == "__main__":
    print(*Bin.packBin(7,5,2,3,5,8))