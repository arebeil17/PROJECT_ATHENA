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
bool Scheduler::determineAlapSchecdule(Block * block){

	if (block->timeConstraint > 0) {
		//Reset all traverse Parameters
		block->resetAll();
		block->findLastNodes();

		Node* startNode;
		Node* currentNode;
		Node* parentNode;
		Node* childNode;
		int earliestAlapTime = 0;
		int maxExecuteTime = 0;
		queue<Node*> predecessors;
		int remainingTime = block->timeConstraint;

		for (int i = 0; i < block->nodeVector.size(); i++) {
			startNode = block->nodeVector.at(i);
			remainingTime = block->timeConstraint;

			if (startNode->last && !startNode->scheduled) {
				currentNode = startNode;
				while (currentNode != NULL) {
					//schedule current node
					//Determine lastScheduled time
					if (!currentNode->last) {
						earliestAlapTime = block->timeConstraint;
						maxExecuteTime = 0;
						for (int k = 0; k < currentNode->childNodes.size(); k++) {
							childNode = currentNode->childNodes.at(k);
							if (std::find(block->nodeVector.begin(), block->nodeVector.end(),
								childNode) != block->nodeVector.end()) {
								if (childNode->executionTime >= maxExecuteTime) {
									maxExecuteTime = childNode->executionTime;
								}
								if ((childNode->scheduled) 
									&& (childNode->alapTime <= earliestAlapTime)){
									earliestAlapTime = childNode->alapTime;
								}
							}
						}
						remainingTime = earliestAlapTime;
						currentNode->alapTime = remainingTime - (currentNode->executionTime - 1);
					}
					else {
						currentNode->alapTime = remainingTime - (currentNode->executionTime - 1);
					}
					currentNode->scheduled = true;
					//Add all current nodes precessors to queue
					for (int j = 0; j < currentNode->parentNodes.size(); j++) {

						parentNode = currentNode->parentNodes.at(j);
						//Check that parentNode is within current block
						if (std::find(block->nodeVector.begin(), block->nodeVector.end(),
							parentNode) != block->nodeVector.end()) {

							if (!parentNode->marked) {
								predecessors.push(parentNode);
								parentNode->marked = true;
							}
						}
					}
					if (!predecessors.empty) {
						currentNode = predecessors.front;
						predecessors.pop();
					}
					else {
						currentNode = NULL; //done, no more nodes
					}
				}
			}
		}
	}
	//Scheduling failed, constraint not met
	block->scheduled = false;
}
/**************************************************************************************************/
