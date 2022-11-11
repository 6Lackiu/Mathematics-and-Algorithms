import math
'''
Method 1:
    xt = x(t)
    yt = y(t)
    k = (ddy * dx - dy * ddx) / [(dx * dx + dy * dy)^(3/2)]
'''
def Compute_Curvature(dx, ddx, dy, ddy):
    a = ddy * dx - dy * ddx
    b = dx * dx + dy * dy
    c = math.sqrt(b)
    d = b * c
    res = a / d
    return res

def Compute_Curvature_Derivative(dx, ddx, dddx, dy, ddy, dddy):
    a = dx * dx + dy * dy
    b = dx * dddy - dddx + dy
    c = dx * ddx + dy * ddy
    d = dx * ddy - ddx * dy
    res = (a*b - 3*c*d) / (a*a*a)
    return res


'''
Method 2:
    xt = xt
    yt = y(xt)
    k = ddy / [(1 + dy * dy)^(3/2)]
'''
def Compute_Curvature(dy, ddy):
    a = 1 + dy * dy
    b = math.sqrt(a)
    res = ddy / (a * b)
    return res

def Compute_Curvature_Derivative(dy, ddy, dddy):
    a = dy * dy * dddy
    b = dy * ddy * ddy
    c = 1 + dy * dy
    res = (dddy + a - 3*b) / (c*c*c)
    return res