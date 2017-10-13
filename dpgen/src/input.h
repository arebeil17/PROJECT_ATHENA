#ifndef INPUT_H
#define INPUT_H
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

/**************************************************************************************************/
using namespace std;

class Input { 
	
	public:
		vector<string> netlistLines;
		//Default Constructor
		Input();
		
		//Reads specified netlist input file
		bool readInputFile(char *inputFile);
		
		//Verify line for errors
		bool errorCheck(string line);
		
};
 
#endif //INPUT_H

