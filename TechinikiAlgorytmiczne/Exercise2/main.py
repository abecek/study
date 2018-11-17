import random
import string
import matplotlib.pyplot as plt

count = 0

def random_str(size, alphabet = string.ascii_lowercase):
    result = ""
    for _ in range(size):
        result += random.choice(alphabet)
    return result


def match_at(T, P, i) :
    global count
    for j in range(0, len(P)):
        if T[i+j] != P[j]:
            count += 1
            return False
    return True


def naive_search(T, P, A = []):
    result = []
    for i in range(len(T) - len(P) + 1):
        if match_at(T, P, i):
            result.append(i)
    return result


def sunday_search(T, P, A):
    result = []
    # Temp init
    Temp = {}
    for i in range(len(A)):
        Temp[A[i]] = -1

    for j in range(len(P)):
        Temp[P[j]] = j
    #print(Temp)

    k = 0
    while k <= len(T) - len(P):
        if match_at(T, P, k):
            result.append(k)
        k += len(P)
        if k < len(T):
            k -= Temp[T[k]]
    return result


def test_alg(T, P, alg, A = []):
    global count
    count = 0
    alg(T, P, A)
    return count



SAMPLE_SIZE = 5
A = string.ascii_lowercase[:4]
P = random_str(5, A)
x = []
y_naive_search = []
y_sunday_search = []

"""
print(A)
print(P)
print('Naive:')
print(naive_search(P,"cba"))
print('Sunday:')
print(sunday_search(P,"cba",A))
"""

for T_size in range(1, 10000, 1000):
    x.append(T_size)
    naive_search_result = 0
    sunday_search_result = 0
    for _ in range(SAMPLE_SIZE):
        T = random_str(T_size, A)
        naive_search_result += test_alg(T, P, naive_search)
        sunday_search_result += test_alg(T, P, sunday_search, A)
    naive_search_result /= SAMPLE_SIZE
    sunday_search_result /= SAMPLE_SIZE
    y_naive_search.append(naive_search_result)
    y_sunday_search.append(sunday_search_result)

plt.figure(1)
plt.plot(x, y_naive_search, label = "naive")
plt.plot(x, y_sunday_search, label = "sunday")
plt.xlabel("|T|")
plt.ylabel("liczba porownan")
plt.title("|P| = " + str(len(P)) + ", |A| = " + str(len(A)))
plt.legend()


SAMPLE_SIZE = 5
A = string.ascii_lowercase[:4]
T = random_str(10000, A)
x = []
y_naive_search = []
y_sunday_search = []

for P_size in range(1, 10000, 1000):
    x.append(P_size)
    naive_search_result = 0
    sunday_search_result = 0
    for _ in range(SAMPLE_SIZE):
        P = random_str(P_size, A)
        naive_search_result += test_alg(T, P, naive_search)
        sunday_search_result += test_alg(T, P, sunday_search, A)
    naive_search_result /= SAMPLE_SIZE
    sunday_search_result /= SAMPLE_SIZE
    y_naive_search.append(naive_search_result)
    y_sunday_search.append(sunday_search_result)

plt.figure(2)
plt.plot(x, y_naive_search, label = "naive")
plt.plot(x, y_sunday_search, label = "sunday")
plt.xlabel("|P|")
plt.ylabel("liczba porownan")
plt.title("|T| = 10000, |A| = 4")
plt.legend()


#print(random_str(20, string.ascii_lowercase))
#print(random_str(20, string.ascii_lowercase[:3]))


SAMPLE_SIZE = 5
x = []
y_naive_search = []
y_sunday_search = []

for A_size in range(1, 24, 1):
    A = string.ascii_lowercase[:A_size]
    P = random_str(10, A)
    x.append(A_size)
    naive_search_result = 0
    sunday_search_result = 0
    for _ in range(SAMPLE_SIZE):
        T = random_str(10000, A)
        P = random_str(1000, A)
        naive_search_result += test_alg(T, P, naive_search)
        sunday_search_result += test_alg(T, P, sunday_search, A)
    naive_search_result /= SAMPLE_SIZE
    sunday_search_result /= SAMPLE_SIZE
    y_naive_search.append(naive_search_result)
    y_sunday_search.append(sunday_search_result)

plt.figure(3)
plt.plot(x, y_naive_search, label = "naive")
plt.plot(x, y_sunday_search, label = "sunday")
plt.xlabel("|A|")
plt.ylabel("liczba porownan")
plt.title("|T| = 10000, |P| = 1000")
plt.legend()
plt.show()

