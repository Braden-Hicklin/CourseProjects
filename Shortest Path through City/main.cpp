#include <iostream>

#include "graph.cpp"

#define para cout << "\n" << endl;

int main() {

    int choice = -1; 
    int distance;
    string name1, name2;

    int Vertices = 9;
    Graph g(Vertices);

    g.addVertex("Home"); // id 0
    g.addVertex("Store"); // id 1
    g.addVertex("School"); // id 2...
    g.addVertex("Gym");
    g.addVertex("Work");
    g.addVertex("Park");
    g.addVertex("Cafe");
    g.addVertex("Restaurant");
    g.addVertex("Pool");
    para;

/*
    g.addEdge("Home", "Store", 30);
    g.addEdge("Home", "Gym", 10);
    g.addEdge("Gym", "Store", 20);
    g.addEdge("Store", "School", 10);
    g.addEdge("Work", "School", 40);
*/

    /* g.addEdge("Home", "Store", 4);
        g.addEdge("Home", "Restaurant", 8);
        g.addEdge("Store", "School", 8);
        g.addEdge("Store", "Restaurant", 11);
        g.addEdge("School", "Gym", 7);
        g.addEdge("School", "Pool", 2);
        g.addEdge("School", "Park", 4);
        g.addEdge("Gym", "Work", 9);
        g.addEdge("Gym", "Park", 14);
        g.addEdge("Work", "Park", 10);
        g.addEdge("Park", "Cafe", 2);
        g.addEdge("Cafe", "Restaurant", 1);
        g.addEdge("Cafe", "Pool", 6);
        g.addEdge("Restaurant", "Pool", 7);
    */

    g.addEdge("Home", "Store", 20);
    g.addEdge("Home", "School", 50);
    g.addEdge("Store", "Gym", 30);
    g.addEdge("School", "Work", 80);
    g.addEdge("Work", "Gym", 20);
    g.addEdge("Gym", "Park", 50);
    g.addEdge("Work", "Park", 70);
    g.addEdge("Work", "Pool", 10);
    g.addEdge("Pool", "Restaurant", 15);
    g.addEdge("Cafe", "Gym", 22);
    g.addEdge("Cafe", "Pool", 20);
    para;

    g.shortestPathSelected("Home", "Park");
    para;

    g.minSpanTree();
    para;

    g.print();

    while(choice != 0) {
        cout << "\n\n";
        cout << "Graph Algorithm Tests" << endl;
        cout << "This Graph is based on distances between locations on a map" << endl;
        cout << "1. Add Edge" << endl;
        cout << "2. Print Locations and Edges" << endl;
        cout << "3. Shortest Path between two locations" << endl;
        cout << "4. Minimum Spanning Tree Algorithm" << endl;
        //cout << "6. Check if Location exists" << endl;
        //cout << "7. Check if Edge exists" << endl; 
        cout << "0. Quit" << endl;
        cin >> choice;

        switch(choice) {
            case(1):
                cout << "Enter the names of the locations you would like to create an edge between, and the distance between them" << endl;
                cout << "Location 1: ";
                cin >> name1;
                cout << "Location 2: ";
                cin >> name2;
                cout << "Distance between: ";
                cin >> distance;
                g.addEdge(name1, name2, distance);
                break;
            case(2):
                g.print();
                break;
            case(3):
                cout << "Enter the names of the locations you'd like to find the shortest path between" << endl;
                cout << "Location 1: ";
                cin >> name1;
                cout << "Location 2: ";
                cin >> name2;
                g.shortestPathSelected(name1, name2);
                break;
            case(4):
                g.minSpanTree();
                break;
            default:
                cout << "Invalid selection, please try again" << endl;
                break;
        }
    }
    return 0;
}