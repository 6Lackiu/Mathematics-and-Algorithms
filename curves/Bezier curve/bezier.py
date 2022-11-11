'''
    Beizer curve
'''

import matplotlib.pyplot as plt
import numpy as np

NUM = 100

def factorial(n):
    if n == 0:
        return 1
    res = 1
    for i in range(1, n+1):
        res *= i
    return res

def combinatorial_num(n, i):
    return factorial(n) / (factorial(i) * factorial(n-i))

def bernstein_polynomial(n, i, t):
    return combinatorial_num(n, i) * pow(t, i) * pow((1.0-t), (n-i))

def bezier_curve(point_list):
    n = len(point_list) - 1     # order
    t = np.linspace(0, 1, NUM)
    x = 0.0
    y = 0.0
    for i in range(n + 1):
        x += bernstein_polynomial(n, i, t) * point_list[i][0]
        y += bernstein_polynomial(n, i, t) * point_list[i][1]
    
    return [x, y]

p_start1 = [0, 0]
p_0 = [2, 10]
p_1 = [6, -7]
p_end1 = [10, 10]
p_list = [p_start1, p_0, p_1, p_end1]

x, y = bezier_curve(p_list)
res = []
for i in range(NUM):
    res.append([round(x[i], 2), round(y[i], 2)])
print(res)

plt.subplot(121)
plt.plot(p_start1[0], p_start1[1], 'or')
plt.plot(p_0[0], p_0[1], 'ob')
plt.plot(p_1[0], p_1[1], 'ob')
plt.plot(p_end1[0], p_end1[1], 'or')

plt.plot(x, y, 'og')
plt.axis('equal')



# *** Common situations ***
# second order Bezier curve ---> three points
def second_order_Bezier(p_start, p_control, p_end):

    t = np.linspace(0, 1, NUM)

    B_x = ((1 - t) ** 2) * p_start[0] + 2 * t * (1 - t) * p_control[0] + (t ** 2) * p_end[0]
    B_y = ((1 - t) ** 2) * p_start[1] + 2 * t * (1 - t) * p_control[1] + (t ** 2) * p_end[1]
    return [B_x, B_y]

p_start2 = [0, 0]
p_3 = [13, 6]
p_end2 = [10, 10]

x_p, y_p = second_order_Bezier(p_start2, p_3, p_end2)
res2 = []
for i in range(NUM):
    res2.append([round(x_p[i],2), round(y_p[i],2)])
print(res2)

plt.subplot(122)
plt.plot(p_start2[0],p_start2[1],'or')
plt.plot(p_3[0],p_3[1],'ob')
plt.plot(p_end2[0],p_end2[1],'or')

plt.plot(x_p, y_p, 'og')
plt.show()



# third order Bezier curve ---> four points
# ...