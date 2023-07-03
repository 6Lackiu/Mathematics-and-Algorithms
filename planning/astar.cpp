#include <iostream>
#include <vector>
#include <queue>

struct Node {
    int x, y;           // 节点坐标
    int g, h;           // g: 从起点到当前节点的路径长度；h: 当前节点到终点的预估路径长度
    Node* parent;       // 当前节点的父节点

    Node(int x_, int y_) : x(x_), y(y_), g(0), h(0), parent(nullptr) {}

    int getF() const {
        return g + h;
    }
};

// 比较两个节点的 F 值（路径长度 + 预估路径长度）
struct CompareNode {
    bool operator()(const Node* lhs, const Node* rhs) const {
        return lhs->getF() > rhs->getF();
    }
};

// A* 算法实现
std::vector<Node*> AStarSearch(std::vector<std::vector<int>>& grid, Node* start, Node* end) {
    // 方向数组，用于表示上下左右四个方向的移动
    int dx[4] = { -1, 1, 0, 0 };
    int dy[4] = { 0, 0, -1, 1 };

    int rows = grid.size();
    int cols = grid[0].size();

    // 创建一个优先队列用于存放待扩展的节点
    std::priority_queue<Node*, std::vector<Node*>, CompareNode> openList;

    // 创建一个二维数组来记录已经访问过的节点
    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));

    // 将起点加入 openList
    openList.push(start);

    while (!openList.empty()) {
        // 从 openList 中取出 F 值最小的节点
        Node* current = openList.top();
        openList.pop();

        // 判断是否到达终点
        if (current->x == end->x && current->y == end->y) {
            // 构造路径
            std::vector<Node*> path;
            while (current != nullptr) {
                path.push_back(current);
                current = current->parent;
            }
            return path;
        }

        // 标记当前节点为已访问
        visited[current->x][current->y] = true;

        // 对当前节点的相邻节点进行扩展
        for (int i = 0; i < 4; i++) {
            int nx = current->x + dx[i];
            int ny = current->y + dy[i];

            // 判断相邻节点是否在网格范围内，并且没有被访问过，并且不是障碍物
            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && !visited[nx][ny] && grid[nx][ny] != 1) {
                // 创建相邻节点
                Node* neighbor = new Node(nx, ny);
                neighbor->g = current->g + 1;
                neighbor->h = abs(nx - end->x) + abs(ny - end->y);
                neighbor->parent = current;

                // 将相邻节点加入 openList
                openList.push(neighbor);
            }
        }
    }

    // 如果无法找到路径，返回空路径
    return std::vector<Node*>();
}

int main() {
    // 二维网格示例，0 表示可通过的空地，1 表示障碍物
    std::vector<std::vector<int>> grid = {
        {0, 0, 1, 0, 1},
        {1, 0, 1, 0, 1},
        {1, 0, 0, 0, 1},
        {0, 0, 1, 0, 1},
        {0, 0, 1, 0, 1},
        {0, 0, 1, 0, 0}
    };

    // 创建起点和终点节点
    Node* start = new Node(0, 0);
    Node* end = new Node(5, 4);

    // 运行 A* 算法
    std::vector<Node*> path = AStarSearch(grid, start, end);

    // 输出路径
    if (path.empty()) {
        std::cout << "无法找到路径！" << std::endl;
    } else {
        std::cout << "找到路径！" << std::endl;
        for (int i = path.size() - 1; i >= 0; i--) {
            std::cout << "(" << path[i]->x << ", " << path[i]->y << ")" << std::endl;
        }
    }

    // 释放节点内存
    delete start;
    delete end;
    for (Node* node : path) {
        delete node;
    }

    return 0;
}
