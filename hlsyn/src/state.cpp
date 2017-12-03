/*
* File: state.cpp
* Author: Andres Rebeil
* NetID: andres07
* Date: December 1st, 2015
*
* Description: This file .cpp file contains the implementation of the state class
*/
/**************************************************************************************************/
#include "state.h"
/**************************************************************************************************/
//Default Constructor
State::State(){
	name = "";
	nextStateName = "";
	cycle = 0;
	verilogString = "";
}
/**************************************************************************************************/
State::State(string name, string nextStateName, int cycle) {
	this->name = name;
	this->nextStateName = nextStateName;
	this->cycle = cycle;
}
/**************************************************************************************************/
bool State::generateVerilogString(){

	this->verilogString = ""; //Clear string

	this->verilogString += "\t\t\t" + this->name + ":begin\n";

	for (unsigned int i = 0; i < scheduledNodes.size(); i++) {
		
		//Check special case: Mux has three inputs
		if(!scheduledNodes.at(i)->opSymbol.compare("?")) {
			if (scheduledNodes.at(i)->inputs.size() != 3) return false;
			this->verilogString += "\t\t\t\t" + scheduledNodes.at(i)->output->name + " = (";
			this->verilogString += scheduledNodes.at(i)->inputs.at(0)->name + ") ? ";
			this->verilogString += scheduledNodes.at(i)->inputs.at(1)->name + " : ";
			this->verilogString += scheduledNodes.at(i)->inputs.at(2)->name + ";\n";
		}else {
			if (scheduledNodes.at(i)->inputs.size() != 2) return false;
			this->verilogString += "\t\t\t\t" + scheduledNodes.at(i)->output->name + " = ";
			this->verilogString += scheduledNodes.at(i)->inputs.at(0)->name;
			this->verilogString += " " + scheduledNodes.at(i)->opSymbol + " ";
			this->verilogString += scheduledNodes.at(i)->inputs.at(1)->name + ";\n";
		}
		
	}
	this->verilogString += "\t\t\t\tNextState <= " + nextStateName + ";\n";
	this->verilogString += "\t\t\tend\n";

	return true;
}
