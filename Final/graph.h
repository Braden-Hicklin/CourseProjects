#pragma once

#include <list>
#include <vector>
#include <queue>

#include "edge.h"
#include "vertex.h"

#define INF 999

class Graph {
    public:
        // init graph using number of vertices
        Graph(int V);
    
        // takes two strings, a destination and a source, and an int, weight, and creates an edge, adds edge to edgeList
        // also adds the edge identifiers (source and destination vertex ids) to adj
        void addEdge(string source, string destination, int weight);
        // takes a string and creates a vertex, adds vertex to vertexList    
        void addVertex(string name);
        void print();

        // could be private utility functions, but user might benefit from seeing if a vertex/edge exists
        // takes two strings, returns a bool
        bool edgeExists(string source, string destination);
        // takes one string returns a bool
        bool vertexExists(string name);

        // shortest path algorithm based on the priority queue pseudo code found on https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm
        // void shortestPath(string source); no longer in use kept in code for reference sake
        
        // takes two strings one for a source and another for a destination, prints out shortest path and route taken
        void shortestPathSelected(string source, string destination);
        // prints out minimum spanning tree based on prim's algorithm, source is always 0 (first vertex) and graph is native to class so no input needed
        void minSpanTree();

    private:
        // utility functions
        // takes a string for the vertex name (locationName) and returns its respective ID as an int
        int getIDByString(string vertexName);
        // takes two integers, an index and a targetVertex ID, and a vector, prints the adjacent components of root vector
        void printPath(int currentVertex, int targetVertex, vector<int> root);
        
        // used for initialization of the graph
        // this was supposed to be dynamically sizeable but I couldn't get that functionality to work properly...
        int V; 

        // used from GeeksforGeeks priority_queue (min and max heap) guide
        // most important, stores the id's of vertices adjacent to each other
        vector<pair<int, int>>* adj; 
        
        // stores pointer to edges in a vector
        // used to call locationNames of source and destination vertices, and weight
        vector<Edge*> edgeList; 
        // stores the vertices in a vector
        // used to call locationNames and use ID's for indexing
        vector<Vertex*> vertexList; 
};
