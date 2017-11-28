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


	}
	//Scheduling failed, constraint not met
	block->scheduled = false;
}
/**************************************************************************************************/
bool Scheduler::asapSchedule(Block * block){
	if (block->timeConstraint <= 0) {
	    //Scheduling failed, constraint not met
	    block->scheduled = false;
        return false;
	}
	//Reset all traverse Parameters
	block->resetAll();
    
    bool scheduleNotDone = true;
    // Initialize
    for (unsigned int i = 0; i< block->nodeVector.size();i++){
        block->nodeVector[i]->output->available = false;
        block->nodeVector[i]->output->nAvailable = false;
    }
    int exec_cycle = 1;
    //vector start from time 1 too;
    //asap.push_back(newScheduled);
    while(scheduleNotDone){
        vector<Node*> newScheduled;
        //executing phase
        for(unsigned int i = 0; i< block->nodeVector.size();i++){
            bool nodeAvailable = true;
            for(unsigned int j = 0; j< block->nodeVector.at(i)->inputs.size();j++){
                if(block->nodeVector.at(i)->inputs.at(j)){
                    nodeAvailable &= block->nodeVector.at(i)->inputs.at(j)->available;
                }
            }
            if(nodeAvailable&&
               //node available but not scheduled yet
               (block->nodeVector.at(i)->visited==false)){
                if(block->nodeVector.at(i)->op=="MUL"){
                    block->nodeVector.at(i)->nVisited=true;
                    block->nodeVector.at(i)->nAsapCount++;
                    newScheduled.push_back(block->nodeVector.at(i));
                }
                else if(block->nodeVector.at(i)->op=="DIV"){
                    block->nodeVector.at(i)->nVisited=true;
                    block->nodeVector.at(i)->nAsapCount++;
                    newScheduled.push_back(block->nodeVector.at(i));
                }
                else if(block->nodeVector.at(i)->op=="MOD"){
                    block->nodeVector.at(i)->nVisited=true;
                    block->nodeVector.at(i)->nAsapCount++;
                    newScheduled.push_back(block->nodeVector.at(i));
                }
                else {
                    block->nodeVector.at(i)->nVisited=true;
                    block->nodeVector.at(i)->nMarked=true;
                    block->nodeVector.at(i)->output->nAvailable=true;
                    newScheduled.push_back(block->nodeVector.at(i));
                }
            }
            else if((block->nodeVector.at(i)->visited==true)&&
                    //node scheduled but not finished yet
                    (block->nodeVector.at(i)->marked==false)){
                //complete at current cycle
                if((block->nodeVector.at(i)->op=="MUL")&&
                    (block->nodeVector.at(i)->asapCount==2)){
                    block->nodeVector.at(i)->nMarked=true;
                    block->nodeVector.at(i)->output->nAvailable=true;
                }
                else if((block->nodeVector.at(i)->op=="DIV")&&
                    (block->nodeVector.at(i)->asapCount==3)){
                    block->nodeVector.at(i)->nMarked=true;
                    block->nodeVector.at(i)->output->nAvailable=true;
                } 
                else if((block->nodeVector.at(i)->op=="MOD")&&
                    (block->nodeVector.at(i)->asapCount==3)){
                    block->nodeVector.at(i)->nMarked=true;
                    block->nodeVector.at(i)->output->nAvailable=true;
                }
                //need more cycles
                else if((block->nodeVector.at(i)->op=="MUL")&&
                    (block->nodeVector.at(i)->asapCount<2)){
                    block->nodeVector.at(i)->nAsapCount++;
                }
                else if((block->nodeVector.at(i)->op=="DIV")&&
                    (block->nodeVector.at(i)->asapCount<3)){
                    block->nodeVector.at(i)->nAsapCount++;
                }
                else if((block->nodeVector.at(i)->op=="MOD")&&
                    (block->nodeVector.at(i)->asapCount<3)){
                    block->nodeVector.at(i)->nAsapCount++;
                }
            }
        }
        //increment cycle
        exec_cycle++;
        
        //check phase
        bool done = true;
        for(unsigned int i = 0; i< block->nodeVector.size();i++){
            done &= block->nodeVector.at(i)->marked;
        }
        scheduleNotDone = !done;
        if(!done){
            //one cycle end, and there are new scheduled nodes, push to array
            asap.push_back(newScheduled);
        }

        // Then update "n"flag to flag
        //
        for(unsigned int i = 0; i< block->nodeVector.size();i++){
           block->nodeVector.at(i)->marked = block->nodeVector.at(i)->nMarked;
           block->nodeVector.at(i)->visited = block->nodeVector.at(i)->nVisited;
           block->nodeVector.at(i)->asapCount = block->nodeVector.at(i)->nAsapCount;
           block->nodeVector.at(i)->output->available = block->nodeVector.at(i)->output->nAvailable;
        }
    }
return true;
}

void Scheduler::depthFirstSearch(Node * source, bool alap){
	if (alap) {
		queue<Node*> nodeQueue;
		Node* currentNode;
	}
}
/**************************************************************************************************/

