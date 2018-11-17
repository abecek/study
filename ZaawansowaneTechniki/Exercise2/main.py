import string
import random
count = 0

def match_at(T, W, i) :
    global count
    for j in range(0, len(W)) :
        if T[i+j] != W[j]:
            count += 1
            return False
    return True


def naive_search(T, W, tab):
    for i in range(len(T) - len(W) + 1):
        #if match_at(T, W, i):
        if T[i:i+len(W)] == W:
            #print("Found at: {}: T: ".format(i) + T[:i] + T[i:i+len(W)].upper() + T[i+len(W):])
            #print("Found at: {}: T: {}({}){}".format(i, T[:i], T[i:i + len(W)], T[i + len(W):]))
            #print("Found at: {}: T: {}".format(i, T))
            '''
            print(T)
            temp = " " * i
            print("{}{}".format(temp[0:i], "^"))
            tab.append(i)
            '''

            #print("Found at: {}: T: \n{}{}{}\n{}{}".format(i, T[:i], T[i:i + len(W)], T[i + len(W):], " " * i, "^"))
            print("Found at: {index}: T: \n{beg}{mid}{end}\n{spaces}{arrow}".format(
                index = i,
                beg = T[:i],
                mid = T[i:i + len(W)],
                end = T[i + len(W):],
                spaces =" " * i,
                arrow = "^"
            ))


def create_rand_str(length) :
    str = ""
    for i in range(length):
        str += random.choice(string.ascii_lowercase)
    return str

T = 'alamakota';
W = 'ma'
tab = [];
naive_search(T, W, tab);
print(tab);
print(count)

print(create_rand_str(10))

'''
print(T[3:5])
# od 3 wlacznie do 5 wylacznie [3-4], [3,5)
print(T[-2])
print(T[:5])
print(T[3:])
print(T[1:5:2])
print(T[len(T):0:-1])
print(T[5:2:-1]) # index 2 nie wchodzi(otwarte z prawej)
'''
