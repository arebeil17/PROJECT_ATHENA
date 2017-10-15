/*
* File: Node.cpp
* Author: Andres Rebeil
* NetID: andres07
* Date: December 1st, 2015
*
* Description: This file .cpp file contains the implementation of the input class
*/
/**************************************************************************************************/
#include "node.h"
/**************************************************************************************************/

//Default Constructor
Node::Node()
{

}
/**************************************************************************************************/
//Returns a string representation of this Node
string Node::toString() {
	string result = "Inputs: ";

	for (int i = 0; i < inputs.size(); i++) {
		result += " " + inputs.at(i)->name;
	}
	result += " Output: " + output->name;
	result += " Bitwidth: " + to_string(width) + " Delay: " + to_string(delay);

	return result;
}
