import matplotlib.pyplot as plt
import random
import string

def random_str(size, alphabet = string.ascii_lowercase):
    result = ""
    for _ in range(size):
        result += random.choice(alphabet)
    return result

counter = 0

def match_at(T, W, i):
    global counter
    for j in range(len(W)):
        counter += 1
        if T[i+j] != W[j]: return False
    return True

def naive_search(T, W):
    for i in range(len(T)-len(W)+1):
        if match_at(T, W, i):
            pass
        
def test_alg(T, W, alg):
    global counter
    counter = 0
    alg(T, W)
    return counter

SAMPLE_SIZE = 10
A = string.ascii_lowercase[:4]
W = random_str(5, A)
x = []
y_naive_search = []
#y_sunday_search = [] #TODO
for T_size in range(1, 1000, 10):
    x.append(T_size)
    naive_search_res = 0
    #sunday_search_res = 0 #TODO
    for _ in range(SAMPLE_SIZE):
        T = random_str(T_size, A)
        naive_search_res += test_alg(T, W, naive_search)
        # sunday_search_res += test_alg(T, W, sunday_search)
    naive_search_res /= SAMPLE_SIZE
    #sunday_search_res /= SAMPLE_SIZE
    y_naive_search.append(naive_search_res)
    #y_sunday_search.append(sunday_search_res)

plt.plot(x, y_naive_search, label='naive')
#plt.plot(x, y_sunday_search, label='sunday')
plt.xlabel('|T|')
plt.ylabel('liczba porównań')
plt.title("|W|=5, |A|=4")
plt.legend()
plt.show()
