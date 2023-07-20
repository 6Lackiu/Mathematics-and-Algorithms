#include <iostream>
using namespace std;
class Vector {
public:
	// position: (x, y) --> (v.x, v.y)
	float x;
	float y;
	Vector(float _x, float _y) {
		x = _x;
		y = _y;
	}

	Vector operator - (Vector& v) {
		return Vector(x - v.x, y - v.y);
	}

	float cross(Vector& v) {
		return x * v.y - y * v.x;
	}
};

bool SameSide(Vector A, Vector B, Vector C, Vector P) {
	Vector AB = B - A;
	Vector AC = C - A;
	Vector AP = P - A;

	float v1 = AB.cross(AC);
	float v2 = AB.cross(AP);

	return v1 * v2 >= 0;
}

bool PointinTriangle1(Vector A, Vector B, Vector C, Vector P)
{
    bool b1 = SameSide(A, B, C, P);
    bool b2 = SameSide(B, C, A, P);
    bool b3 = SameSide(C, A, B, P);
    return b1 && b2 && b3;
}

int main() {
	Vector A(0, 0);
	Vector B(5, 0);
	Vector C(0, 6);
	Vector P(1, 3);

	if(PointinTriangle1(A, B, C, P)) {
		cout << "inside" << endl;
	}
	else {
		cout << "outside" << endl;
	};

}
