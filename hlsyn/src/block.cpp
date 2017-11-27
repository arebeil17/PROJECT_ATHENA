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
