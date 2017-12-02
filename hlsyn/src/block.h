#ifndef BLOCK_H
#define BLOCK_H
/*************/
/*
* File: Block.h
* Author: Andres Rebeil
* NetID: andres07
* Date: November 17th, 2017
*
* Description:
*/
/**************************************************************************************************/
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdarg>
#include <cstring>
#include <math.h>
#include <cstdio>
#include "node.h"

/**************************************************************************************************/
using namespace std;

class Block {

	private:

	public:
		Net * branchConditionNet;
        string  condText;
		//Block Pointers
		Block * prev;
		Block * next;
		Block * parent;
		vector<Block *> children;
		Block * adjacent;
		vector<Node *> nodeVector;
		vector<Node*> rootNodes;
        string type;
        unsigned int blockId;
        unsigned int level;
		int timeConstraint;
		bool scheduled;
		
		//Constructor
		Block();
		//Add Node pointer to current block
		void addNode(Node * newNode);
        void resetAll();
		//Reset all nodes' traverse paraneters
		//Find root nodes
		void findLastNodes();

		void printSchedulingInfo();
		
};

#endif //Block_H


