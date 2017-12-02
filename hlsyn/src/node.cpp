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
Node::Node(){
	id = 0;
	pathDelay = 0.0;
	delay = 0.0;
	width = 0;
	last = false;
	scheduled = false;
	visited = false;
	marked = false;
	signedBit = false;
	criticalNode = NULL;
	depth = 0;
	parentBlockId = 0;
	//New Variables for FDS
	forceData = ForceData();
	alapTime = 0;
	asapTime = 0;
	scheduleTime = 0;
	executionTime = 0;
	
    asapCount = 1;
    nAsapCount = 1;
	nVisited = false;
	nMarked = false;
}
/**************************************************************************************************/
//Returns a string representation of this Node
string Node::toString() {
	string result = "Inputs: ";

	for (unsigned int i = 0; i < inputs.size(); i++) {
		result += " " + inputs.at(i)->name;
	}
	result += " Output: " + output->name;
	result += " Bitwidth: " + to_string(width) +/*" Delay: " + to_string(delay) + " Path Delay: " + to_string(pathDelay) +*/ " ParentBlock Id: " + to_string(parentBlockId);

	return result;
}
//Update delay based off current bitwidth
bool Node::updateDelay(){
	float delay = getDelay();
	if (delay > 0) {
		this->delay = delay;
		return true;
	}
	return false;
}
/**************************************************************************************************/
//Get delay
float Node::getDelay() {
	return getDelay(this->op, this->width);
}
/**************************************************************************************************/
//Get delay based off operation and bitwidth
float Node::getDelay(string op, int bitwidth)
{
	executionTime = ALU_CYCLES;

	if (!op.compare("REG")) {
		switch (bitwidth) {
			case 1:  return REG_1B;
			case 2:  return REG_2B;
			case 8:  return REG_8B;
			case 16: return REG_16B;
			case 32: return REG_32B;
			case 64: return REG_64B;
		}
	}
	if (!op.compare("ADD")) {
		switch (bitwidth) {
			case 1:  return ADD_1B;
			case 2:  return ADD_2B;
			case 8:  return ADD_8B;
			case 16: return ADD_16B;
			case 32: return ADD_32B;
			case 64: return ADD_64B;
		}
	}
	if (!op.compare("SUB")) {
		switch (bitwidth) {
			case 1:  return SUB_1B;
			case 2:  return SUB_2B;
			case 8:  return SUB_8B;
			case 16: return SUB_16B;
			case 32: return SUB_32B;
			case 64: return SUB_64B;
		}
	}
	if (!op.compare("MUL")) {
		executionTime = MULT_CYCLES;
		switch (bitwidth) {
			case 1:  return MUL_1B;
			case 2:  return MUL_2B;
			case 8:  return MUL_8B;
			case 16: return MUL_16B;
			case 32: return MUL_32B;
			case 64: return MUL_64B;
		}
	}

	if (!op.compare("COMP_LT") || 
		!op.compare("COMP_EQ") || 
		!op.compare("COMP_GT")) {
		switch (bitwidth) {
			case 1:  return COMP_1B;
			case 2:  return COMP_2B;
			case 8:  return COMP_8B;
			case 16: return COMP_16B;
			case 32: return COMP_32B;
			case 64: return COMP_64B;
		}
	}
	if (!op.compare("MUX2x1")) {
		switch (bitwidth) {
			case 1:  return MUX_1B;
			case 2:  return MUX_2B;
			case 8:  return MUX_8B;
			case 16: return MUX_16B;
			case 32: return MUX_32B;
			case 64: return MUX_64B;
		}
	}

	if (!op.compare("SHR")) {
		switch (bitwidth) {
			case 1:  return SHR_1B;
			case 2:  return SHR_2B;
			case 8:  return SHR_8B;
			case 16: return SHR_16B;
			case 32: return SHR_32B;
			case 64: return SHR_64B;
		}
	}

	if (!op.compare("SHL")) {
		switch (bitwidth) {
			case 1:  return SHL_1B;
			case 2:  return SHL_2B;
			case 8:  return SHL_8B;
			case 16: return SHL_16B;
			case 32: return SHL_32B;
			case 64: return SHL_64B;
		}
	}

	if (!op.compare("DIV")) {
		executionTime = DIV_CYCLES;
		switch (bitwidth) {
			case 1:  return DIV_1B;
			case 2:  return DIV_2B;
			case 8:  return DIV_8B;
			case 16: return DIV_16B;
			case 32: return DIV_32B;
			case 64: return DIV_64B;
		}
	}

	if (!op.compare("MOD")) {
		executionTime = MOD_CYCLES;
		switch (bitwidth) {
			case 1:  return MOD_1B;
			case 2:  return MOD_2B;
			case 8:  return MOD_8B;
			case 16: return MOD_16B;
			case 32: return MOD_32B;
			case 64: return MOD_64B;
		}
	}

	if (!op.compare("INC")) {
		switch (bitwidth) {
			case 1:  return INC_1B;
			case 2:  return INC_2B;
			case 8:  return INC_8B;
			case 16: return INC_16B;
			case 32: return INC_32B;
			case 64: return INC_64B;
		}
	}

	if (!op.compare("DEC")) {
		switch (bitwidth) {
			case 1:  return DEC_1B;
			case 2:  return DEC_2B;
			case 8:  return DEC_8B;
			case 16: return DEC_16B;
			case 32: return DEC_32B;
			case 64: return DEC_64B;
		}
	}
	return 0;
}
/**************************************************************************************************/
//compute node delay
void Node::computeDelay()
{
	//Update max path delay to node
	float max = 0.0;
	float pathDelay = 0.0;

	for (unsigned int i = 0; i < this->parentNodes.size(); i++) {
		//If parent node is not a Register then include node delay as part of path delay
		if (this->parentNodes.at(i)->op.compare("REG") != 0)
			pathDelay = this->parentNodes.at(i)->pathDelay + this->parentNodes.at(i)->delay;
		else
			pathDelay = 0.0;

		if (max <= pathDelay) {
			max = pathDelay;
			this->criticalNode = this->parentNodes.at(i);
			this->depth = this->parentNodes.at(i)->depth + 1;
		}
	}
	this->pathDelay = max;
}
/**************************************************************************************************/
//Reset Traverse Parameters
void Node::reset(){
	scheduled = false;
	visited = false;
	marked = false;
}
/**************************************************************************************************/
