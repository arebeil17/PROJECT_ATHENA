/*
* File: Scheduler.cpp
* Author: Andres Rebeil
* NetID: andres07
* Date: November 21st, 2017
*
* Description: This file .cpp file contains the implementation of the Scheduler class
*/
/**************************************************************************************************/
#include "scheduler.h"
/**************************************************************************************************/

//Default Constructor
Scheduler::Scheduler()
{
	
}

/**************************************************************************************************/
void Scheduler::forceDirectedScheduling(Block* block){

}
/**************************************************************************************************/
void Scheduler::determineAlapSchecdule(Block * block){

	if (block->timeConstraint > 0) {
		//Reset all traverse Parameters
		block->resetAll();

		queue<Node*> nodeQueue;
		Node* currentNode;

	}
	//Scheduling failed, constraint not met
	block->scheduled = false;
}
/**************************************************************************************************/
