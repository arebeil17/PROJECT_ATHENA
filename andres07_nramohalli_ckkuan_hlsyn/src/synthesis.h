#ifndef SYNTHESIS_H
#define SYNTHESIS_H
/*************/
/*
 * File: Synthesis.h
 * Author: Andres Rebeil
 * NetID: andres07
 * Date: November 21st, 2017
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
#include <cmath>
#include <algorithm>
#include "node.h"
#include "net.h"
#include "block.h"
#include "state.h"

/**************************************************************************************************/
using namespace std;

class Synthesis { 
	
	public:
		int timeConstraint;
		Block nextLevelBlock[100];
		vector<Block*>   blockVector;
		vector<string>  netlistLines;
		vector<Node>*   nodeListVector;
		unsigned int    currentLine;
		unsigned int    blockId;
		vector<State> states;


		//Default Constructor
		Synthesis();
        //Custom Constructor 
        Synthesis(int timeConstraint, vector<string> netlistLines, vector<Node>* nodeListVector);
        
        bool parseBlocksNodes(Block* parentBlock, unsigned int currentLevel);	
        bool parseBlocks_prefix();
        bool makeBlocks();
        bool buildNextBlock(Block* currentBlock, string type, unsigned int level, string condText);
        bool setBlockConstraint(int timeConstraint);

		void setAllBlockPointers();

		void printBlocks();

		void generateStates();
};
 
#endif //SYNTHESIS_H

