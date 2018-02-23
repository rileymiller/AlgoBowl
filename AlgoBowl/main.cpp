#include "Edge.h"
#include "Node.h"
#include <map>
#include <set>
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>


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
void updateEdgeVec(int swapNode, map<int, Node> &nodeMap, vector<Edge> &edgeVec, bool arrOne[], bool arrTwo[]) {
	Node swapNodeNode = nodeMap[swapNode];
	for (int i = 0; i < swapNodeNode.getChildren().size(); i++) {
		if (arrOne[swapNodeNode.getChildren().at(i).target] == 1) {
			edgeVec.push_back(swapNodeNode.getChildren().at(i));
			
		}
		else {
			for (int j = 0; j < edgeVec.size(); j++) {
				if ((edgeVec[j].parent == swapNode && edgeVec[j].target == swapNodeNode.getChildren().at(i).target)
					|| (edgeVec[j].target == swapNode && edgeVec[j].parent == swapNodeNode.getChildren().at(i).target)) {
					edgeVec.erase(edgeVec.begin() + j);
					break;
				}
			}
		}


	}
}
void swapvector(vector<int> &vectorOne, vector<int> &vectorTwo, int node, bool arrOne[], bool arrTwo[], map<int,Node> &nodeMap, vector<Edge> &edgeVec) {
	for (int i = 0; i < vectorOne.size(); i++) {
		if (vectorOne[i] == node) {
			updateCost(node, nodeMap, arrOne);
			updateEdgeVec(node, nodeMap, edgeVec, arrOne, arrTwo);
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


int getTotalCost(vector<int> &vectorOne, vector<int> &vectorTwo, map<int,Node>&nodeMap, bool arr[], vector<Edge> &edgeVec, bool doIt){
	int total_cost = 0;
	for (int j = 0; j < vectorOne.size(); j++) {
		for (int i = 0; i < nodeMap.at(vectorOne[j]).getChildren().size(); i++) {
			if (arr[nodeMap.at(vectorOne[j]).getChildren().at(i).getTarget()] == 0) {
				if (doIt == 1) {
					edgeVec.push_back(nodeMap.at(vectorOne[j]).getChildren().at(i));
				}
				total_cost += nodeMap.at(vectorOne[j]).getChildren().at(i).getCost();
			}
		}
	}
	return total_cost;
} 

int betterTotalCost(vector<Edge> &edgeVec) {
	int totalCost = 0;
	for (int i = 0; i < edgeVec.size(); i++) {
		totalCost += edgeVec[i].cost;
	}
	return totalCost;
}
/*struct less_than_key
{
	inline bool operator() (const Node& nodeOne, const Node& nodeTwo)
	{
		return (nodeOne.getChildren().size < struct2.key);
	}
};*/


int main() {
	srand(time(NULL));
	map<int, Node> nodeMap;
	vector<Node> nodeVector;

	cout << "Hello world" << endl;


	ifstream fin;
	ofstream fout;

	
	//fin.open("input.txt");
	fin.open("input_group5.txt"); //insert input file here 

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
		if (nodeTwo > maxNode) {
			maxNode = nodeTwo;
		}
		if (nodeMap.find(nodeOne) != nodeMap.end()) {
			nodeMap[nodeOne].addChild(Edge(nodeTwo, weight, nodeOne));
		}
		else {
			Node tempNode = Node(nodeOne, Edge(nodeTwo, weight, nodeOne));
			nodeMap.insert(make_pair(nodeOne, tempNode));
		}
		if (nodeMap.find(nodeTwo) != nodeMap.end()) {
			nodeMap[nodeTwo].addChild(Edge(nodeOne, weight, nodeTwo));
		}
		else {
			Node tempNodeTwo = Node(nodeTwo, Edge(nodeOne, weight, nodeTwo));
			nodeMap.insert(make_pair(nodeTwo, tempNodeTwo));
		}
	}


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
	//sort(nodes.begin(), nodes.end());
	cout << endl;
	/*for(int i =0; i < nodes.size(); i++){
		cout << nodes.at(i).getValue() << " : "; 
		cout << nodes[i].getChildren().size();
		cout << endl;
	}*/


	vector<int> vectorOne;
	vector<int> vectorTwo;
	//int k = 0;
	//cout << nodes.size() << "NOED SIZE" << endl;
	while (vectorOne.size() <= maxNode / 2) {
		if (vectorOne.size() < (maxNode / 2)) {
			vectorOne.push_back(nodes[0].getValue());
		}
		else {
			break;
		}
		for (int i = 0; i < nodes[0].getChildren().size(); i++) {
			if (vectorOne.size() < (maxNode / 2)) {
				if (!findElement(vectorOne, nodes[0].getChildren().at(i).getTarget())) {
					vectorOne.push_back(nodes[0].getChildren().at(i).getTarget());
					nodes.erase(nodes.begin() + getIndex(nodes[0].getChildren().at(i).getTarget(), nodes));
				}
			}
			else {
				//vectorTwo.push_back(nodes[0].getChildren().at(i).getTarget());
			}
			//if (getIndex(nodes[0].getChildren().at(i).getTarget(), nodes) != -1) {
			//	cout << getIndex(nodes[0].getChildren().at(i).getTarget(), nodes) << endl;
			//	nodes.erase(nodes.begin() + getIndex(nodes[0].getChildren().at(i).getTarget(), nodes));
			//}
		}
		nodes.erase(nodes.begin());
		//k++;
	}
	for (int i = 0; i < nodes.size(); i++) {
		vectorTwo.push_back(nodes[i].getValue());
	  }
	//sort(vectorOne.begin(), vectorOne.end());
	//sort(vectorTwo.begin(), vectorTwo.end());
	//printvectors(vectorOne, vectorTwo);
	//cout << endl;
	//cout <<	vectorOne.size() << endl;
	//cout << vectorTwo.size() << endl;
	/*for(int i = 0; i < nodes.size(); i++){
		if(i % 2 == 0){
			vectorOne.push_back(nodes.at(i).getValue());
		} else {
			vectorTwo.push_back(nodes.at(i).getValue());
		}
	}*/
	//printvectors(vectorOne, vectorTwo);
	for (int i = 0; i < vectorOne.size(); i++) {
		bitArrayOne[vectorOne[i]] = 1;
	}
	for (int i = 0; i < vectorTwo.size(); i++) {
		bitArrayTwo[vectorTwo[i]] = 1;
	}
	bool rando = 1;
	vector<Edge> edgeVec;
	fin.close();
	int initialCost = getTotalCost(vectorOne, vectorTwo, nodeMap, bitArrayOne, edgeVec, 1);
	int swapIndex;
	int swapIndexTwo;
	int lastSwapped = -1;
	cout << endl;
	vector<int> bestvectorOne = vectorOne;
	vector<int> bestvectorTwo = vectorTwo;
	int bestCost = initialCost;
	int currentCost = 0;
	cout << "Initial cost: " << initialCost << endl;
	//bestCost = currentCost;
	cout << "@#$@$@#$@#$@#$@#$BEST COST: " << bestCost << endl;
	bestvectorOne = vectorOne;
	bestvectorTwo = vectorTwo;
	for (int i = 0; i <= maxNode; i++) {
		bitArrayOneBest[i] = bitArrayOne[i];
	}
	fout.open("output.txt");
	fout << bestCost << "\n";
	for (int i = 0; i < bestvectorOne.size(); i++) {
		fout << bestvectorOne[i] << " ";
	}
	fout << "\n";
	for (int i = 0; i < bestvectorTwo.size(); i++) {
		fout << bestvectorTwo[i] << " ";
	}
	fout << "\n";
	fout.close();
	calcCost(vectorOne, vectorTwo, nodeMap, bitArrayOne);
	calcCost(vectorTwo, vectorOne, nodeMap, bitArrayTwo);
	for (int i = 0; i < edges*250; i++) {
		cout << "I: " << i << endl;
		//cout << "VEC 1 SIZE: " << vectorOne.size() << endl;
		//cout << "VEC 2 SIZE: " << vectorTwo.size() << endl;
		//cout << "EDGEVEC " << edgeVec.size() << endl;
		if (rando == 0) {
			if (i % 10 == 0 && i > 25) {
				swapIndex = vectorOne[rand() % vectorOne.size()];
			}
			else {
				swapIndex = selectNode(vectorOne, vectorTwo, nodeMap, lastSwapped);
			}
		}
		else {
			swapIndex = selectNode(vectorOne, vectorTwo, nodeMap, lastSwapped);
		}
		swapvector(vectorOne, vectorTwo, swapIndex, bitArrayOne, bitArrayTwo, nodeMap, edgeVec);
		if (rando == 0) {
			if (i % 10 == 0 && i > 25) {
				swapIndex = vectorTwo[rand() % vectorTwo.size()];
			}
			else {
				swapIndex = selectNode(vectorTwo, vectorOne, nodeMap, lastSwapped);
			}
		}
		else {
			swapIndex = selectNode(vectorTwo, vectorOne, nodeMap, lastSwapped);
		}
		swapvector(vectorTwo, vectorOne, swapIndex, bitArrayTwo, bitArrayOne, nodeMap, edgeVec);
		currentCost = betterTotalCost(edgeVec);
		cout << "Current Cost: " << currentCost << endl;
		if (currentCost < bestCost) {
			bestCost = currentCost;
			cout << "@#$@$@#$@#$@#$@#$BEST COST: " << bestCost << endl;
			bestvectorOne = vectorOne;
			bestvectorTwo = vectorTwo;
			for (int i = 0; i <= maxNode; i++) {
				bitArrayOneBest[i] = bitArrayOne[i];
			}
			fout.open("output.txt");
			fout << bestCost << "\n";
			for(int i = 0; i < bestvectorOne.size(); i++) {
				fout << bestvectorOne[i] << " ";
			}
			fout << "\n";
			for (int i = 0; i < bestvectorTwo.size(); i++) {
				fout << bestvectorTwo[i] << " ";
			}
			fout << "\n";
			fout.close();
		}
	}
	cout << getTotalCost(bestvectorOne, bestvectorTwo, nodeMap, bitArrayOneBest, edgeVec, 0) << endl;
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