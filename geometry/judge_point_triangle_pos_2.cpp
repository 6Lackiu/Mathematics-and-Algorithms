#include <iostream>
using namespace std;

class Vector2D {
public:
    Vector2D(double _x, double _y): x(_x), y(_y) {}

    Vector2D operator-(Vector2D v) {
        return Vector2D(x - v.x, y - v.y);
    }

    double cross(Vector2D v) {
        return (x * v.y - y * v.x);
    }

private:
    double x;
    double y;
};


bool isTriangle(double ax, double ay, double bx, double by, double cx, double cy, double px, double py) {
    Vector2D A(ax, ay);
    Vector2D B(bx, by);
    Vector2D C(cx, cy);
    Vector2D P(px, py);

    Vector2D AP = P - A;
    Vector2D BP = P - B;
    Vector2D CP = P - C;

    double v1 = AP.cross(BP);
    double v2 = BP.cross(CP);
    double v3 = CP.cross(AP);

    return v1 * v2 >= 0 && v1 * v3 >= 0;
}

int main() {
    bool res = isTriangle(0, 0, 5, 0, 0, 6, 2, 6);

    if(res) {
        cout << "inside" << endl;
    }
    else {
        cout << "ouside" << endl;
    }

    return 0;
}
