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
#include <fstream>
#include <sstream>
#include <string>
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
        string type;
        unsigned int blockId;
        unsigned int level;
		
		//Constructor
		Block();
		//Add Node pointer to current block
		void addNode(Node * newNode);

};

#endif //Block_H


