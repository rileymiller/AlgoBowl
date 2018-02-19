using namespace std;
#include "Edge.h"

Edge::Edge() {
}

Edge::Edge(int target, int cost) {
	this->target = target;
	this->cost = cost;
}