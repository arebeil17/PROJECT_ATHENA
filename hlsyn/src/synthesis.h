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
#include <algorithm>
#include "node.h"
#include "net.h"
#include "block.h"

/**************************************************************************************************/
using namespace std;

class Synthesis { 
	
	public:
		vector<Block*> blockVector;

		//Default Constructor
		Synthesis();
	
};
 
#endif //SYNTHESIS_H

