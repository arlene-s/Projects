from queue import PriorityQueue
from pprint import pprint

# Graph of cities with connections to each city. Similar to our class exercises, you can draw it on a piece of paper 
# with step-by-step node inspection for better understanding 
graph = {
    'San Bernardino': ['Riverside', 'Rancho Cucamonga'],
    'Riverside': ['San Bernardino', 'Ontario', 'Pomona'],
    'Rancho Cucamonga': ['San Bernardino', 'Azusa', 'Los Angeles'],
    'Ontario': ['Riverside', 'Whittier', 'Los Angeles'],
    'Pomona': ['Riverside', 'Whittier', 'Azusa', 'Los Angeles'],
    'Whittier': ['Ontario','Pomona', 'Los Angeles'],
    'Azusa': ['Rancho Cucamonga', 'Pomona', 'Arcadia'],
    'Arcadia': ['Azusa', 'Los Angeles'],
    'Los Angeles': ['Rancho Cucamonga', 'Ontario', 'Pomona', 'Whittier', 'Arcadia']
}

# Weights are treated as g(n) function as we studied in our class lecture which represents the backward cost. 
# In the data structure below, the key represents the cost from a source to target node. For example, the first
# entry shows that there is a cost of 2 for going from San Bernardino to Riverside.
weights = {
    ('San Bernardino', 'Riverside'): 2,
    ('San Bernardino', 'Rancho Cucamonga'): 1,
    ('Riverside', 'Ontario'): 1,
    ('Riverside', 'Pomona'): 3,
    ('Rancho Cucamonga', 'Los Angeles'): 5,
    ('Pomona', 'Los Angeles'): 2,
    ('Ontario', 'Whittier'): 2,
    ('Ontario', 'Los Angeles'): 3,
    ('Rancho Cucamonga', 'Azusa'): 3,
    ('Pomona', 'Azusa'): 2,
    ('Pomona', 'Whittier'): 2,
    ('Azusa', 'Arcadia'): 1,
    ('Whittier', 'Los Angeles'): 2,
    ('Arcadia', 'Los Angeles'): 2
}

# heurist is the h(n) function as we studied in our class lecture which represents the forward cost. 
# In the data structure below, each entry represents the h(n) value. For example, the second entry
# shows that h(Riverside) is 2 (i.e., h value as forward cost for eaching at Riverside assuming that
# your current/start city is San Bernardino)

heuristic = {
    'San Bernardino': 4,
    'Riverside': 2,
    'Rancho Cucamonga': 1,
    'Ontario': 1,
    'Pomona': 3,
    'Whittier': 4,
    'Azusa': 3,
    'Arcadia': 2,
    'Los Angeles': 0
}

# Data structure to implement search algorithms. Each function below currently has one line of code
# returning empty solution with empty expanded cities. You can remove the current return statement and 
# implement your code to complete the functions.

class SearchAlgorithms:
    def breadthFirstSearch(self, start, goal, graph):
        """
        Search the shallowest nodes in the search tree first.

        Your search algorithm needs to return (i) a list of cities the algorithm will propose to go to to reach the
        goal, and (ii) set of expanded cities (visited nodes). Make sure to implement a graph search algorithm.

        """
        "*** YOUR CODE HERE ***"
        visited = set()     # create a set that holds nodes visited
        # list in tuple contains path 
        queue = [(start, [start])] # create a list in a tuple in a queue(list), append start node 

        while queue:    # while queue is not empty
            node, path = queue.pop(0)   # dequeue node from queue, set as current node

            if node == goal:            # check if visited node is the goal state
                return {f'Returned solution: {path}, Expanded cities: {visited}'}
            
            if node not in visited:     # append visited node to visited set
                visited.add(node) 
                for child in graph[node]:
                    queue.append((child, path + [child]))

        return "Goal not found"

    def depthFirstSearch(self, start, goal, graph):
        """
        Search the deepest nodes in the search tree first.

        Your search algorithm needs to return (i) a list of cities the algorithm will propose to go to to reach the
        goal, and (ii) set of expanded cities (visited nodes). Make sure to implement a graph search algorithm.

        Please be very careful when you expand the neighbor nodes in your code when using stack. In case of using 
        normal list or a data structure other than the Stack, you might need to reverse the order of the neighbor nodes
        before you push them in the stack to get correct results 

        """
        "*** YOUR CODE HERE ***"

        visited = set()
        stack = [(start,[start])]

        while stack:
            node, path = stack.pop()

            if node == goal:
                return {f'Returned solution: {path}, Expanded cities: {visited}'}
            
            if node not in visited:    
                visited.add(node) 
                for child in reversed(graph[node]):     # reverse list 
                    stack.append((child, path + [child]))
                    
        return "Goal not found"
            

    def uniformCostSearch(self, start, goal, graph, weights):
        """Search the node of least total cost first.
        Important things to remember
        1 - Use PriorityQueue with .put() and .get() functions
        2 - In addition to putting the start or current node in the queue, also put the cost (g(n)) using weights data structure
        3 - When you're expanding the neighbor of the current you're standing at, get its g(neighbor) by weights[(node, neighbor)] 
        4 - Calling weights[(node, neighbor)] may throw KeyError exception which is due to the fact that the weights data structure
            only has one directional weights. In the class, we mentioned that there is a path from Arad to Sibiu and back. If the 
            exception occurs, you will need to get the weight of the nodes in reverse direction (weights[(neighbor, node)])
        """

        "*** YOUR CODE HERE ***"

        visited = set()
        pqueue = PriorityQueue()
        pqueue.put((0, start, [start]))     # weight, node, path 

        while not pqueue.empty():
            cost, node, path = pqueue.get()     # new sorted queue, grabs first in queue

            if node == goal:
                return {f'Returned solution: {path}, Expanded cities: {visited}'}
            
            if node not in visited:    
                visited.add(node) 
                for neighbor in graph[node]:                 
                    if (node, neighbor) in weights:     # took forever here
                        # get backwards cost
                        pqueue.put((cost + weights[(node, neighbor)], neighbor, path + [neighbor]))

        return "Goal not found"
        

    def AStar(self, start, goal, graph, weights, heuristic):
        """Search the node that has the lowest combined cost and heuristic first.
        Important things to remember
        1 - Use PriorityQueue with .put() and .get() functions
        2 - In addition to putting the start or current node in the queue, and the g(n), also put the combined cost (i.e., g(n) + h(n)) 
            using weights and heuristic data structure
        3 - When you're expanding the neighbor of the current you're standing at, get its g(neighbor) by weights[(node, neighbor)] 
        4 - Calling weights[(node, neighbor)] may throw KeyError exception which is due to the fact that the weights data structure
            only has one directional weights. In the class, we mentioned that there is a path from Arad to Sibiu and back. If the 
            exception occurs, you will need to get the weight of the nodes in reverse direction (weights[(neighbor, node)])
        """
        "*** YOUR CODE HERE ***"

        visited = set()
        pqueue = PriorityQueue()
        pqueue.put((0, 0, start, [start])) # combined_cost(f(n)), backwards_cost(g(n)), node, path

        while not pqueue.empty():
            fOfn, backwards_cost, node, path = pqueue.get()

            if node == goal:
                return {f'Returned solution: {path}, Expanded cities: {visited}'}
            
            if node not in visited:    
                visited.add(node) 
                for neighbor in graph[node]:                 
                    if (node, neighbor) in weights:     # copied UCS, added heuristic
                        gOfn = backwards_cost + weights[(node, neighbor)]
                        fOfn = gOfn + heuristic[neighbor]
                        pqueue.put((fOfn, gOfn, neighbor, path + [neighbor]))

        return "Goal not found"


# Call to create the object of the above class
search = SearchAlgorithms()

# Call to each algorithm to print the results
print("Breadth First Search Result") # ['San Bernardino', 'Rancho Cucamonga', 'Los Angeles']
pprint(search.breadthFirstSearch('San Bernardino', 'Los Angeles', graph))

print("Depth First Search Result") # ['San Bernardino', 'Riverside', 'Ontario', 'Whittier', 'Pomona', 'Azusa', 'Rancho Cucamonga', 'Los Angeles']
pprint(search.depthFirstSearch('San Bernardino', 'Los Angeles', graph))

print("Uniform Cost Search Result") # ['San Bernardino', 'Rancho Cucamonga', 'Los Angeles']
pprint(search.uniformCostSearch('San Bernardino', 'Los Angeles', graph, weights))

print("A* Search Result") # ['San Bernardino', 'Rancho Cucamonga', 'Los Angeles']
pprint(search.AStar('San Bernardino', 'Los Angeles', graph, weights, heuristic))
