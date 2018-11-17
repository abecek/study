import matplotlib.pyplot as plt

class EmptyClass: pass
class DeletedCell: pass
# empty classes above


s = None
print(s is EmptyClass)
s = EmptyClass
print( s is EmptyClass)
[EmptyClass] * 10
# array len 10 of EmptyCell


class SimpleSet:

    # *args - 0 or more arguments
    def __init__(self, *args):
        self._tab = [] # sth like private, just convention
        self._counter = 0
        for v in args: self.insert(v)

    def find(self, val):
        return self._find(val) != -1

    def insert(self, val):
        if not self.find(val):
            self._tab.append(val)

    def erase(self, val):
        i = self._find(val)
        if i != -1:
            self._tab[i] = self._tab[-1]
            self._tab.pop(i)
            # del self._tab[i]

    '''
    def _find(self, val):
        for i in range(len(self._tab)):
            self._counter += 1
            if self._tab[i] == val:
                return i
        return -1
    '''

    def _find(self, val):
        for k, v in enumerate(self._tab):
            self._counter += 1
            if v == val:
                return k
        return -1

    def get_count(self):
        return self._counter

    def __str__(self):
        return str(self._tab)

    def __repr__(self):
        return "SimpleSet({})".format(", ".join(repr(v) for v in self._tab))
        # return "SimpleSet({})".format(str(self)[1:-1])

    def __len__(self):
        return len(self._tab)


s = SimpleSet(8, "zzz", 8)

s.insert(1)
s.insert("abc")
s.insert(2)
s.insert(None)
s.erase(2)
s.insert(34)

print(s.find(None))
print(s.find("abc"))
print(s.find(2))
print(str(s))
print(repr(s))
print(len(s))
print(hash(1))
print(hash("abc")%100)

s1 = SimpleSet()
x = []
y = []
for i in range(1, 1001):
    x.append(i)
    s1.insert(i)
    s1.find(0)
    y.append(s1.get_count())

plt.plot(x, y, label="SimpleSet")
plt.xlabel("len")
plt.ylabel("Find count")
plt.legend()
plt.show()
