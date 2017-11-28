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
//Reset all nodes' traverse paraneters
void Block::resetAll(){
	for (unsigned int i = 0; i < nodeVector.size(); i++) {
		nodeVector.at(i)->reset();
	}
}
/**************************************************************************************************/
//Find Root Nodes
bool Block::findRootNodes() {
	unsigned int nodeInputCount = 0;

	for (unsigned int i = 0; i < this->nodeVector.size(); i++) {
		//Check all node inputs are of type input net
		for (unsigned int j = 0; j < this->nodeVector.at(i)->inputs.size(); j++) {
			if (!this->nodeVector.at(i)->inputs.at(j)->type.compare("input"))
				nodeInputCount++;
		}
		//Check if current Nodes nets are all inputs
		if (nodeInputCount == this->nodeVector.at(i)->inputs.size()) {
			//Add to root node vector
			rootNodes.push_back(this->nodeVector.at(i));
		}
		nodeInputCount = 0;
	}
	if (this->rootNodes.size() > 0) return true;
	else return false;
}
