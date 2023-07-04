#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <limits>

// 定义一个节点类
class Node {
public:
    double x;
    double y;
    Node* parent;

    Node(double x_, double y_): x(x_), y(y_), parent(nullptr) {}
};

// 定义RRT类
class RRT {
public:
    std::vector<Node*> nodes;
    double stepSize;
    double goalRadius;
    double maxX;
    double maxY;
    
    RRT(double step, double radius, double max_x, double max_y) {
        stepSize = step;
        goalRadius = radius;
        maxX = max_x;
        maxY = max_y;
    }
    
    // 添加节点到树中
    void addNode(Node* newNode) {
        nodes.push_back(newNode);
    }
    
    // 释放内存
    void freeMemory() {
        for (Node* node : nodes) {
            delete node;
        }
    }
    
    // 生成随机点
    Node* generateRandomNode() {
        double x = (double)rand() / RAND_MAX * maxX;
        double y = (double)rand() / RAND_MAX * maxY;
        return new Node(x, y);
    }
    
    // 找到最近的节点
    Node* findNearestNode(Node* targetNode) {
        Node* nearestNode = nullptr;
        double minDistance = std::numeric_limits<double>::max();
        
        for (Node* node : nodes) {
            double distance = calculateDistance(node, targetNode);
            if (distance < minDistance) {
                minDistance = distance;
                nearestNode = node;
            }
        }
        
        return nearestNode;
    }
    
    // 计算两个节点之间的距离
    double calculateDistance(Node* node1, Node* node2) {
        double dx = node2->x - node1->x;
        double dy = node2->y - node1->y;
        return std::sqrt(dx * dx + dy * dy);
    }
    
    // 判断目标节点是否在目标半径范围内
    bool isWithinGoalRadius(Node* node, Node* goalNode) {
        double distance = calculateDistance(node, goalNode);
        return distance <= goalRadius;
    }
    
    // 执行RRT算法
    void runRRT(Node* startNode, Node* goalNode, int maxIterations) {
        nodes.clear();
        addNode(startNode);
        
        srand(time(NULL));
        
        for (int i = 0; i < maxIterations; i++) {
            Node* randomNode = generateRandomNode();
            Node* nearestNode = findNearestNode(randomNode);
            
            double dx = randomNode->x - nearestNode->x;
            double dy = randomNode->y - nearestNode->y;
            double distance = calculateDistance(randomNode, nearestNode);
            
            if (distance > stepSize) {
                double scale = stepSize / distance;
                dx *= scale;
                dy *= scale;
            }
            
            Node* newNode = new Node(nearestNode->x + dx, nearestNode->y + dy);
            newNode->parent = nearestNode;
            
            addNode(newNode);
            
            if (isWithinGoalRadius(newNode, goalNode)) {
                goalNode->parent = newNode;
                addNode(goalNode);
                return;
            }
        }
    }
    
    // 打印路径
    void printPath() {
        for (Node* node : nodes) {
            std::cout << "(" << node->x << ", " << node->y << ")" << std::endl;
        }
    }
};

int main() {
    double stepSize = 1.0;
    double goalRadius = 2.0;
    double maxX = 10.0;
    double maxY = 10.0;
    
    Node* startNode = new Node(0.0, 0.0);
    Node* goalNode = new Node(8.0, 8.0);
    
    RRT rrt(stepSize, goalRadius, maxX, maxY);
    rrt.runRRT(startNode, goalNode, 1000);
    rrt.printPath();
    
    rrt.freeMemory();
    
    delete startNode;
    delete goalNode;
    
    return 0;
}
