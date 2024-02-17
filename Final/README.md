# Purpose
This project is intended to show some of the functions, features, and algorithms associated with graphs in c++. All references and resources will be listed in the Resources tab at the bottom of this readme.

## Implementation
There are five files in this project, three header files, and two c++ files. The three header files serve to initialize key elements used throughout the code, edge.h initializes the edge struct that stores all the edges in the Graph, the vertex.h initializes the vertex struct that stores the vertices in the Graph, and the graph.h initializes the Graph class that contains all the functions used throughout the code (except for main). The two c++ files are graph.cpp and main.cpp. The driver file is main.cpp so I won't go into much detail on that, but graph.cpp is what stores all the code for the functions initialized in graph.h. 

There are nine functions overall (plus one init function) and four private variables. The nine functions addEdge, addVertex, print, edgeExists, vertexExists, shortestPathSelected, minSpanTree, getIDByString, and printPath. getIDByString and printPath are utility functions private to the class, getIDByString converts the string name of a vertex into its respective ID for use in the shortestpath algorithm and the minSpanTree (although the minSpanTree doesn't need it necessarily), and the printPath function is used to print the route taken using the shortestPath route. 

## Tests
## addVertex
add duplicate vertices: "Home" -- "That Vertex already exists" Program continued and ignored duplicate entry

add non duplicate vertex: "Pool" -- "Vertex Pool successfully created with the id of 8"

## addEdge
add duplicate edge: Home and Store, dist 30 -- That edge already exists. Program ignored duplicate and proceeded with original edge

add non duplicate edge: Pool and Restaurant, dist 15 -- Edge successfully created between Pool and Restaurant

add edge with non existent vertices House and Grocery Store, dist 30 -- The source vertex House and destination vertex Grocery Store do not exist. Program continued as expected

## edgeExists
check for existing edge: Home and Store, dist 20 -- true

check for non existing edge: Home and Pool, dist 20  -- false

## vertexExists
check for existing vertex: Home -- true

check for non existing vertex: House -- false

## shortestPath
check between two vertices that exist: Home and Park -- 
                                      
    The shortest distance from Home to Park is 100
    Home -> Store -> Gym -> Park

check between two vertices that don't exist (or just one that doesn't result should stay the same) Home and Church -- 
                                                                  
    Invalid source vertex selected
    Could not perform Shortest Path algorithm, location was invalid 

start from vertex that is further away than "home" (ie go backwards): Cafe and Home --

    The shortest distance from Cafe to Home is 72
    Cafe ->
The print path function didn't work properly here because its only designed to print roots, and going backwards doesn't work for                                       that. In the future I could solve this by checking the source ID and comparing it to the destination ID, if destination is smaller
go backwards, if source is smaller go forwards. Otherwise specify that the source needs to be closer to Home than the destination.

## minSpanTree
run basic minSpanTree: See main.cpp edges --

    Home -> Store
    Home -> School
    Store -> Gym
    Gym -> Work
    Gym -> Park
    Pool -> Cafe
    Pool -> Restaurant
    Work -> Pool

run minSpanTree when graph is disconnected: Cafe and Pool isolated from Graph --

    Home -> Store
    Home -> School
    Store -> Gym
    Gym -> Work
    Gym -> Park
    terminate called after throwing an instance of 'std::out_of_range'
      what():  vector::_M_range_check: __n (which is 18446744073709551615) >= this->size() (which is 9)
  
  The function could not process the disconnected vertices because it couldn't reach them from source (home). I'm not sure how I'd fix this as I don't think prim's works on disconnected graphs (I could be entirely wrong), but if you don't have a connection to the source how could you span out from it??
  
## Analysis
This project was quite a project and made me really understand the complexity of linked lists, heap, and graphs. I still have a hard time understanding the general application of a minimum spanning tree when I would prefer to use something like a shortest path algorithm for most graph based problems. When thinking about graphs and where these algorithms could be useful in application, it reminded me a lot of the work I've done with game development using C#. When it comes to working with AI in games shortest path algorithms tend to be quite important. But, contrary to how they are typically done, it is normally a good idea to add in some buffers that prevent the AI from performing the algorithm perfectly everytime. Especially in games that want the player to be somewhat powerful, having a perfectly tracking AI be able to find you at any point via the shortest path possible is not exactly fair. So instead you'd add in some random buffers that 'grab' the AI's attention and pull them down a different path occasionally. The difficult part here is finding a good balance, not too aggressive in pursuit, but not too frequent in interuptions that the AI seems clueless. 

BIG O notation:
again, I am still learning Big O so this may be entirely wrong but I will still attempt to analyze my functions

addEdge should be O(E^2) since I am using edgeExists to check if the edge exists, then inserting one if it doesn't exist

addVertex should be O(V) since I am just accessing a list to check if the vertex exists then inserting one if it doesnt

edgeExists should be O(E^2) since I access the list twice inside itself

vertexExists should be O(V) since I am just accessing the list once

print I am unsure of because I would assume it would be O(V+E) because I am just accessing the lists once but I don't think that is correct...

shortestPathSelected should be O(logE of V) where E is edges and V is vertices because I use heap so based on the BigO cheat sheet that would be O(n log(n)) 

minSpanTree should be should also be O(logE of V) where E is edges and V is vertices because I used heap for this one as well via the priority queue

getIDByString should be O(v) because I just search through the vertex list

printPath should be O(r) because I am just accessing the root list 

## Resources

https://cplusplus.com/reference/list/list/

https://www.geeksforgeeks.org/pair-in-cpp-stl/

https://cplusplus.com/reference/vector/vector/

https://iq.opengenus.org/vector-of-pairs-in-cpp/

https://www.geeksforgeeks.org/implement-min-heap-using-stl/
