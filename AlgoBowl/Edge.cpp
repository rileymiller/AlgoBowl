using namespace std;
#include "Edge.h"

Edge::Edge() {
}

Edge::Edge(Node target, int cost) {
	this->target = target;
	this->cost = cost;
}