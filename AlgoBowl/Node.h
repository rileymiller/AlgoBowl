#pragma once
using namespace std;
#include "Edge.h"
#include <set>
#include <vector>
#include <iostream>
//class Node;
class Edge;
class Node {
public:
	int value;
	int finalCost;
	int setCost;
	vector<Edge> children;
	Node();
	Node(int value, Edge child);

	void addChild(Edge child);
	int getValue();
	void printChildren();
};