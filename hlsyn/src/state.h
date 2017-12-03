#ifndef state_H
#define state_H
/*************/
/*
 * File: state.h
 * Author: Andres Rebeil, Kyle, Nikitha
 * NetID: andres07
 * Date: December 1st, 2017
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

class State { 
	
	public:
		string name;
		string nextStateName;
		int cycle;
		vector<Node*> scheduledNodes;
		string verilogString;

		State();
		State(string name, string nextStateName, int cycle);

		bool generateVerilogString();
		
};
 
#endif //State_H