'''
    breadth_first_search Algorithm
'''

import collections
from implementation import *

class SimpleGraph:
    def __init__(self):
        self.edges = {}

    def neighbors(self, id):
        return self.edges[id]


example_graph = SimpleGraph()
example_graph.edges = {
    'A': ['B'],
    'B': ['A', 'C', 'D'],
    'C': ['A'],
    'D': ['E', 'A'],
    'E': ['B']
}


class Queue:
    def __init__(self):
        self.elements = collections.deque()

    def empty(self):
        return len(self.elements) == 0

    def put(self, x):
        self.elements.append(x)

    def get(self):
        return self.elements.popleft()


# print out what we find
def breadth_first_search_1(graph, start):
    frontier = Queue()
    frontier.put(start)
    reached = {}
    reached[start] = True
    
    while not frontier.empty():
        current = frontier.get()
        print("Visiting ", current)
        for next in graph.neighbors(current):
            if next not in reached:
                frontier.put(next)
                reached[next] = True

#breadth_first_search_1(example_graph, 'B')


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

# g = SquareGrid(30, 15)
# g.walls = DIAGRAM1_WALLS
# draw_grid(g)


# return came_from
def breadth_first_search_2(graph, start):
    frontier = Queue()
    frontier.put(start)
    came_from = {}
    came_from[start] = None

    while not frontier.empty():
        current = frontier.get()
        for next in graph.neighbors(current):
            if next not in came_from:
                came_from[next] = current
                frontier.put(next)
    
    return came_from

g = SquareGrid(30, 15)
g.walls = DIAGRAM1_WALLS
parents = breadth_first_search_2(g, (8, 7))
draw_grid(g, width = 2, point_to = parents, start = (8, 7))



# early exit
def breadth_first_search_3(graph, start, goal):
    frontier = Queue()
    frontier.put(start)
    came_from = {}
    came_from[start] = None

    while not frontier.empty():
        current = frontier.get()

        if current == goal:
            break

        for next in graph.neighbors(current):
            if next not in came_from:
                frontier.put(next)
                came_from[next] = current

    return came_from

g = SquareGrid(30, 15)
g.walls = DIAGRAM1_WALLS

parents = breadth_first_search_3(g, (8, 7), (17, 2))
print("\n\nEarly Exit")
draw_grid(g, width=2, point_to=parents, start=(8, 7), goal=(17, 2))