import math as m
from decimal import Decimal as D
'''
import math as m
import cmath as cm
from math import sin, cos
from cmath import *
from math import tan as tg
'''
'''
print(math.pi)
print(m.sin(0))
print(cos(11))
print(tg(1))
'''

print(pow(m.cos(m.pi/3), 2))

print(m.ceil(5*m.log2(20)))

print(m.factorial(30))

print(pow(m.e, 15.5))
print(m.exp(15.5))

print((0.1 + 0.2) == 0.3)
print(m.isclose((0.1+0.2), 0.3))

a = m.pi/2
b = m.sin(m.pi/4) ** 2
c = m.e ** 3

result = a*c* m.sin(a*b) ** 2 + m.floor(c/(a+c)) * m.cos(a) ** b - b*c
result2 = a*c* m.sin(a*b) ** 2 + c//(a+c) * m.cos(a) ** b - b*c

print(result)
print(result2)

print('DECIMALS')


print(D(10))
print((D(0.2)))
print('Should be given as string')
print(D('0.2'))
print(D('0.20'))
print(D('2e-1'))
print(D('2.0e-1'))

print(D('1.30') * D('1.20')) #1.5600
print(D('1.3') * D('1.2')) # 1.56

d = D(-1)
f = 1.5
print(d+5) # 4
#print(d+f) TypeError unclear result type
print(float(d) + f) # 0.5
print(d+D(f)) # 0.5

print(D('0.1').log10())

print(D('2').sqrt())

