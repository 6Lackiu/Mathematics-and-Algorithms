#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class Vector2D{
public:
	Vector2D(double _x, double _y) {
		x = _x;
		y = _y;
	}
	Vector2D operator -(Vector2D& v) {
		return Vector2D(x - v.x, y - v.y);
	}
	double dot(Vector2D& v) {
		return x * v.x + y * v.y;
	}
	double norm(Vector2D& v) {
		return sqrt(v.x * v.x + v.y * v.y);

	}
	double project(Vector2D& v) {
		// u * v = |u| |v| cos 
		// |u| cos = u * v / |v|
		// u向v投影
		Vector2D u = Vector2D(x, y);
		return u.dot(v) / norm(v);
	}

	double x, y;
};

class Rectangle{
public:
	Rectangle(double _x, double _y, double _length, double _width, double _rotation) {
		// x y是最下端的顶点坐标 按这个点旋转
		x = _x;
		y = _y;
		length = _length;
		width = _width;
		rotation = _rotation;
	}
	Vector2D getWidthVec() {
		return Vector2D(cos(rotation), sin(rotation));
	}
	Vector2D getLengthVec() {
		return Vector2D(-sin(rotation), cos(rotation));
	}
	Vector2D getCenterPoint() {
		double centerX = x + (length * cos(rotation) - width * sin(rotation)) / 2.0;
		double centerY = y + (length * sin(rotation) + width * cos(rotation)) / 2.0;
		return Vector2D(centerX, centerY);
	}
	Vector2D getHalfDiagonalVec() {
		return Vector2D((length * cos(rotation) - width * sin(rotation)) / 2.0,
						(length * sin(rotation) + width * cos(rotation)) / 2.0);
	}
	
	double x, y, length, width, rotation;
};


bool isOverlap(Rectangle& r1, Rectangle& r2) {
	// 1. 以任意一条矩形的边向量作为投影基准
	vector<Vector2D> v;
	v.push_back(r1.getWidthVec());
	v.push_back(r1.getLengthVec());
	v.push_back(r2.getWidthVec());
	v.push_back(r2.getLengthVec());

	// 2. 获得两个矩形的对角线半个向量
	Vector2D d1 = r1.getHalfDiagonalVec();
	Vector2D d2 = r2.getHalfDiagonalVec();

	// 3. 获得两个矩形的中心点向量
	Vector2D c1 = r1.getCenterPoint();
	Vector2D c2 = r2.getCenterPoint();
	cout << c1.x << ", " << c1.y << "  <--->  " << c2.x << ", " << c2.y << endl;
	Vector2D c = c2 - c1;

	for (int i = 0; i < 4; i++) {
 		// 4. 每次选择一个基准向量，将两个矩形的对角线向量和中心线向量投影
		double p1 = d1.project(v[i]);
		double p2 = d2.project(v[i]);
		double p = c.project(v[i]);

		// 5. 投影和的距离关系
		// cout << p1 << " " << p2 << " " << p << endl;
		// 投影某一条边时，两矩形中心点相连向量都大于p1+p2，说明两个矩形相距很远，直接return false
		if (abs(p1 + p2) < abs(p)) return false;	// 不重叠
	}
	return true;	// 重叠
}


int main()
{
	// 初始化两个矩形的类
	Rectangle r1 = Rectangle(1, 0, sqrt(2), sqrt(2), 3.14 / 4);
	Rectangle r2 = Rectangle(3, 0, 2*sqrt(2), 2*sqrt(2), 3.14 / 4);


	bool res = isOverlap(r1, r2);
	if (res) cout << "重叠" << endl;
	else cout << "不重叠" << endl;

}

