# A* Algorithm
## To run the code:
```
g++ astar.cpp
./a.exe < input.txt (or Get-Content input.txt | .\a.exe)
```
## Input format:
* vertices: id,cell (x_coordinate = cell // 10 and y_coordinate cell % 10)
    > 1,11
* edges: u,v,w
    > 1,2,7 
* source and destination nodes
    > S,1

    > D,4
## Implementation choices:
* Storing the input:
    > To hold edges of the graph: I use an array of vectors which hold arrays of size two (e.g. u -> v with weight w: graph[u_id][0] = v and graph[u_id][1] = w).

    > To hold coordinates of each node: I have two arrays called x and y which hold corresponding coordinates of a node.
* Implementation of A* algorithm:
    > The algorithm returns the path from the source node to the destination node if it is found in the form of a vector and receives the mode as a parameter.  

    > To prevent an infinite loop: I have an array called vis. vis[1] = 1; means node with id = 1 is visited.  

    > Finding the path: I have a loop which runs until the priority queue is empty. In this loop firstly I get the node with smallest f(n) and pop it from the queue, then I assign vis[id_currrent_node] = 1. If the current node equals to the destination node, I create the path to this node and return it. If it is not, I add all the neighbouring nodes to the queue with their f(n) cost, update its distance from the source node, and assign the current node as its parent.   

    > In each iteration I update the number of pushes, expanded nodes, and the maximum size of frontier. 
* Main function:
    > To get the input: I have two while loops; the first runs until there are two commas in a line and the second  runs until we get source and destination nodes. I receive every line and break it into parts according to the format. 

    > Number of nodes: I hold variable n to find the number nodes so that I can create parent array to find the desired path.

    > Modes: I have a loop in which I run the algorithm in 3 modes. Each time I reset the parent array, then I run astar(mode) unless source and destination nodes are equal.    

## Output format:
* MODE: <UCS | A* Euclidean | A* Manhattan>
* Optimal cost: <number | NO PATH>
* Path: <S -> ... -> D | (omit if NO PATH)>
* Expanded: [int]
* Pushes: [int]
* Max frontier: [int]
* Runtime (s): [float]
* Runtime (s * 10^(-6)): [float]

## Answers to the given questions:
* Optimality
    > Do all three modes return the same cost? -> Most of the time Yes, but sometimes they do not because I use an array to keep track of visited nodes which misleads the algorithm by preventing it going back. 

* Efficiency:
    > UCS >= Euclidean >= Manhattan in terms of runtime and the number of expanses. 
* Heuristic validity:
    > For the examples that I have choosen heuristics are admissible (the results of the algorithm for all the modes are same). 
