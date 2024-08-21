class Node:
    def __init__(self, freq, char=None):
        self.left = None
        self.right = None
        self.freq = freq
        self.char = char

    def __lt__(self, other):
        return self.freq < other.freq


def buildHuffmanTree(freqMap):
    import heapq
    priorityQueue = [Node(freq, char) for char, freq in freqMap.items()]
    heapq.heapify(priorityQueue)
    while len(priorityQueue) > 1:
        left = heapq.heappop(priorityQueue)
        right = heapq.heappop(priorityQueue)
        merged = Node(left.freq + right.freq)
        merged.left = left
        merged.right = right
        heapq.heappush(priorityQueue, merged)
    return priorityQueue[0]


def huffmanDecoding(encodedText, root):
    decodedText = ''
    currentNode = root
    for bit in encodedText:
        if bit == '0':
            currentNode = currentNode.left
        else:
            currentNode = currentNode.right
        if currentNode.char is not None:
            decodedText += currentNode.char
            currentNode = root
    return decodedText


def decodeString(encodedText, freqMap):
    root = buildHuffmanTree(freqMap)
    return huffmanDecoding(encodedText, root)


if __name__ == "__main__":
    encodedText = "100011110111101010"
    freqMap = {'s': 4, 'm': 1, 'p': 2, 'i': 4}
    decodedText = decodeString(encodedText, freqMap)
    print("Decoded Text:", decodedText)