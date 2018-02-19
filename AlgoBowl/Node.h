#pragma once
using namespace std;
#include "Edge.h"
#include <set>
//class Node;
class Edge;
class Node {
public:
	int value;
	int finalCost;
	int setCost;
	set<Edge> children;
	Node();
	Node(int value, Edge child);

	void addChild(Edge child);
};