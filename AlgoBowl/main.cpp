#include "Edge.h"
#include "Node.h"
#include <map>
#include <set>
#include <iostream>
#include <fstream>
#include <vector>


using namespace std;

int main() {
	map<int, Node> nodeMap;
	vector<Node> nodeVector;

	cout << "Hello world" << endl;


	ifstream fin;

	fin.open("input.txt"); //insert input file here 

	if (!fin) {
		cerr << "Unable to open file datafile.txt";
	//	exit(1);   // call system to stop
	}

	int vertices;
	int edges; 
	int nodeOne;
	int nodeTwo;
	int weight;
	fin >> vertices;
	fin >> edges;

	while (!fin.eof) {
		fin >> nodeOne;
		fin >> nodeTwo;
		fin >> weight;
		if (nodeMap.find(nodeOne) != nodeMap.end()) {
			nodeMap[nodeOne].addChild(Edge(nodeTwo, weight));
		}
		else {
			Node tempNode = Node(nodeOne, Edge(nodeTwo, weight));
			nodeMap.insert({ nodeOne, tempNode });
		}
		if (nodeMap.find(nodeTwo) != nodeMap.end()) {
			nodeMap[nodeTwo].addChild(Edge(nodeOne, weight));
		}
		else {
			Node tempNodeTwo = Node(nodeTwo, Edge(nodeOne, weight));
			nodeMap.insert({ nodeTwo, tempNodeTwo });
		}
	}

	//ask John how he planned on creating nodes


	/**************************************************/
	//			read in file input to create nodes with fin
	// object. Need to figure out how John was planning on 
	// storing nodes.
	/**************************************************/ 



	//going to need to decide what data structure we will store the nodes in


	//function that sorts data structure according to weight



	//calc net benefit

	//swap

	return 0;
}