#include "Edge.h"
#include "Node.h"

#include <set>
#include <iostream>
#include <fstream>


using namespace std;

int main() {

	cout << "Hello world" << endl;


	ifstream fin;

	fin.open("input.txt"); //insert input file here 

	if (!fin) {
    cerr << "Unable to open file datafile.txt";
    exit(1);   // call system to stop
	}

	int vertices;
	int edges; 
	fin >> vertices;
	fin >> edges;

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