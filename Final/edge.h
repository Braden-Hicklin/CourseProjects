#pragma once

#include <string>

#include "vertex.h"

using namespace std;

struct Edge {
    Vertex *source; // points to source Vertex
    Vertex *destination; // points to destination vertex
    int weight; // weight/cost/value
};