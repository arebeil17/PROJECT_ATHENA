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

/**************************************************************************************************/
using namespace std;

class Synthesis { 
	
	public:

		//Default Constructor
		Synthesis();
        //Custom Constructor 
        Synthesis(vector<string> netlistLines, vector<Node>* nodeListVector);
        
        Block nextLevelBlock[100];        
		vector<Block*>   blockVector;
        vector<string>  netlistLines;
        vector<Node>*   nodeListVector; 
        unsigned int    currentLine;
        unsigned int    blockId;

        bool parseBlocksNodes(Block* parentBlock, unsigned int currentLevel);	
        bool parseBlocks_prefix();
        bool makeBlocks();
        bool buildNextBlock(Block* currentBlock, string type, unsigned int level, string condText);

		void setAllBlockPointers();

		void printBlocks();
};
 
#endif //SYNTHESIS_H

