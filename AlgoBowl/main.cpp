#include "Edge.h"
#include "Node.h"
#include <map>
#include <set>
#include <iostream>
#include <fstream>
#include <vector>


using namespace std;
void printSets(set<int> &setOne, set<int> &setTwo) {
	cout << "Set One: ";
	for (const int &value : setOne) {
		cout << " " << value;
	}
	cout << endl;
	cout << "Set Two: ";
	for (const int &value : setTwo) {
		cout << " " << value;
	}
}
int selectNode(set<int> &setOne, set<int> &setTwo, map<int, Node> &nodeMap, int &lastSwapped) {
	int maxCost = -99999;
	int maxInt = -1;
	for (const int &value : setOne) {
		if (nodeMap[value].setCost > maxCost && value != lastSwapped) {
			maxInt = value;
			maxCost = nodeMap[value].setCost;
		}
	}
	lastSwapped = maxInt;
	return maxInt;
}

void swapSet(set<int> &setOne, set<int> &setTwo, int node) {
	if (setOne.find(node) != setOne.end()) {
		setOne.erase(node);
		setTwo.insert(node);
	}
	else {
		setTwo.erase(node);
		setOne.insert(node);
	}
}
void calcCost(set<int> &setOne, set<int> &setTwo, map<int,Node> &nodeMap) {
	for (const int &value : setOne) {
		int setCost = 0;
		for (int i = 0; i < nodeMap.at(value).getChildren().size(); i++) {
			if (setTwo.find(nodeMap.at(value).getChildren().at(i).getTarget()) != setTwo.end()) {
				setCost += nodeMap.at(value).getChildren().at(i).getCost();
			}
			else {
				setCost -= nodeMap.at(value).getChildren().at(i).getCost();;
			}
		}
		nodeMap.at(value).setCost = setCost;
	}
}
int getIndex(int value, vector<Node> &nodes){
	for(int i =0; i < nodes.size(); i++){
		if(nodes.at(i).getValue() == value)
			return i;
	}

	return -1;
}


int getTotalCost(set<int> &setOne, set<int> &setTwo, map<int,Node>&nodeMap){
	int total_cost = 0;
	for(const int &value : setOne){
		for(int i = 0; i < nodeMap.at(value).getChildren().size(); i++){
			//cout << i << " ";
			if(setTwo.find(nodeMap.at(value).getChildren().at(i).getTarget()) != setTwo.end()){
				total_cost += nodeMap.at(value).getChildren().at(i).getCost();
			}
		}
	}

	return total_cost;
} 

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

	while (!fin.eof()) {
		fin >> nodeOne;
		fin >> nodeTwo;
		fin >> weight;
		if (nodeMap.find(nodeOne) != nodeMap.end()) {
			nodeMap[nodeOne].addChild(Edge(nodeTwo, weight));
		}
		else {
			Node tempNode = Node(nodeOne, Edge(nodeTwo, weight));
			nodeMap.insert(make_pair(nodeOne, tempNode));
		}
		if (nodeMap.find(nodeTwo) != nodeMap.end()) {
			nodeMap[nodeTwo].addChild(Edge(nodeOne, weight));
		}
		else {
			Node tempNodeTwo = Node(nodeTwo, Edge(nodeOne, weight));
			nodeMap.insert(make_pair(nodeTwo, tempNodeTwo));
		}
	}

	//cout << nodeMap << endl;

	/*for (auto& kv : nodeMap) {
    std::cout << kv.first << " has value " << kv.second << std::endl;
	}*/

    vector<Node> nodes;
	for (auto &p : nodeMap) {
    cout << "m[" << p.first << "] = ";
    p.second.printChildren();
    cout << endl;
    nodes.push_back(p.second);
	}

	cout << endl;
	for(int i =0; i < nodes.size(); i++){
		cout << nodes.at(i).getValue() << " : "; 
		nodes.at(i).printChildren();
		cout << endl;
	}


	set<int> setOne;
	set<int> setTwo;
	

	for(int i = 0; i < nodes.size(); i++){
		if(i % 2 == 0){
			setOne.insert(nodes.at(i).getValue());
		} else {
			setTwo.insert(nodes.at(i).getValue());
		}
	}

	int initialCost = getTotalCost(setOne, setTwo, nodeMap);
	int swapIndex;
	int swapIndexTwo;
	int lastSwapped = -1;
	cout << endl;
	cout << getTotalCost(setOne, setTwo, nodeMap) << endl;
	set<int> bestSetOne = setOne;
	set<int> bestSetTwo = setTwo;
	int bestCost = initialCost;
	int currentCost = 0;

	for (int i = 0; i < edges; i++) {
		calcCost(setOne, setTwo, nodeMap);
		calcCost(setTwo, setOne, nodeMap);
		swapIndex = selectNode(setOne, setTwo, nodeMap, lastSwapped);
		swapSet(setOne, setTwo, swapIndex);
		calcCost(setTwo, setOne, nodeMap);
		swapIndex = selectNode(setTwo, setOne, nodeMap, lastSwapped);
		swapSet(setTwo, setOne, swapIndex);
		currentCost = getTotalCost(setOne, setTwo, nodeMap);
		cout << "BEST COST: " << bestCost << endl;
		if (currentCost < bestCost) {
			//cout << "BEST COST: " << bestCost << endl;
			bestCost = currentCost;
			bestSetOne = setOne;
			bestSetTwo = setTwo;
		}
		cout << "Cost: " << getTotalCost(setOne, setTwo, nodeMap) << endl;
	}
	printSets(setOne, setTwo);
	cout << endl;
	printSets(bestSetOne, bestSetTwo);
	cout << endl;
	cout << getTotalCost(bestSetOne, bestSetTwo, nodeMap) << endl;
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