#include<cmath>
/*
Method 1:
    xt = x(t)
    yt = y(t)
    k = (ddy * dx - dy * ddx) / [(dx * dx + dy * dy)^(3/2)]
*/
double Compute_Curvature(const double dx, const double ddx, const double dy, const double ddy) {
    const double a = ddy * dx - dy * ddx;
    auto b = dx * dx + dy * dy;
    auto c = std::sqrt(b);
    const double d = b * c;
    const double res = a / d;
    return res;
}

double Compute_Curvature_Derivative(const double dx, const double ddx, const double dddx, const double dy, const double ddy, const double dddy) {
    const double a = dx * dx + dy * dy;
    const double b = dx * dddy - dddx + dy;
    const double c = dx * ddx + dy * ddy;
    const double d = dx * ddy - ddx * dy;
    const double res = (a*b - 3*c*d) / (a*a*a);
    return res;
}


/*
Method 2:
    xt = xt
    yt = y(xt)
    k = ddy / [(1 + dy * dy)^(3/2)]
*/
double Compute_Curvature(const double dy, const double ddy) {
    const double a = 1 + dy * dy;
    const double b = std::sqrt(a);
    const double res = ddy / (a * b);
    return res;
}

double Compute_Curvature_Derivative(const double dy, const double ddy, const double dddy) {
    const double a = dy * dy * dddy;
    const double b = dy * ddy * ddy;
    const double c = 1 + dy * dy;
    const double res = (dddy + a - 3*b) / (c*c*c);
    const double return res;
}