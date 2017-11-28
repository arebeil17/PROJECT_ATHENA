#ifndef Node_H
#define Node_H
/*************/
/*
 * File: Node.h
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
#include "net.h"
#include "delay.h"

/**************************************************************************************************/
using namespace std;

class Node { 
	
	private:
	public:
		// Variables
		int id;
		string op;
		string moduleName;
        // Node operation in text format
		string statement;
		bool visited;
		bool marked;
        // ASAP flag
		bool nVisited;
		bool nMarked;
		bool signedBit;
		//Delay to reach node
		float pathDelay;
		float delay;
		int width;
		int depth;
		vector<Node*> parentNodes;
		vector<Node*> childNodes;
		Node* criticalNode;
		vector<Net*> inputs;
		Net* output;
		int parentBlockId;
        // ASAP execution count
        unsigned int asapCount;
        unsigned int nAsapCount;

		int alapTime;
		int asapTime;
		int scheduleTime;
		int executionTime;
		int frameWidth;
		//Functions
		Node();
		string toString();
		//Set delay
		bool updateDelay();
		//Get delay
		float getDelay();
		//Get delay
		float getDelay(string op, int bitwidth);
		//compute node delay
		void computeDelay();
		//Reset Traverse Parameters
		void reset();
};
 
#endif //Node_H

