class LinkedList:

    def __init__(self):
        self.__head = None
        self.__tail = None
        self.__size = 0

    # Return the size of the list
    def getSize(self):
        return self.__size

    # Add an element to the end of the list
    def add(self, e):
        newNode = Node(e) # Create a new node for e   

        if self.__tail == None:
            self.__head = self.__tail = newNode # The only node in list
        else:
            self.__tail.next = newNode # Link the new with the last node
            self.__tail = self.__tail.next # tail now points to the last node  

        self.__size += 1 # Increase size

   

    # return a reference to the node with this index
    def get_node(self, index):
        val = self.__head
        for _ in range(index):
            val = val.next
        return val.element
   

   
    # swap current with next
    def swap_with_next(self, prev, current, next):
        n1 = self.__head
        n2 = n1.next
        n3 = n2.next
        while True:
            if n1.element == prev and n2.element == current and n3.element == next:
                n2.element, n3.element = n3.element, n2.element
                break
            else:
                if n3.next:
                    n1 = n2
                    n2 = n3
                    n3 = n3.next
                else:
                    break


    def __str__(self):
        result = "["
        current = self.__head
        while current != None:
            result += str(current.element)
            current = current.next
            if current != None:
                result += ", " # Separate two elements with a comma
            else:
                result += "]" # Insert the closing ] in the string

        return result


   

# The Node class
class Node:
    def __init__(self, e):
        self.element = e
        self.next = None


# test it
lst = LinkedList()
lst.add("One")
lst.add("Two")
lst.add("Three")
print(lst)
lst.swap_with_next(lst.get_node(0), lst.get_node(1), lst.get_node(2))
print(lst)