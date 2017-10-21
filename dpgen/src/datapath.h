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
#include "delay.h"

/**************************************************************************************************/
using namespace std;

class Datapath { 
	
	public:
		// Variables
		vector<string>* netlistLines;
		vector<Net>  netListVector;
		vector<Node> nodeListVector;

		//Custom constructors
		Datapath(vector<string>* netlistLines);


		//Default Constructor
		Datapath();

		int createNetList(string* nowParsingText, string type, int width, bool signedBit);
		bool createNodeInputs(string* nowParsingText, vector<Net*>* inputNets);
		int parseNetlistLines();

		void printNodeListVector();

};
 
#endif //DATAPATH_H

