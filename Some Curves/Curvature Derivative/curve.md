# 曲率、曲率（对弧长）的导数以及曲率导数（对弧长）的导数的计算

本文参考[这篇windSeS博主关于曲率的文章]([(37条消息) 曲率、曲率（对弧长）的导数以及曲率导数（对弧长）的导数的计算_windSeS的博客-CSDN博客_曲率公式推导过程](https://blog.csdn.net/u013468614/article/details/108416552))

## 1.曲线的表示形式

二维平面上的曲线有两种参数化形式，分别为：

- 参数方程1
  $$
  \begin{cases}
   x_t = x(t)\\
   y_t = y(t)
  \end{cases}
  $$

- 参数方程2
  $$
  \begin{cases}
   x_t = x_t\\
   y_t = y(x_t)
  \end{cases}
  $$
  以上两种参数方程都可以唯一确定一条二维平面内的曲线。因此，下文计算的曲率、曲率的导数以及曲率导数的导数的公式都有两种等价的形式。
  
  

## 2.曲率计算公式及推导

### 2.1 参数方程1曲率公式推导

假定 $(x_t, y_t)$ 处的切点为 $\alpha$，则此点处曲线的斜率为 $tan(\alpha)$。$(x_t, y_t)$ 的变量都为 $t$，假定 $t$ 有一个小的增量 $\Delta_t$ ，则 $x_t$ 与 $y_t$ 相应的都有一个小的增量 $\Delta_x$ 与 $\Delta_y$ 。如下图所示，当 $\Delta_t$ 很小时，$\frac{\Delta_y}{\Delta_x} \approx tan(\alpha)$ 。

<img src="D:\GitHub\Some-Mathematics\pics\Some Curves\Curvature Derivative\curve.jpg" width="550" />

a与b之间的距离dx即x的微分。dx曲线增量为dy，即y的微分。因为dx是无穷小量，所以ab连线即为切线，斜率是 $f^{\prime}(x)=\frac{dy}{dx}$。

${\Delta_x}$ 与 ${\Delta_y}$ 为 $x_t$ 与 $y_t$ 在 t 处的微分，一般分别表示为 dx 和 dy。$x\prime$ 与 $y\prime$ 表示函数 $x(t)$，$y(t)$ 对 t 的导数。

> 导数是函数图像在某一点处的斜率，是一个**比值**。微分是函数图像在某一点处的切线在横坐标取得 ${\Delta_x}$ 以后，纵坐标取得的增量，是一个**增量**。

当 ${\Delta_t}\rightarrow0$ 时，$\frac{\Delta_y}{\Delta_x} = \frac{dy}{dx} = tan(\alpha)$  ⇒ $\frac{\frac{dy}{dt}}{{\frac{dx}{dt}}}=tan(\alpha)$  ⇒ $\frac{y^{\prime}}{{x^{\prime}}}=tan(\alpha)$ 得：
$$
\frac{y^{\prime}}{{x^{\prime}}}=tan(\alpha)
$$
对上式两边分别求导得：
$$
\frac{y^{\prime\prime} x^{\prime}-x^{\prime\prime}y^{\prime}}{x^{\prime2}}dt
=(1+tan^2(\alpha)d\alpha)
=(\frac{x^{\prime2}+y^{\prime2}}{x^{\prime2}})d\alpha
$$
化简得：
$$
\frac{y^{\prime\prime} x^{\prime}-x^{\prime\prime}y^{\prime}}{x^{\prime2}+y^{\prime2}}dt=d\alpha
$$
又因为 $ds=\sqrt{x^{\prime2}+y^{\prime2}}dt$ ,代入上式得到曲线参数方程1对应的曲率计算公式（曲率为角度对弧度的导数）：
$$
k = \frac{d\alpha}{ds} = \frac{y^{\prime\prime} x^{\prime}-x^{\prime\prime}y^{\prime}}{(x^{\prime2}+y^{\prime2})^\frac{3}{2}}
\tag{1}
$$

### 2.2 参数方程2曲率公式推导

此时曲线的自变量为 x，曲线在点 $(x_t,y_t)$ 处的导数为 $y^\prime=f^\prime(x)=tan(\alpha)$ 。等式两边分别求导得：
$$
y^{\prime\prime}dx
=(1+tan^2(\alpha))d\alpha
=(1+y^{\prime2})d\alpha
$$
化简得：
$$
\frac{y^{\prime\prime}}{1+y^{\prime2}}dx = d\alpha
$$
又因为 $ds = \sqrt{1+y^{\prime2}}dx$，代入上式得到曲线参数方程2对应的曲率计算公式（曲率为角度对弧度得导数）：
$$
k = \frac{y^{\prime\prime}}{(1+y^{\prime2})^{\frac{3}{2}}}
\tag{2}
$$

### 2.3 小结

两种参数方程得到的曲率公式推导过程和最终公式形式相似。在表示曲线时，不同情况下用到的参数方程不一样。为了简便，可以统一两种参数方程，令 $x(t)=t$ 时，参数方程1就变成了参数方程2。此时 $x^\prime=1$, $x^{\prime\prime}=0$，代入式(1)就得到了式(2)。下文中只求针对参数方程1的曲率导数 $k^\prime$ 以及曲率导数的导数 $k^{\prime\prime}$。



## 3.曲率的导数（或称为变化率）公式及推导

对曲率公式 $k = \frac{d\alpha}{ds} = \frac{y^{\prime\prime} x^{\prime}-x^{\prime\prime}y^{\prime}}{(x^{\prime2}+y^{\prime2})^\frac{3}{2}}$ 两边分别求导，得：
$$
k^\prime = \frac{dk}{ds}
= \frac{\frac{(y^{\prime\prime}x^\prime-x^{\prime\prime}y^\prime)^\prime (x^{\prime2}+y^{\prime2})^{\frac{3}{2}}
-((x^{\prime2}+y^{\prime2})^{\frac{3}{2}})^\prime(y^{\prime\prime}x^\prime-x^{\prime\prime}y^\prime)}{(x^{\prime2}+y^{\prime2})^3}dt}{ds}
$$
将 $ds=\sqrt{x^{\prime2}+y^{\prime2}}dt$ 代入上式可得 $k^\prime$ 计算公式如下（对应参数方程1）：
$$
k^\prime=\frac{(y^{\prime\prime\prime}x^\prime-x^{\prime\prime\prime}y^\prime)(x^{\prime2}+y^{\prime2})
-3(x^\prime x^{\prime\prime}+y^\prime y^{\prime\prime})(y^{\prime\prime}x^\prime-x^{\prime\prime}y^\prime)}
{(x^{\prime2}+y^{\prime2})^3}
\tag{3}
$$
令 $x^\prime = 1$ ，$x^{\prime\prime} = 0$ ，$x^{\prime\prime\prime} = 0$ 代入式(3)可得参数方程2的 $k^\prime$ 计算公式如下：
$$
k^\prime=\frac{y^{\prime\prime\prime}+y^{\prime\prime\prime}y^{\prime2}-3y^\prime y^{\prime\prime2}}{(1+y^{\prime2})^3}
\tag{4}
$$


## 4.曲率导数的导数公式及推导

$$
k^{\prime\prime} = \frac{dk^\prime}{ds}
=\frac{d\frac{(y^{\prime\prime\prime}x^\prime-x^{\prime\prime\prime}y^\prime)(x^{\prime2}+y^{\prime2})
-3(x^\prime x^{\prime\prime}+y^\prime y^{\prime\prime})(y^{\prime\prime}x^\prime-x^{\prime\prime}y^\prime)}
{(x^{\prime2}+y^{\prime2})^3}}{ds}
=...
$$
