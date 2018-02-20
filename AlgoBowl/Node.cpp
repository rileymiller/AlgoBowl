using namespace std;
#include "Node.h"

Node::Node() {

}
Node::Node(int value, Edge child) {
	children.push_back(child);
	this->value = value;
}

void Node::addChild(Edge child){
	children.push_back(child);
}

int Node::getValue() {
	return value;
}

void Node::printChildren() {
	for(int i = 0; i < children.size(); i++){
		cout << "target: " << children.at(i).getTarget() << ", cost: " << children.at(i).getCost() << " | ";
	}
}

vector<Edge> Node::getChildren() const {
	return children;
}