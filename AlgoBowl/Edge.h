#pragma once
#include "Node.h"
using namespace std;

class Edge {
public:
	int cost;
	Node target;
	Edge();
	Edge(Node target, int cost);
};

