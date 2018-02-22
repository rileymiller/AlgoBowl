#pragma once
#include "Node.h"
using namespace std;

class Edge {
public:
	int cost;
	int target;
	int parent;
	Edge();
	Edge(int target, int cost, int parent);
	int getCost();
	int getTarget();
};

