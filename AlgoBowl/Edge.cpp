using namespace std;
#include "Edge.h"

Edge::Edge() {
}

Edge::Edge(int target, int cost) {
	this->target = target;
	this->cost = cost;
}

int Edge::getCost() {
	return cost;
}

int Edge::getTarget() {
	return target;
}