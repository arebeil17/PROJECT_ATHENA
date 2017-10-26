/*
* File: input.cpp
* Author: Andres Rebeil
* NetID: andres07
* Date: December 1st, 2015
*
* Description: This file .cpp file contains the implementation of the input class
*/
/**************************************************************************************************/
#include "input.h"
/**************************************************************************************************/

//Default Constructor
Input::Input()
{

}
/**************************************************************************************************/
//Reads specified netlist input file
bool Input::readInputFile(char *inputFile){
    
    ifstream inputFS;
	
	string currentLine; //Temp string stores current line read in from netlist file
	
	inputFS.open(inputFile);

	if (!inputFS.is_open()) //Check that valid input file was provided
	{
		cout << "Could not read from input file " << inputFile << endl;
		return false;
	}
	else
	{
		while (inputFS.good())
		{	
		    getline(inputFS, currentLine);
	
			if(currentLine != "") 
				this->netlistLines.push_back(currentLine);

		};
		inputFS.close();
		return true;
	}
	return false;
}
/**************************************************************************************************/
//Verify line for errors
bool Input::errorCheck(string line){
	
	//TODO: check for errors in current line
	// ...
	// ...
	//Case 1: x = a + b nswfgjwbnfk
	
	//Case 2: x = a $ b
	
	//Case 3: etc ...
	
	return true;
}
/**************************************************************************************************/