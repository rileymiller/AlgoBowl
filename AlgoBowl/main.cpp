#include "Edge.h"
#include "Node.h"
#include <map>
#include <set>
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <cstdlib>


using namespace std;
void printvectors(vector<int> &vectorOne, vector<int> &vectorTwo) {
	cout << "vector One: ";
	for (int j = 0; j < vectorOne.size(); j++) {
		cout << " " << vectorOne[j];
	}
	cout << endl;
	cout << "vector Two: ";
	for (const int &value : vectorTwo) {
		cout << " " << value;
	}
}
int selectNode(vector<int> &vectorOne, vector<int> &vectorTwo, map<int, Node> &nodeMap, int &lastSwapped) {
	int maxCost = -99999;
	int maxInt = -1;
	for (int j = 0; j < vectorOne.size(); j++) {
		if (nodeMap[j].setCost > maxCost && vectorOne[j] != lastSwapped) {
			maxInt = vectorOne[j];
			maxCost = nodeMap[j].setCost;
		}
	}
	lastSwapped = maxInt;
	return maxInt;
}
void updateCost(int swapNode, map<int, Node> &nodeMap, bool arr[]) {
	nodeMap[swapNode].setCost *= -1;
	for (int i = 0; i < nodeMap[swapNode].getChildren().size(); i++) {
		int target = nodeMap[swapNode].getChildren().at(i).target;
		Edge edge = nodeMap[swapNode].getChildren().at(i);
		if (arr[target] == 0) {
			nodeMap[target].setCost -= 2 * edge.cost;
		}
		else {
			nodeMap[target].setCost += 2 * edge.cost;
		}
	}
}
void swapvector(vector<int> &vectorOne, vector<int> &vectorTwo, int node, bool arrOne[], bool arrTwo[], map<int,Node> &nodeMap) {
	for (int i = 0; i < vectorOne.size(); i++) {
		if (vectorOne[i] == node) {
			updateCost(node, nodeMap, arrOne);
			vectorTwo.push_back(node);
			arrTwo[node] = 1;
			vectorOne.erase(vectorOne.begin() + i);
			arrOne[node] = 0;
			/*cout << "Vector One" << endl;
			for (int i = 0; i < vectorOne.size(); i++) {
				cout << vectorOne[i] << ", ";
			}
			cout << endl;
			for (int i = 0; i < 7; i++) {
				cout << arrOne[i] << ", ";
			}
			cout << endl;*/
			return;
		}
	}
	/*for (int i = 0; i < vectorTwo.size(); i++) {
		if (vectorTwo[i] == node) {
			vectorOne.push_back(node);
			arrOne[node] = 1;
			vectorTwo.erase(vectorOne.begin() + i);
			arrTwo[node] = 0;
			cout << "Vector 2" << endl;
			for (int i = 0; i < vectorTwo.size(); i++) {
				cout << vectorTwo[i] << ", ";
			}
			cout << endl;
			for (int i = 0; i < 7; i++) {
				cout << arrTwo[i] << ", ";
			}
			cout << endl;
			return;
		}
	}*/
}
bool findElement(vector<int> &vec, int element) {
	for (int i = 0; i < vec.size(); i++) {
		if (vec[i] == element) {
			return true;
		}
	}
	return false;
}

void calcCost(vector<int> &vectorOne, vector<int> &vectorTwo, map<int,Node> &nodeMap, bool arr[]) {
	for (int j = 0; j < vectorOne.size(); j++) {
		int setCost = 0;
		for (int i = 0; i < nodeMap.at(vectorOne[j]).getChildren().size(); i++) {
			if (arr[nodeMap.at(vectorOne[j]).getChildren().at(i).getTarget()] == 0) {
				setCost += nodeMap.at(vectorOne[j]).getChildren().at(i).getCost();
			}
			else {
				setCost -= nodeMap.at(vectorOne[j]).getChildren().at(i).getCost();
		}
	}
		nodeMap.at(vectorOne[j]).setCost = setCost;
	}
}
int getIndex(int value, vector<Node> &nodes){
	for(int i =0; i < nodes.size(); i++){
		if(nodes.at(i).getValue() == value)
			return i;
	}

	return -1;
}


int getTotalCost(vector<int> &vectorOne, vector<int> &vectorTwo, map<int,Node>&nodeMap, bool arr[]){
	int total_cost = 0;
	for (int j = 0; j < vectorOne.size(); j++) {
		for (int i = 0; i < nodeMap.at(vectorOne[j]).getChildren().size(); i++) {
			if (arr[nodeMap.at(vectorOne[j]).getChildren().at(i).getTarget()] == 0) {
				total_cost += nodeMap.at(vectorOne[j]).getChildren().at(i).getCost();
			}
		}
	}


	/*for(int j = 0; j < vectorOne.size(); j++){
		for(int i = 0; i < nodeMap.at(vectorOne[j]).getChildren().size(); i++){
			//cout << "node: " << vectorOne[j] << endl;
			//cout << "edge " << nodeMap.at(vectorOne[j]).getChildren().at(i).getTarget() << " " << endl;
			if(findElement(vectorTwo, nodeMap.at(vectorOne[j]).getChildren().at(i).getTarget())){
			//	cout << "j: " << j << endl;
			//	cout << "target: " << nodeMap.at(vectorOne[j]).getChildren().at(i).getTarget() << endl;
				total_cost += nodeMap.at(vectorOne[j]).getChildren().at(i).getCost();
			}
		}
	}*/

	return total_cost;
} 

int main() {
	srand(time(NULL));
	map<int, Node> nodeMap;
	vector<Node> nodeVector;

	cout << "Hello world" << endl;


	ifstream fin;
	ofstream fout;

	fout.open("output.txt");

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
	int maxNode = 0;
	fin >> vertices;
	fin >> edges;

	while (!fin.eof()) {
		fin >> nodeOne;
		fin >> nodeTwo;
		fin >> weight;
		if (nodeOne > maxNode) {
			maxNode = nodeOne;
		}
		else if (nodeTwo) {
			maxNode = nodeTwo;
		}
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
	/*bool bitArrayOne[10000];
	bool bitArrayTwo[10000];
	bool bitArrayOneBest[10000];
	bool bitArrayTwoBest[10000];*/
	/*bool bitArray
	bool* bitArrayOne = NULL;
	bool* bitArrayOneBest = NULL;
	bitArrayOneBest = new bool[maxNode + 1];
	bitArrayOne = new bool[maxNode+1];
	bool* bitArrayTwo = NULL;
	bool* bitArrayTwoBest = NULL;
	bitArrayTwoBest = new bool[maxNode + 1];
	bitArrayTwo = new bool[maxNode+1];
	*/

	bool *bitArrayOne = new bool[maxNode + 1];
	bool *bitArrayOneBest = new bool[maxNode + 1];
	bool *bitArrayTwo = new bool[maxNode + 1];
	bool *bitArrayTwoBest = new bool[maxNode + 1];
	for (int i = 0; i <= maxNode; i++) {
	bitArrayOne[i] = 0;
	bitArrayTwo[i] = 0;
	}
	//cout << bitArrayOne[2] << endl;
	//cout << nodeMap << endl;

	/*for (auto& kv : nodeMap) {
    std::cout << kv.first << " has value " << kv.second << std::endl;
	}*/

    vector<Node> nodes;
	for (auto &p : nodeMap) {
    //cout << "m[" << p.first << "] = ";
    //p.second.printChildren();
    //cout << endl;
    nodes.push_back(p.second);
	}

	/*cout << endl;
	for(int i =0; i < nodes.size(); i++){
		cout << nodes.at(i).getValue() << " : "; 
		nodes.at(i).printChildren();
		cout << endl;
	}*/


	vector<int> vectorOne;
	vector<int> vectorTwo;
	

	for(int i = 0; i < nodes.size(); i++){
		if(i % 2 == 0){
			vectorOne.push_back(nodes.at(i).getValue());
		} else {
			vectorTwo.push_back(nodes.at(i).getValue());
		}
	}
	for (int i = 0; i < vectorOne.size(); i++) {
		bitArrayOne[vectorOne[i]] = 1;
	}
	for (int i = 0; i < vectorOne.size(); i++) {
		cout << vectorOne[i] << ", ";
	}
	for (int i = 0; i < 7; i++) {
		cout <<  bitArrayOne[i] << ", ";
	}
	for (int i = 0; i < vectorTwo.size(); i++) {
		bitArrayTwo[vectorTwo[i]] = 1;
	}
	bool rando = 0;

	int initialCost = getTotalCost(vectorOne, vectorTwo, nodeMap, bitArrayOne);
	int swapIndex;
	int swapIndexTwo;
	int lastSwapped = -1;
	cout << endl;
	cout << getTotalCost(vectorOne, vectorTwo, nodeMap, bitArrayOne) << endl;
	vector<int> bestvectorOne = vectorOne;
	vector<int> bestvectorTwo = vectorTwo;
	int bestCost = initialCost;
	int currentCost = 0;
	cout << "Initial cost: " << initialCost << endl;
	cout << "EDGED: " << edges << endl;
	calcCost(vectorOne, vectorTwo, nodeMap, bitArrayOne);
	calcCost(vectorTwo, vectorOne, nodeMap, bitArrayTwo);
	for (int i = 0; i < edges; i++) {
		cout << "I: " << i << endl;
		if (rando == 0) {
			cout << "Calc cost 1" << endl;
			//calcCost(vectorOne, vectorTwo, nodeMap, bitArrayOne);
			//cout << "Calc cost 2" << endl;
			//calcCost(vectorTwo, vectorOne, nodeMap, bitArrayTwo);
		//	cout << "Calculated costs" << endl;
			cout << "selecting node" << endl;
			swapIndex = selectNode(vectorOne, vectorTwo, nodeMap, lastSwapped);
			cout << "selected" << endl;
		}
		else {
			swapIndex = vectorOne[rand() % vectorOne.size()];
		}
		//cout << "got index" << swapIndex << " " << vectorOne.size() <<  endl;
		cout << "Swapping" << endl;
		swapvector(vectorOne, vectorTwo, swapIndex, bitArrayOne, bitArrayTwo, nodeMap);
		cout << "swapped nodes" << endl;
		if (rando == 0) {
			//calcCost(vectorTwo, vectorOne, nodeMap, bitArrayTwo);
			swapIndex = selectNode(vectorTwo, vectorOne, nodeMap, lastSwapped);
		}
		else {
			swapIndex = vectorTwo[rand() % vectorTwo.size()];
		}
		swapvector(vectorTwo, vectorOne, swapIndex, bitArrayTwo, bitArrayOne, nodeMap);
		cout << "start calc cost" << endl;
		currentCost = getTotalCost(vectorOne, vectorTwo, nodeMap, bitArrayOne);
		cout << "Current Cost: " << currentCost << endl;
		//cout << "done calc cost" << currentCost << endl;
		//cout << "BEST COST: " << bestCost << endl;
		if (currentCost < bestCost) {
			bestCost = currentCost;
			cout << "@#$@$@#$@#$@#$@#$BEST COST: " << bestCost << endl;
			for (int i = 0; i < 7; i++) {
				cout << "BEST value: " << bitArrayOne[i] << endl;
			}
			bestvectorOne = vectorOne;
			bestvectorTwo = vectorTwo;
			for (int i = 0; i <= maxNode; i++) {
				bitArrayOneBest[i] = bitArrayOne[i];
			}
			//bitArrayOneBest = bitArrayOne;
			//bitArrayTwoBest = bitArrayTwo;
			fout << bestCost << "\n";
			for(int i = 0; i < bestvectorOne.size(); i++) {
				fout << bestvectorOne[i] << " ";
			}
			fout << "\n";
			for (int i = 0; i < bestvectorTwo.size(); i++) {
				fout << bestvectorTwo[i] << " ";
			}
			fout << "\n";
		}
		//cout << "Cost: " << getTotalCost(vectorOne, vectorTwo, nodeMap) << endl;
	}
	printvectors(vectorOne, vectorTwo);
	cout << endl;
	printvectors(bestvectorOne, bestvectorTwo);
	cout << endl;
	for (int i = 0; i < 11; i++) {
		cout << "value: " << bitArrayOneBest[i] << endl;
	}
	cout << getTotalCost(bestvectorOne, bestvectorTwo, nodeMap, bitArrayOneBest) << endl;
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