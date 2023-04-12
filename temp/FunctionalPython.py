#!/usr/bin/python3
#!/usr/bin/env python3
# -*- coding: utf-8 -*-



### 函数式编程思想示例 

# 简单数值计算求和
from ctypes import util


s = 0
for i in range(1, 10):
    if i % 3 == 0 or i % 5 == 0:
        s += i
        print(s, i)
print(s)

# 面向对象求和
m = list()
for i in range(1, 10):
    if i % 3 ==0 or i % 5 == 0:
        m.append(i)
        print(m)
print(sum(m))

# 混合范式求和
print(sum(n for n in range(1, 10) if n % 3 == 0 or n % 5 == 0))

# 纯递归求和（函数编程思想）
def until(n, filter_func, v):
    if v == n: 
        return []
    if filter_func(v): # 如果v通过了filter_func()函数的测试，返回一个序列，则该序列的第一个元素是v
        return [v] + until(n, filter_func, v+1)
    else: 
        return until(n, filter_func, v+1) # 如果v没有通过filter_func()函数的测试，将忽略该值

sum(until(10, lambda x: x % 3 == 0 or x % 5 == 0, 1))



## 比较大小
year_cheese = [(2000, 29.87), (2001, 30.12), (2002, 30.6), (2003, 30.66), (2004, 31.33), (2005, 32.62), (2006, 32.73), (2007, 33.5), (2008, 32.84), (2009, 33.02), (2010, 32.92)]

max(year_cheese)  # (默认) 按元组下标为0的元素比较大小，返回最大的元素所在的元组。
max(year_cheese, key=lambda yc: yc[0])  # 按元组下标为0的元素比较大小，返回最大的元素所在的元组。
max(year_cheese, key=lambda yc: yc[1])  # 按元组下标为1的元素比较大小，返回最大的元素所在的元组。


def numbers():
    for i in range(1024):
        print(f"= {i}")
        yield i

n = numbers()
n.__next__()



