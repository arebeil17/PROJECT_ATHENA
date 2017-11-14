#ifndef DATAPATH_H
#define DATAPATH_H
/*************/
/*
 * File: Input.h
 * Author: Andres Rebeil
 * NetID: andres07
 * Date: December 1st, 2015
 *
 * Description: 
 */
 /**************************************************************************************************/
#include <vector>
#include <queue>
#include <list>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>
#include <cstdio>
#include <algorithm>
#include "node.h"
#include "net.h"

/**************************************************************************************************/
using namespace std;

class Datapath { 
	
	public:
		float criticalDelay;
		int currentLine;
		vector<string>* netlistLines;
		vector<Net>  netListVector;
		vector<Node> nodeListVector;
		vector<Node*> rootNodes;
		list<Node*> criticalPath;
		int maxBitwidth;
		//Custom constructors
		Datapath(vector<string>* netlistLines);


		//Default Constructor
		Datapath();
		//Create Netlist from parsed netlist string and specified parameters
		int createNetList(string* nowParsingText, string type, int width, bool signedBit);
		//Create node inputs from parsed string and input net vector
		bool createNodeInputs(string* nowParsingText, vector<Net*>* inputNets);
		//Parse all netlist lines read from netlist file
		bool parseNetlistLines();
		//Print information of all nodes created from netlist file
		void printNodeListVector();
		//Update each nodes bitwidth based off output
		void updateAllNodeBitwidth();
		//Update all node delays based off bitwidth
		void updateAllNodeDelay();
		//Find Root Nodes
		bool findRootNodes();
		//Determine critical path of circuit by perform BFS on node graph
		float determineCriticalPath();
		//creates critical path list given the final node
		void createCriticalPathList(Node* finalNode);
		//Perform BFS given source node and return maximum path delay
		void breadthFirstSearch(Node* source);
		//Expand current node by updating path delay and setting it's children
		bool expandNode(Node* currentNode);
		//Print Root Nodes
		void printRootNodes();
		//Print critical path info
		void printCriticalPathInfo(bool full);
		//Print all information by setting all to true else just critical path
		bool printAll(bool all);
		
};
 
#endif //DATAPATH_H

