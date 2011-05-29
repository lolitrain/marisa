import math

class vector:
    def __init__(self, vec):
        self.vec = vec

    def __sub__(self, other):
        return vector(tuple((x-y for x,y in zip(self.vec, other.vec))))

    def __add__(self, other):
        return vector(tuple((x+y for x,y in zip(self.vec, other.vec))))

    def dot(self, other):
        return math.sqrt(sum((x*y for x,y in zip(self.vec, other.vec))))

    def length(self):
        return self.dot(self)

    def normalize(self):
        length = self.length()
        return vector(tuple((x/length for x in self.vec)))

    def __mul__(self, n):
        return vector(tuple((x*n for x in self.vec)))

    def __str__(self):
        return str(self.vec)
    
    def __getitem__(self, i):
        return self.vec[i]
