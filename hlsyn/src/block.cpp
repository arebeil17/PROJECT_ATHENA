/*
* File: block.cpp
* Author: Andres Rebeil
* NetID: andres07
* Date: November 17th, 2017
*
* Description: This file .cpp file contains the implementation of the block class
*/
/**************************************************************************************************/
#include "block.h"
/**************************************************************************************************/

//Default Constructor
Block::Block()
{
	this->branchConditionNet = NULL;
	this->prev = NULL;
	this->next = NULL;
	this->parent = NULL;
	this->adjacent = NULL;
    level = 0;
    blockId = 0xFFFFFFFF;
	timeConstraint = 0;
	scheduled = false;
}
/**************************************************************************************************/
//Add Node pointer to current block
void Block::addNode(Node * newNode)
{
	newNode->parentBlockId = this->blockId;
	this->nodeVector.push_back(newNode);
}
/**************************************************************************************************/
//Reset all nodes' traverse parameters
void Block::resetAll(){
	for (unsigned int i = 0; i < nodeVector.size(); i++) {
		nodeVector.at(i)->reset();
	}
}
/**************************************************************************************************/
//Find last Nodes in block
void Block::findLastNodes() {
	
	Node * currentNode;
	Node * childNode;

	for (unsigned int i = 0; i < this->nodeVector.size(); i++) {
		
		currentNode = this->nodeVector.at(i);
		currentNode->last = false;

		//Check if output net is type output
		if (!currentNode->output->type.compare("output")) {
			currentNode->last = true;
		//Else Check if current Node has children, and check if outside current block
		}else if (!currentNode->childNodes.empty()) {
			//Check if children 
			for (int j = 0; j < currentNode->childNodes.size(); j++) {
				childNode = currentNode->childNodes.at(j);
				if (this->blockId < childNode->parentBlockId) {
					currentNode->last = true;
					break;
				}
			}
		}
		else { //No children
			currentNode->last = true;
		}

	}
}
/**************************************************************************************************/
void Block::printSchedulingInfo(){
	cout << "--------------------------------------------------------------------------" << endl;
	cout << "Block " << this->blockId << " Schedule " << " Constraint: "<< timeConstraint <<endl;
	cout << "--------------------------------------------------------------------------" << endl;
	if (this->scheduled) {
		for (unsigned int i = 0; i < this->nodeVector.size(); i++) {
			string op = nodeVector.at(i)->op;
			int diff = 8 - op.length();
			if (diff > 0) for (int j = 0; j < diff; j++) op += " ";
			cout << "Node Id: "<<nodeVector.at(i)->id <<"  Op: " << op << " Last: " << nodeVector.at(i)->last <<"  Alap: " << setw(3) << nodeVector.at(i)->alapTime << " Asap: " << nodeVector.at(i)->asapTime << " FDS Schedule: " << nodeVector.at(i)->scheduleTime <<endl;
		}
	}
	else {
		if(this->nodeVector.size() == 0) 
			cout << "Not scheduled. Block Empty." << endl;
		else
			cout << "Not scheduled. Constraint cannot not be met for specified netlist file." << endl;
	}
	cout << endl;
}

