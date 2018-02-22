using namespace std;
#include "Edge.h"

Edge::Edge() {
}

Edge::Edge(int target, int cost, int parent) {
	this->target = target;
	this->parent = parent;
	this->cost = cost;
}

int Edge::getCost() {
	return cost;
}

int Edge::getTarget() {
	return target;
}