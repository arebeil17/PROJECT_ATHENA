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
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>
#include <cstdio>
#include "node.h"
#include "net.h"

/**************************************************************************************************/
using namespace std;

class Datapath { 
	
	public:
		// Variables
		vector<string>* netlistLines;
		vector<Net>  netListVector;
		vector<Node> nodeListVector;
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
		int parseNetlistLines();
		//Print information of all nodes created from netlist file
		void printNodeListVector();
		//Update each nodes bitwidth based off output
		void updateNodeBitwidth();
		//Update all node delays based off bitwidth
		void updateNodeDelay();
};
 
#endif //DATAPATH_H

