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
			
			//Trim string by removing \r\n or other hidden characters
			currentLine = trim_right(currentLine);

			if(currentLine.compare("") != 0) 
				this->netlistLines.push_back(currentLine);

		};
		inputFS.close();
		
		//Check for empty input file
		if (netlistLines.size() == 0) {
			cout << "\nEmpty netlistFile provided. Aborted netlist conversion." << endl;
			return false;  
		} else
			return true;
	}
	return false;
}
/**************************************************************************************************/
//Right trim
//
string Input::trim_right(const std::string& str)
{
	const std::string pattern = " \f\n\r\t\v";
	return str.substr(0, str.find_last_not_of(pattern) + 1);
}