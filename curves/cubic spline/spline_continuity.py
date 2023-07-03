'''
    spline continunity
'''

import numpy as np
import matplotlib.pyplot as plt
from scipy.interpolate import interp1d

class Spline2D:
    def __init__(self, x, y, kind="cubic"):
        self.s = self._calc_s(x, y)
        self.fx = interp1d(self.s, x, kind)    # interpolate.interp1d返回的是一个函数
        self.fy = interp1d(self.s, y, kind)
    
    def _calc_s(self, x, y):
        ds = np.hypot(np.diff(x), np.diff(y))  # 计算两个矩阵之间的欧氏距离
        s = [0.0]
        s.extend(np.cumsum(ds))
        return s    # 从第一个点到后面各个点的距离

    def calc_pos(self, s):
        x = self.fx(s)  # self.sx self.sy都是函数
        y = self.fy(s)
        return x, y


def main():
    x = [-2.5, 0.0, 2.5, 5.0, 7.5, 3.0, 1.0]
    y = [0.7, -6, -5, -3.5, 0.0, 5.0, -2.0]
    ds = 0.1  # distance of each interpolated points

    plt.plot(x, y, "xb", label="Data points")

    for (kind, label) in [("linear", "C0 (Linear spline)"),
                          ("quadratic", "C0 & C1 (Quadratic spline)"),
                          ("cubic", "C0 & C1 & C2 (Cubic spline)")]:
        sp = Spline2D(x, y, kind=kind)
        #print(sp.s)
        s = np.arange(0, sp.s[-1], ds)
        rx, ry = [], []
        for i_s in s:
            ix, iy = sp.calc_pos(i_s)
            rx.append(ix)
            ry.append(iy)
        plt.plot(rx, ry, "-", label=label)

    plt.grid(True)
    plt.axis("equal")
    plt.xlabel("x")
    plt.ylabel("y")
    plt.legend(loc=1)
    plt.show()

    
if __name__ == "__main__":
    main()