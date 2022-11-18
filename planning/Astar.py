'''
    A* Algorithm
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

def heuristic(a, b):
    (x1, y1) = a
    (x2, y2) = b
    return abs(x1 - x2) + abs(y1 - y2)

def a_star_search(graph, start, goal):
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
                came_from[next] = current
                cost_so_far[next] = new_cost
                priority = new_cost + heuristic(goal, next)
                frontier.put(next, priority)
    
    return came_from, cost_so_far


start, goal = (1, 4), (8, 3)
came_from, cost_so_far = a_star_search(diagram4, start, goal)
draw_grid(diagram4, point_to=came_from, start=start, goal=goal)
print()
draw_grid(diagram4, path=reconstruct_path(came_from, start=start, goal=goal))
print()
draw_grid(diagram4, number=cost_so_far, start=start, goal=goal)