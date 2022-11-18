'''
    Dijkstra Algorithm
'''

import heapq
from implementation import *

class SquareGrid:
    def __init__(self, width, height):
        self.width = width
        self.height = height
        self.walls = []

    def in_bound(self, id):
        (x, y) = id
        return (0 <= x < self.width) and (0 <= y < self.height)

    def passable(self, id):
        return id not in self.walls

    def neighbors(self, id):
        (x, y) = id
        res = [(x + 1, y), (x - 1, y), (x, y + 1), (x, y - 1)]  # E W N S
        # choose a better path (more beautiful path)
        if (x + y) % 2 == 0:
            res.reverse() # S N W E      
        res = filter(self.in_bound, res)
        res = filter(self.passable, res)
        return res


class GridWithWeights(SquareGrid):
    def __init__(self, width, height):
        super().__init__(width, height)
        self.weights = {}
    
    def cost(self, from_node, to_node):
        return self.weights.get(to_node, 1)


class PriorityQueue:
    def __init__(self):
        self.elements = []
    
    def empty(self):
        return len(self.elements) == 0

    def put(self, item, priority):
        heapq.heappush(self.elements, (priority, item))

    def get(self):
        return heapq.heappop(self.elements)[1]


def dijkstra_search(graph, start, goal):
    frontier = PriorityQueue()
    frontier.put(start, 0)
    came_from = {}
    came_from[start] = None
    cost_so_far = {}
    cost_so_far[start] = 0

    while not frontier.empty():
        current = frontier.get()
        if current == goal:
            break

        for next in graph.neighbors(current):
            new_cost = cost_so_far[current] + graph.cost(current, next)
            if next not in came_from or new_cost < cost_so_far[next]:
                cost_so_far[next] = new_cost
                came_from[next] = current
                priority = new_cost
                frontier.put(next, priority)

    return came_from, cost_so_far


def reconstruct_path(came_from, start, goal):
    current = goal
    path = []
    while current != start:
        path.append(current)
        current = came_from[current]    # 将came_from中指向前一节点的数据指向current
    path.append(start)
    path.reverse()  # 将path从反向(goal-->start)变为正向（可选）
    return path



start, goal = (1, 4), (8, 3)
came_from, cost_so_far = dijkstra_search(diagram4, start, goal)
draw_grid(diagram4, point_to=came_from, start=start, goal=goal)
print()
draw_grid(diagram4, path=reconstruct_path(came_from, start=start, goal=goal))
print()
draw_grid(diagram4, number=cost_so_far, start=start)