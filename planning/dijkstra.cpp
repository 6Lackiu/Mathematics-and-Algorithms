#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>

struct Node {
    int x, y;
    int distance;
    Node* parent;

    Node(int x_, int y_) : x(x_), y(y_), distance(0), parent(nullptr) {}
};

struct CompareNode {
    bool operator()(const Node* lhs, const Node* rhs) const {
        return lhs->distance > rhs->distance;
    }
};

std::vector<Node*> Dijkstra(const std::vector<std::vector<int>>& graph, Node* start, Node* end) {
    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    int rows = graph.size();
    int cols = graph[0].size();

    std::priority_queue<Node*, std::vector<Node*>, CompareNode> openList;
    openList.push(start);

    std::unordered_set<Node*> closeList;

    while (!openList.empty()) {
        Node* current = openList.top();
        openList.pop();

        if (current->x == end->x && current->y == end->y) {
            std::vector<Node*> path;
            while (current != nullptr) {
                path.push_back(current);
                current = current->parent;
            }
            return path;
        }

        closeList.insert(current);

        for (int i = 0; i < 4; ++i) {
            int nx = current->x + dx[i];
            int ny = current->y + dy[i];
            Node* neighbor = new Node(nx, ny);

            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && graph[nx][ny] != 1 && !closeList.count(neighbor)) {
                neighbor->distance = current->distance + 1;
                neighbor->parent = current;

                openList.push(neighbor);
            }
            else {
                delete neighbor;
            }
        }
    }

    return std::vector<Node*>();
}

int main() {
    std::vector<std::vector<int>> graph = {
        {0, 1, 1, 0, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 0, 1, 0}
    };

    Node* start = new Node(0, 0);
    Node* end = new Node(4, 4);

    std::vector<Node*> path = Dijkstra(graph, start, end);

    if (path.empty()) {
        std::cout << "无法找到路径" << std::endl;
    } else {
        std::cout << "找到路径!" << std::endl;
        for (int i = path.size() - 1; i >= 0; --i) {
            std::cout << "(" << path[i]->x << ", " << path[i]->y << ")" << std::endl;
        }
    }

    // 释放内存
    delete start;
    delete end;
    for (Node* node : path) {
        delete node;
    }

    return 0;
}
