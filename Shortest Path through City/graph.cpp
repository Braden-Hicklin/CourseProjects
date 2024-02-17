#include <iostream>
#include <bits/stdc++.h>

#include "graph.h"

using namespace std;

void Graph::addVertex(string name){
    Vertex *newVertex = new Vertex; // allocates memory to new vertex

    // checks if vertex exists
    // if true, print that it already exists and moves on
    // if false, creates new vertex
    bool checkVertex = vertexExists(name);
    if(checkVertex == true) {
        cout << "That Vertex already exists" << endl;

    } else {    
        newVertex->locationName = name; // new locationName
        newVertex->id = vertexList.size(); // id unique to each based on number of vertices in vertexList vector

        vertexList.push_back(newVertex); // adds vertex to vertexList vector
        // lets user know the code worked properly
        cout << "Vertex " << newVertex->locationName << " successfully created with the id of " << newVertex->id << endl;
    }
}

Graph::Graph(int V) {
    this->V = V; // V becomes number of vertices initialized here
    adj = new vector<pair<int, int>>[V]; // allocates memory to vector adjacency list based on number of vertices (V)
}

void Graph::addEdge(string source, string destination, int weight) {
    // attempted to give a return type string for the user
    // string success = "Edge successfully created";
    // string failure = "Unable to create Edge";
    
    Edge *newEdge = new Edge; // allocates memory to new edge

    bool checkDest = vertexExists(destination); // checks if the destination vertex exists
    bool checkSrc = vertexExists(source); // checks if the source vertex exists

    bool checkEdge = edgeExists(source, destination); // checks if the edge between the two vertices exists

    if(checkDest && checkSrc == true) { // first check vertices
        if(checkEdge == true) { // then check edge
            cout << "That edge already exists." << endl; // edge was invalid
        
        } else { // both vertices and edge check passed (true for vertices, false for edge)
            for(int i = 0; i < vertexList.size(); i++) { // iterate through vertexList
                if(vertexList.at(i)->locationName == source) // get source vertex
                    newEdge->source = vertexList.at(i); // set current vertex to source
                if(vertexList.at(i)->locationName == destination) // get destination vertex
                    newEdge->destination = vertexList.at(i); // set current vertex to destination
            }
            newEdge->weight = weight;
            
            edgeList.push_back(newEdge);

            adj[newEdge->source->id].push_back(make_pair(
                newEdge->destination->id, newEdge->weight));

            adj[newEdge->destination->id].push_back(make_pair(
                newEdge->source->id, newEdge->weight));

            cout << "Edge successfully created between " << newEdge->source->locationName << " and " << newEdge->destination->locationName << endl;
        }
    } else { // vertices were invalid
        cout << "The source vertex " << source << " and destination vertex " << destination << " do not exist." << endl;
    }
}

bool Graph::edgeExists(string source, string destination) {
    for(int i = 0; i < edgeList.size(); i++) {
        if(edgeList.at(i)->source->locationName == source) {
            if(edgeList.at(i)->destination->locationName == destination) {
                return true;
            }
        }
    }
    return false;
}

bool Graph::vertexExists(string name) {
    for(int i = 0; i < vertexList.size(); i++) {
        if(vertexList.at(i)->locationName == name) {
            return true;
        }
    }

    return false;
}

void Graph::print() {

    cout << "Printing Vertices..." << endl;
    for(int v = 0; v < vertexList.size(); v++)
        
        // add below code after 'locationName' to see ids along with their respective locationName
        /*<< "\t" << vertexList.at(v)->id */ 
        
        cout << vertexList.at(v)->locationName << endl;

    cout << "\nPrinting Edges..." << "\nSrc\tDest\tWeight" << endl;
    for(int e = 0; e < edgeList.size(); e++)
        cout << edgeList.at(e)->source->locationName << " -> " << edgeList.at(e)->destination->locationName << "\t" << edgeList.at(e)->weight << endl;

}

int Graph::getIDByString(string vertexName) {
    bool checkVertex = vertexExists(vertexName); // checks if the input source vertex even exists
    int location;
    if(checkVertex != false) {
        for(int v = 0; v < V; v++) {
            if(vertexList.at(v)->locationName == vertexName) {
                location = vertexList.at(v)->id;
            }
        } 
    } else {
        cout << "Invalid source vertex selected" << endl;
        return INF;
    }

    return location;
}

/* Dijkstra's Pseudo Code
   HEAVILY INSPIRED BY THE PRIORITY QUEUE DESIGN FOUND ON https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm

    potentially add in new list in graph.h like ## list<pair<string, int>>* adjList;
    
    void shortestPath(Graph ??how do I plan on pulling the graph??, source vertex ??use string and iterate through
        vertex list to find matching string, how will I use it as a source vertex??) {
        dist[source] = 0                           // 

        create priority queue ?? priority_queue<pair<id, weight>, vector<pair<id, weight>>, greater<pair<id,weight>>> Q?? ---> min heap priority queue

        for each vertex v in Graph.Vertices:
            if v != source
                dist[v] ← INF       ?? make this a list, list<int> dist(v, INF);
                Q.push(v, dist[v]) 

        while (!Q.empty()):                      
            u ← Q.top().second --> list operator
            Q.pop(); 

            for loop ?? would iterator be more efficient ?? call pointer ?? use first/second operators                    
            for each neighbor v of u:   ?? could use pair instead of neighbors since you struggle implementing the neighbors --sigh--           
                alt ← dist[u] + adj(u, v)
                if alt < dist[v]:
                    dist[v] ← alt
                    prev[v] ← u
                    Q.decrease_priority(v, alt)

     return dist, prev
}

*/

// Change shortest path algo to search from one dest to another rather than showing path of all destinations
/*void Graph::shortestPath(string source){
    int location;

    bool checkVertex = vertexExists(source); // checks if the input source vertex even exists
    if(checkVertex != false) {
        for(int v = 0; v < V; v++) {
            if(vertexList.at(v)->locationName == source) {
                location = vertexList.at(v)->id;
            }
        } 
    } else {
        cout << "Invalid source vertex selected, cannot run SSSP algorithm." << endl;
        return;
    } // now a helper function

    int location = getVertexByString(source);
    if (location == INF) {
        cout << "Could not perform Shortest Path algorithm, source location was invalid" << endl;
        return;
    }

    // creates a min heap for priority queue based on the adjlist design (pair<source/dest, weight>)
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> Q; 
    vector<int> dist(V, INF); // creates a vector for distances

    Q.push(make_pair(0, location));
    dist[location] = 0;

    while(!Q.empty()) {
        int u = Q.top().second;
        Q.pop();

        vector<pair<int, int> >::iterator it;
        for(it = adj[u].begin(); it != adj[u].end(); ++it) {
            int v = (*it).first;
            int w = (*it).second;
            
        // cout << "printing dist[u]..." << dist[u] << endl; debug printing

            if(dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                Q.push(make_pair(dist[v], v));
            }

        }
    }

    cout << "Source\t" << "Destination\t" << "Distance" << endl;
    for(int i = 0; i < V; i++) {
        cout << source << " -> " << vertexList.at(i)->locationName << "\t\t" << dist[i] << endl;
    }
} */

// Decided to modify the original dijkstra's algorithm to make it from a chosen source to a chosen destination
// That way it differs from the more broad approach of the minimum spanning tree algorithm. This function takes
// two string inputs for location names from the user, gets the id for those vertices using the getIDByString
// prints the distance from location to source
// UPDATED -- Added a root vector like the one in prim's algorithm, printPath function helps print the route you would
// need to take in order to achieve the shortest path
void Graph::shortestPathSelected(string source, string destination) {
    int sourceID = getIDByString(source);
    int destinationID = getIDByString(destination);

    if(sourceID == INF || destinationID == INF) {
        cout << "Could not perform Shortest Path algorithm, source location was invalid" << endl;
        return;
    }

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> Q; 
    vector<int> dist(V, INF);
    vector<int> root(V, -1);

    Q.push(make_pair(0, sourceID));
    dist[sourceID] = 0;

    while(!Q.empty()) {
        int u = Q.top().second;
        Q.pop();

        vector<pair<int, int>>::iterator it;
        for(it = adj[u].begin(); it != adj[u].end(); ++it) {
            int v = (*it).first;
            int w = (*it).second;

            // checks for target, ends once target is reached
            if(dist[v] == dist[destinationID]) {
                // if shorter path is found, update distance 
                if(dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    Q.push(make_pair(dist[v], v));
                    root[v] = u;
                }
            } 
        }
    }

    for(int i = 0; i < V; i++) {
    // debug print to make sure the loop ends once the target has been reached
    //  cout << "This is a distance stored  in dist list, if its INF it hasn't been searched: " << dist[i] << endl;
        if(i == destinationID) {
            cout << "The shortest distance from " << source << " to " << vertexList.at(i)->locationName << " is " << dist[i] << endl;   
        }
    }

    for(int i = 0; i < V; i++) {
        if(i != sourceID) {
            if(i == destinationID) {
                cout << source << " -> ";
                printPath(i, destinationID, root);
            }
        }
    }
}

// Helper function to print the route taken to achieve shortest path
void Graph::printPath(int currentVertex, int targetVertex, vector<int> root) {
    // Ignores source vertex 
    if(currentVertex == 0) {
        return;
    }
    
    // Prints root vertices until target vertex is met
    printPath(root[currentVertex], targetVertex, root);
    cout << vertexList.at(currentVertex)->locationName;
    if(currentVertex != targetVertex) {
        cout << " -> ";
    }
}

/* void Graph::minSpanTree(?? do we need to check for source, shouldn't it default to 0 ??) {
    
    int source = vertex ?? should we get this from string or just default to 0 ??
    
    create a priority queue Q; ?? same as dijkstra's probably ??
    like dijkstra's, distance will be our key
    distance = INF ?? same way as dijkstras or a for loop that iterates through edgelist getting weights ??
    
    
    list visited[] ?? how should this be done, list, vector, bool array ??
    list parent[] ?? list, vector, array -- should it be a pair that contains both parent and child ??

    distance(source) = 0;

    while(!Q.empty()):
        get min value  ?? how should I get this, same as dijkstra's Q.top().second to isolate min key then pop to delete label ?? 
        int u = Q.top().second
        Q.pop()
        
        Iterate through adj and decrease key of Q  
        for iterator = adj[u].begin(); iterator < adj[u].end(); ++iterator:
            int v = (*it).first
            int w = (*it).second ?? follow the same route as dijkstras

            similar to dijkstra's except check bool and compare dist to w ?? does distance[v] become w?
            if(visited[v] == false && distance[v] > w):
                change distance 
                Q.push(make_pair(dist[v], v)) ?? again, like dijkstras
    
    print MST

} */


// Nearly identical to the shortest path algorithm but added root and visited lists
// that indicate where you have been (visited) and which vertex the current vertex 
// spans from (root)
// UPDATE -- root is now found in both functions, however the root vector here is used to show singular parent
// whereas shortest path root vector is used to show the route
void Graph::minSpanTree() { // doesn't need any input, always spanning from source and graph is inherited by the class
    int source = 0;

    // same priority queue design found in the dijkstra's algorithm, based on adj vector setup
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> Q;
    
    vector<int> dist(V, INF);
    vector<int> root(V, -1); // read that 'root' is better nomenclature for this array... don't know the validity of this, parent seems better but root fits the 'tree' theme
    vector<bool> visited(V, false); // visited list that contains bool, true for visited, false for unvisited, all vertices init at false

    Q.push(make_pair(0, source));
    dist[source] = 0;

    while(!Q.empty()) {
        int u = Q.top().second;
        Q.pop();

        if(visited[u] == true) {
            continue;
        }
    
        visited[u] = true;
        vector<pair<int, int>>::iterator it;
        for(it = adj[u].begin(); it != adj[u].end(); ++it){
            int v = (*it).first;
            int w = (*it).second;

            // if the vertex hasn't been visited, and the weight (distance) is smaller than
            // current distance, update distance to new weight (distance)
            if(visited[v] == false && dist[v] > w) {
                dist[v] = w;
                Q.push(make_pair(dist[v], v));
                root[v] = u; 
            }
        }
    }

    for (int i = 1; i < V; ++i) // i = 1 because source span to source is redundant
        cout << vertexList.at(root[i])->locationName << " -> " << vertexList.at(i)->locationName << endl;
}
