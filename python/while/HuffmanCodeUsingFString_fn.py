from Heap import Heap

def main():
    text = input("Enter a text: ").strip()
    
    counts = getCharacterFrequency(text) # Count frequency

    print(f"{'ASCII Code':<14s} {'Character':<14s}",
          f"{'Frequency':<14s} {'Code':<14s}")  
    
    tree = getHuffmanTree(counts) # Create a Huffman tree
    codes = getCode(tree.root) # Get codes
        
    for i in range(len(codes)):
        if counts[i] != 0: # (char)i is not in text if counts[i] is 0
            print(f"{i:<14d} {chr(i):<14s}",
                  f"{counts[i]:<14d} {codes[i]:<14s}")
 

# Get Huffman codes for the characters 
# This method is called once after a Huffman tree is built
def getCode(root):
    if root == None: 
        return None    
    codes = 128 * [0]
    assignCode(root, codes)
    return codes
  
# Recursively get codes to the leaf node 
def assignCode(root, codes):
    if root.left != None:
        root.left.code = root.code + "0"
        assignCode(root.left, codes)
      
        root.right.code = root.code + "1"
        assignCode(root.right, codes)
    else:
        codes[ord(root.element)] = root.code
  
# Get a Huffman tree from the codes   
def getHuffmanTree(counts):
    # Create a heap to hold trees
    heap = Heap() # Defined in Listing 17.9
    for i in range(len(counts)):
        if counts[i] > 0:
            heap.add(Tree(Node(counts[i], chr(i)))) # A leaf node tree
    
    while heap.getSize() > 1:
        t1 = heap.remove() # Remove the smallest-weight tree
        t2 = heap.remove() # Remove the next smallest 
        heap.add(Tree(t1, t2)) # Combine two trees

    return heap.remove() # The final tree
  
# Get the frequency of the characters 
def getCharacterFrequency(text):
    counts = 128 * [0] # 128 ASCII characters
    
    for i in range(len(text)):
        counts[ord(text[i])] += 1 # Count the characters in text
    
    return counts
  
# Define a Huffman coding tree 
class Tree:
    def __init__(self, t1, t2 = None):
        if t2 == None:
            self.root = t1
        else:
            self.root = Node()
            self.root.left = t1.root
            self.root.right = t2.root
            self.root.weight = t1.root.weight + t2.root.weight
    
    # Overload the comparison operators
    # Note we purposely reverse the order
    def __lt__(self, other): 
        return self.root.weight > other.root.weight 
        
    def __le__(self, other):
        return self.root.weight >= other.root.weight 
        
    def __gt__(self, other):
        return self.root.weight < other.root.weight 

    def __ge__(self, other):
        return self.root.weight <= other.root.weight 

class Node:
    # Create a node with the specified weight and character 
    def __init__(self, weight = None, element = None):
        self.weight = weight
        self.element = element
        self.left = None
        self.right = None
        self.code = ""

main()
