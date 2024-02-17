#pragma once

#include <string>
#include <vector>

#include "edge.h"

using namespace std;

struct Vertex {
    string locationName; // name of the place representing the vertex
    int id; // automated id that is determined by size of the list containing the vertices
};
