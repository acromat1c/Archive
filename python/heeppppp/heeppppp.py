class Heap:
    def __init__(self):
        self.__lst = []

    # Add a new item into the lst 
    def add(self, e):
        self.__lst.append(e)  # Append to the lst
        # The index of the last node
        currentIndex = len(self.__lst) - 1  
    
        while currentIndex > 0:
            parentIndex = (currentIndex - 1) // 2
            # Swap if the current item is greater than its parent
            if self.__lst[currentIndex] < self.__lst[parentIndex]: 
                self.__lst[currentIndex], self.__lst[parentIndex] = \
                    self.__lst[parentIndex], self.__lst[currentIndex]
            else:
                break  # The tree is a lst now
    
            currentIndex = parentIndex

    # Remove the root from the lst 
    def remove(self):
        if len(self.__lst) == 0:
            return None
    
        removedItem = self.__lst[0]
        self.__lst[0] = self.__lst[len(self.__lst) - 1]
        self.__lst.pop(len(self.__lst) - 1) # Remove the last item
    
        currentIndex = 0
        while currentIndex < len(self.__lst):
            leftChildIndex = 2 * currentIndex + 1
            rightChildIndex = 2 * currentIndex + 2
          
            # Find the maximum between two children
            if leftChildIndex >= len(self.__lst): 
                break  # The tree is a lst
            maxIndex = leftChildIndex
            if rightChildIndex < len(self.__lst):
                if self.__lst[maxIndex] < self.__lst[rightChildIndex]:
                    maxIndex = rightChildIndex
          
            # Swap if the current node is less than the maximum 
            if self.__lst[currentIndex] < self.__lst[maxIndex]:
                self.__lst[maxIndex], self.__lst[currentIndex] = \
                    self.__lst[currentIndex], self.__lst[maxIndex]
                currentIndex = maxIndex
            else:
                break  # The tree is a lst
    
        return removedItem
  
    # Returns the size of the heap
    def getSize(self):
        return len(self.__lst)

    # Returns True if the heap is empty
    def isEmpty(self):
        return self.getSize() == 0

    # Returns the largest element in the heap without removing it
    def peek(self):
        return self.__lst[0]
        
    # Returns the list in the heap
    def getLst(self):
        return self.__lst

    def __str__(self):
        return str(self.__lst)



if __name__ == "__main__":
    heap = Heap()
    heap.add(5)
    heap.add(4)
    heap.add(8)
    heap.add(2)
    heap.add(3)
    heap.add(1)
    heap.add(6)
    heap.add(11)
    heap.add(26)
    heap.add(23)
    heap.add(17)
    heap.add(7)
    heap.add(18)
    heap.add(12)
    heap.add(13)
    print(heap)