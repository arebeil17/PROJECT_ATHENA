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
		
		//Trim string to remove hidden carriage return characters
		string trim_right(const std::string& str);
};
 
#endif //INPUT_H

