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

/**************************************************************************************************/
using namespace std;

class Node { 
	
	private:
	public:
		Node();
		// Variables
		string op;
		float delay = 0.0;
		int width = 0;
		vector<Node*> parentNodes;
		vector<Node*> childNodes;
		vector<Net*> inputs;
		Net* output;
		//Functions
		string toString();
};
 
#endif //Node_H

