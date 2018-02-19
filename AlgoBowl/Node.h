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
	set<Edge> children;
	Node* parent;
	Node();
	Node(int value, Edge child);

	void addChild(int value, Edge child);
};