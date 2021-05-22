class PriorityQueue:
    """Priority Queue implemented with binary heap for efficiency"""

    def __init__(self):
        """Constructor for the binary heap"""
        self.size = 0
        self.capacity = 0
        self.array = []

    def is_empty(self):
        """Returns true if queue is empty false otherwise"""
        return self.size == 0

    def left_child(self, index):
        """Returns the left child of the node given as an index"""
        return (2 * index) + 1

    def right_child(self, index):
        """Returns the right child of the node given as an index"""
        return (2 * index) + 2

    def parent(self, index):
        """Returns the parent of the node given as an index"""
        return (index - 1) // 2

    def hasleftchild(self, index):
        """Checks if the indexed element has a left child"""
        return self.left_child(index) < len(self.array)

    def hasrightchild(self, index):
        """Checks if the indexed element has a right child"""
        return self.right_child(index) < len(self.array)

    def pop(self):
        """Returns the smallest element from the list and removes the element. Asserts a error if it is called on a
        empty list """
        if self.is_empty():
            assert "Empty List"

        min_el = self.array[0]
        self.array[0] = self.array[len(self.array) - 1]
        del self.array[len(self.array) - 1]
        self.downheap(0)
        return min_el

    def view(self):
        """Returns the smallest element from the list without removing it. Asserts a error if it is called on a
        empty list """
        if self.is_empty():
            assert "Empty List"

        return self.array[0]

    def push(self, element):
        """Adds the given element to the queue"""
        self.array.append(element)
        self.upheap(len(self.array) - 1)

    def upheap(self, index):
        """Corrects the heap property top down if it is broken"""
        while index > 0:
            parent = self.parent(index)
            if self.array[parent] == self.array[index] or self.array[index] > self.array[parent]:
                break
            temp = self.array[parent]
            self.array[parent] = self.array[index]
            self.array[index] = temp
            index = parent

    def __str__(self):
        """Prints the queue"""
        string = "[ "
        for k in range(0, len(self.array)):
            if k % 20 == 0 and k != 0:
                string += "\n"
            string += self.array[k].__str__() + " "
        string += "]\n"
        return string

    def downheap(self, index):
        """Corrects the heap property  bottom up if it is broken"""
        while self.hasrightchild(index) or self.hasleftchild(index):
            small = self.left_child(index)

            if self.hasrightchild(index):
                rc = self.right_child(index)

                if self.array[rc] < self.array[small]:
                    small = rc

            if self.array[small] == self.array[index] or self.array[small] > self.array[index]:
                break
            temp = self.array[small]
            self.array[small] = self.array[index]
            self.array[index] = temp
            index = small


if __name__ == '__main__':
    q = PriorityQueue()

    array = [3, 2, 1, 7, 8, 4, 10, 16, 12, 34, 12, 9, 13, 442, 40, 66, 23, 434, 42, 133, 432, 545, 2445, 53234, 545,
             24355, 532, 912, 2234]
    for k in range(0, len(array)):
        q.push(array[k])

    for k in range(0, len(array)):
        print(q)
