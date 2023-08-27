#include<iostream>
#include<vector>

using namespace std;

struct Param {
    double k;
    double b;
};

// cost = sum((yi - k * xi - b)^2)
// \partial{cost}/\partial{b} = 0
// \partial{cost}/\partial{k} = 0
// \partial{ cost } / \partial{ b } = \sum{ 2 * (yi - k * xi - b) } = 0
// ==> b = mean(y) - k * mean(x)

// \partial{ cost } / \partial{ k } = \sum{ 2 * (yi - k * xi - b) * (-xi) } = 0



Param get_line(vector<vector<double>> points) {
    double y_sum = 0, x_sum = 0;
    int num_points = points.size();
    for (int i = 0; i < num_points; ++i) {
        x_sum += points[i][0];
        y_sum += points[i][1];
    }
    double y_mean = y_sum / num_points, x_mean = x_sum / num_points;
    double sum1 = 0, sum2 = 0;
    for (int i = 0; i < num_points; ++i) {
        sum1 += (points[i][0] - x_mean) * points[i][0];
        sum2 += (points[i][1] - y_mean) * points[i][0];
    }
    Param res;
    res.k = sum2 / (sum1 + 1e-6);
    res.b = y_mean - res.k * x_mean;
    return res;
}

int main() {

    // vector<vector<int>> points = { {0,1},{1,3},{2,5},{3,7} };
    vector<vector<double>> points = { {1, 2}, {2, 3.1}, {3, 4.1}, {4, 5.2}, {5, 6} };

    Param res = get_line(points);
    cout << "y = " << res.k << "x + " << res.b << endl;

    return 0;
}