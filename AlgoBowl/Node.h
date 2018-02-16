#pragma once
using namespace std;
#include "Edge.h"
#include <set>
class Node;
class Node {
public:
	int value;
	int finalCost;
	set<Edge> children;
	Node* parent;
	Node();
	Node(int value, Edge child);
};