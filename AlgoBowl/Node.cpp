using namespace std;
#include "Node.h"

Node::Node() {

}
Node::Node(int value, Edge child) {
	children.insert(child);
	this->value = value;
}