#pragma once
#include "Node.h"
using namespace std;

class Edge {
public:
	int cost;
	int target;
	Edge();
	Edge(int target, int cost);
	int getCost();
	int getTarget();
};

