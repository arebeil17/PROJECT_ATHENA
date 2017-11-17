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
	this->child = NULL;
	this->parent = NULL;
}
/**************************************************************************************************/
//Add Node pointer to current block
void Block::addNode(Node * newNode)
{
	this->nodeVector.push_back(newNode);
}
/**************************************************************************************************/
