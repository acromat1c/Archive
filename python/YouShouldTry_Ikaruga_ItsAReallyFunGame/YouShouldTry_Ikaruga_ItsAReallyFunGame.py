DEFAULT_INITIAL_CAPACITY = 4
DEFAULT_MAX_LOAD_FACTOR = 0.75
MAXIMUM_CAPACITY = 2 ** 30

class Map:
    def __init__(self, capacity=DEFAULT_INITIAL_CAPACITY, loadFactorThreshold=DEFAULT_MAX_LOAD_FACTOR):
        self.capacity = capacity
        self.loadFactorThreshold = loadFactorThreshold
        self.table = [None] * self.capacity
        self.size = 0

    def put(self, key, value):
        if self.size >= self.capacity * self.loadFactorThreshold:
            if self.capacity == MAXIMUM_CAPACITY:
                raise RuntimeError("Exceeding maximum capacity")
            self.rehash()

        index = self.getHash(hash(key))
        original_index = index
        while self.table[index] is not None and self.table[index][0] != key:
            index = (index + 1) % self.capacity  # Linear probing
            if index == original_index:
                raise RuntimeError("Map is full and couldn't find a suitable place to insert")

        self.table[index] = (key, value)
        self.size += 1

    def get(self, key):
        index = self.getHash(hash(key))
        original_index = index
        while self.table[index] is not None:
            if self.table[index][0] == key:
                return self.table[index][1]
            index = (index + 1) % self.capacity  # Linear probing
            if index == original_index:
                break
        return None

    def remove(self, key):
        index = self.getHash(hash(key))
        original_index = index
        while self.table[index] is not None:
            if self.table[index][0] == key:
                self.table[index] = None
                self.size -= 1
                return
            index = (index + 1) % self.capacity  # Linear probing
            if index == original_index:
                break

    def containsKey(self, key):
        return self.get(key) is not None

    def containsValue(self, value):
        for entry in self.table:
            if entry and entry[1] == value:
                return True
        return False

    def items(self):
        return [(entry[0], entry[1]) for entry in self.table if entry is not None]

    def getAll(self, key):
        return tuple(entry[1] for entry in self.table if entry and entry[0] == key)

    def keys(self):
        return tuple(entry[0] for entry in self.table if entry is not None)

    def values(self):
        return tuple(entry[1] for entry in self.table if entry is not None)

    def clear(self):
        self.table = [None] * self.capacity
        self.size = 0

    def getSize(self):
        return self.size

    def isEmpty(self):
        return self.size == 0

    def rehash(self):
        temp = self.items()
        self.capacity *= 2
        self.table = [None] * self.capacity
        self.size = 0
        for key, value in temp:
            self.put(key, value)

    def toString(self):
        return str(self.items())

    def setLoadFactorThreshold(self, threshold):
        self.loadFactorThreshold = threshold

    def getTable(self):
        return str(self.table)

    def getHash(self, hashCode):
        return self.supplementalHash(hashCode) & (self.capacity - 1)

    def supplementalHash(self, h):
        h ^= (h >> 20) ^ (h >> 12)
        return h ^ (h >> 7) ^ (h >> 4)