# this is comment
'''
this is multiline comment
whatever
'''

"""
or that one
"""
def printTable(T) :
    for i in range(len(T)) :
        print(str(i) + ' : ' + str(T[i]))
    return None

def Find(T, v) :
    for i in range(len(T)) :
        if T[i] == v : return True
    return False

def FindInRange(T, v, f, l) :
    for i in range(f, l) :
        if T[i] == v : return True
    return False

T = [33,112,24,345,476,245,116,47,86,59]
isFound = Find(T, 3)
isFoundInRange = FindInRange(T, 11, 0, 9)

def findMin(T) :
    r = 0;
    for i in range(len(T)) :
        if T[i] < T[r] : r = i
    return r

def findMinInRange(T, f, l) :
    r = f;
    for i in range(f + 1, l) :
        if T[i] < T[r] : r = i
    return r

def findMaxInRange(T, f, l) :
    r = f;
    for i in range(f + 1, l) :
        if T[i] > T[r] : r = i
    return r

def sort(T, order = 'asc') :
    for i in range(len(T)) :
        if order == 'asc' :
            index = findMinInRange(T, i, len(T))
        elif order == 'desc' : 
            index = findMaxInRange(T, i, len(T))

        T[i], T[index] = T[index], T[i]
    return None

def sortFunction(T, findSth) :
    for i in range(len(T)) :
            index = findSth(T, i, len(T))
            T[i], T[index] = T[index], T[i]
    return None

'''
    Create insertion sort method
'''
def noNameSort(T) :
    for i in range(len(T)) :
        for j in range(0, i) :
            if T[j] > T[i] :
                T[i], T[j] = T[j], T[i]
    return None

'''
    Proper insert sort
'''
def insertSort(T):
    for i in range(1, len(T)):
        temp = T[i]
        for j in range(i-1, -1, -1):
            if T[i] < T[j]:
                T[j+1] = T[j]
            else:
                break
            T[j+1] = temp
            
    return None


def insertSort2(tab):
    for i in range(1, len(tab)):
        temp = tab[i]
        for j in range(i-1, -2, -1):
            if temp < tab[j]:
                tab[j + 1] = tab[j]
            else:
                break
            print("j: {}".format(j))
        tab[j + 1] = temp;        


printTable(T)
print('\n')
print('Is found: ' + str(isFound))
print('Is found in range: ' + str(isFoundInRange))
print('Min in T index: ' + str(findMin(T)) + ', value: ' + str(T[findMin(T)]) + '\n')
findSth = findMinInRange
#sort(T, 'asc')
#sortFunction(T, findSth)
printTable(T)
print('\n')
findSth = findMaxInRange
#sort(T, 'desc')
#sortFunction(T, findSth)
#printTable(T)

insertSort2(T)
printTable(T)