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
Scheduler::Scheduler(){
	
}
/**************************************************************************************************/
bool Scheduler::forceDirectedScheduling(Block* block){
    while(fdsNotDone){
		if (updateTimeFrame(block)) {
			updateDistributions(block);
			updateSelfForce(block);
			updatePredecessorForces(block);
			updateSucessorForces(block);
			scheduleNode(block);
		}
		else {
			fdsNotDone = false;
			cout << "Impossible Time Constaint. Scheduling Aborted." << endl;
			return false;
		}
    };
	return true;
}
/**************************************************************************************************/
bool Scheduler::updateTimeFrame(Block* block){
	
	if (!asapSchedule(block)) {
		return false;
	}
    determineAlapSchedule(block);

    for(unsigned int i = 0; i< block->nodeVector.size(); i++){
        block->nodeVector.at(i)->updateFrameParams();        
        if(block->nodeVector.at(i)->asapTime==block->nodeVector.at(i)->alapTime){
            block->nodeVector.at(i)->scheduleTime = block->nodeVector.at(i)->asapTime;
        }
    }
    return true;
}
/**************************************************************************************************/
bool Scheduler::updateDistributions(Block* block){
    //clear distribution and update by new probabilities
    aluDistribution.clear();
    multDistribution.clear();
    divModDistribution.clear();
    aluDistribution.push_back(0.0);
    multDistribution.push_back(0.0);
    divModDistribution.push_back(0.0);

    for(int i = 1; i<=block->timeConstraint; i++){
        float aluTemp = 0.0;
        float multTemp = 0.0;
        float divModTemp = 0.0;
        for(unsigned int j = 0; j< block->nodeVector.size(); j++){
            if(block->nodeVector.at(j)->op=="MUL"){
                multTemp+=block->nodeVector.at(j)->forceData.probabilities.at(i);
            }
            else if (block->nodeVector.at(j)->op=="DIV"){
                divModTemp+=block->nodeVector.at(j)->forceData.probabilities.at(i);
            }
            else if (block->nodeVector.at(j)->op=="MOD"){
                divModTemp+=block->nodeVector.at(j)->forceData.probabilities.at(i);
            }
            else{
                aluTemp+=block->nodeVector.at(j)->forceData.probabilities.at(i);
            }
        }
        aluDistribution.push_back(aluTemp);
        multDistribution.push_back(multTemp);
        divModDistribution.push_back(divModTemp);
    }
//#if 0
	cout << endl << "All distribution: \n";
	cout << "--------------------------------------------------------------------------" << endl;
	cout << "aluDG: ";
	for (int i = 1; i <= block->timeConstraint; i++) {
		cout << "	"<< aluDistribution.at(i);
	}
    cout<<endl;
    cout << "--------------------------------------------------------------------------" << endl;
	cout << "--------------------------------------------------------------------------" << endl;
	cout << "mulDG: ";
	for (int i = 1; i <= block->timeConstraint; i++) {
		cout << "	"<< multDistribution.at(i);
	}
    cout<<endl;
    cout << "--------------------------------------------------------------------------" << endl;
//#endif
    return true;
}
/**************************************************************************************************/
bool Scheduler::updateSelfForce(Block* block){
    for(unsigned int i = 0; i< block->nodeVector.size(); i++){
        block->nodeVector.at(i)->updateSelfForces(aluDistribution,multDistribution,divModDistribution);
//#if 0
    cout << "-------------Self Forces--------------------------------------------------" << endl;
        cout << "Node "<< i << " : ";
        for (int j = 1; j <= block->timeConstraint; j++) {
		    cout << "\t"<< block->nodeVector.at(i)->forceData.selfForces.at(j);
	    }
        cout<<endl;
//#endif
    } 
   fdsNotDone = false; // temperally stop here 
 return true;
}
/**************************************************************************************************/
vector<Node*> Scheduler::generateSuccessorQueue(Block* block, unsigned int nodeIndex){
	Node* currentNode = block->nodeVector.at(nodeIndex);
    //Node* childNode;
    queue<Node*>   frontierQueue;
    vector<Node*>   successorQueue;
    frontierQueue.push(currentNode); //beginning node for exploration 
	block->resetAll();
    while(frontierQueue.size()!=0){
        //for(unsigned int i = 0; i< frontierQueue.size(); i++){
            currentNode = frontierQueue.front();
            frontierQueue.pop();
            for	(unsigned i = 0; i<currentNode-> childNodes.size(); i++){
                if(currentNode->childNodes.at(i)->marked!=true){
                    currentNode->childNodes.at(i)->marked=true;
                    currentNode->childNodes.at(i)->fromNode = currentNode;
                    frontierQueue.push(currentNode->childNodes.at(i));
                    successorQueue.push_back(currentNode->childNodes.at(i));
                }
            }
            currentNode->visited = true;
    }
return successorQueue;
}
/**************************************************************************************************/
bool Scheduler::updateSucessorForces(Block* block){
    for(unsigned int i = 0; i< block->nodeVector.size(); i++){
        Node * currentNode = block->nodeVector.at(i);
        // push a dummy cycle start at time 1
        currentNode->forceData.successorForces.push_back(0.0);
        for(int j = 1; j<=block->timeConstraint; j++){
            vector<Node*>   successorQueue;
            Node * startNode = nullptr;
            successorQueue = generateSuccessorQueue(block,i);
            float tempForce = 0.0;
            if(j>=currentNode->asapTime && j<=currentNode->alapTime){
                int nowTime = j;
                while(successorQueue.size()!=0){
                    //find the lowest asap
                    int asapTrial=65536; // any big initial number greater than any possible asap
                    int si;
                    bool hasSameCycle = false;
                    int restoreTime;
                    for(unsigned int i =0; i<successorQueue.size();i++){
                        if(asapTrial==successorQueue.at(i)->asapTime){
                            hasSameCycle = true; // already has a node that has been set
                        }
                        else if(asapTrial>successorQueue.at(i)->asapTime){
                            asapTrial = successorQueue.at(i)->asapTime;
                            startNode = successorQueue.at(i);
                            si = i; // memorize index
                        }
                    }
                    if(startNode->isInTimeFrame(nowTime)){
                        if(hasSameCycle){
                            restoreTime = nowTime;
                        }

                        if(startNode->fromNode->op=="MUL"){
                            nowTime+=2;
                        }
                        else if(startNode->fromNode->op=="DIV"){
                            nowTime+=3;
                        }
                        else if(startNode->fromNode->op=="MOD"){
                            nowTime+=3;
                        }
                        else{
                            nowTime++;
                        }
                        tempForce += startNode->forceData.selfForces.at(nowTime);
                        
                        if(hasSameCycle){
                            nowTime = restoreTime;
                        }
                        //node is done, remove this one
                        successorQueue.erase(successorQueue.begin()+si);
                    }
                    else{
                        successorQueue.clear(); //no available successors
                    }
                }
                currentNode->forceData.successorForces.push_back(tempForce);
            }
            else{
                currentNode->forceData.successorForces.push_back(0.0);
            }
        }
    //#if 0
        cout << "-------------Successor Forces--------------------------------------------------" << endl;
        cout << "Node "<< i << " : ";
        for (int j = 1; j <= block->timeConstraint; j++) {
		    cout << "\t"<< block->nodeVector.at(i)->forceData.successorForces.at(j);
	    }
        cout<<endl;
//#endif
    }
    return true;
}
/**************************************************************************************************/
vector<Node*> Scheduler::generatePredecessorQueue(Block* block, unsigned int nodeIndex){
	Node* currentNode = block->nodeVector.at(nodeIndex);
    //Node* childNode;
    queue<Node*>   frontierQueue;
    vector<Node*>   predecessorQueue;
    frontierQueue.push(currentNode); //beginning node for exploration 
	block->resetAll();
    while(frontierQueue.size()!=0){
        //for(unsigned int i = 0; i< frontierQueue.size(); i++){
            currentNode = frontierQueue.front();
            frontierQueue.pop();
            for	(unsigned i = 0; i<currentNode-> parentNodes.size(); i++){
                if(currentNode->parentNodes.at(i)->marked!=true){
                    currentNode->parentNodes.at(i)->marked=true;
                    currentNode->parentNodes.at(i)->toNode = currentNode;
                    frontierQueue.push(currentNode->parentNodes.at(i));
                    predecessorQueue.push_back(currentNode->parentNodes.at(i));
                }
            }
            currentNode->visited = true;
    }
return predecessorQueue;
}
/**************************************************************************************************/
bool Scheduler::updatePredecessorForces(Block* block){
     for(unsigned int i = 0; i< block->nodeVector.size(); i++){
        Node * currentNode = block->nodeVector.at(i);
        // push a dummy cycle start at time 1
        currentNode->forceData.predecessorForces.push_back(0.0);
        for(int j = 1; j<=block->timeConstraint; j++){
            vector<Node*>   predecessorQueue;
            Node * startNode = nullptr;
            predecessorQueue = generatePredecessorQueue(block,i);
            float tempForce = 0.0;
            if(j>=currentNode->asapTime && j<=currentNode->alapTime){
                int nowTime = j;
                while(predecessorQueue.size()!=0){
                    //find the highest alap in all predecessors -> the closest child node 
                    int alapTrial=0; // any small initial number smaller than any possible alap
                    int si;
                    bool hasSameCycle = false;
                    int restoreTime;
                    for(unsigned int i =0; i<predecessorQueue.size();i++){
                        if(alapTrial==predecessorQueue.at(i)->alapTime){
                            hasSameCycle = true; // already has a node that has been set
                        }
                        else if(alapTrial<predecessorQueue.at(i)->alapTime){
                            alapTrial = predecessorQueue.at(i)->alapTime;
                            startNode = predecessorQueue.at(i);
                            si = i; // memorize index
                        }
                    }
                    if(startNode->isInTimeFrame(nowTime)){
                        if(hasSameCycle){
                            restoreTime = nowTime;
                        }

                        if(startNode->op=="MUL"){
                            nowTime-=2;
                        }
                        else if(startNode->op=="DIV"){
                            nowTime-=3;
                        }
                        else if(startNode->op=="MOD"){
                            nowTime-=3;
                        }
                        else{
                            nowTime--;
                        }
                        tempForce += startNode->forceData.selfForces.at(nowTime);
                        
                        if(hasSameCycle){
                            nowTime = restoreTime;
                        }
                        //node is done, remove this one
                        predecessorQueue.erase(predecessorQueue.begin()+si);
                    }
                    else{
                        predecessorQueue.clear(); //no available successors
                    }
                }
                currentNode->forceData.predecessorForces.push_back(tempForce);
            }
            else{
                currentNode->forceData.predecessorForces.push_back(0.0);
            }
        }
    //#if 0
        cout << "-------------Predecessors Forces--------------------------------------------------" << endl;
        cout << "Node "<< i << " : ";
        for (int j = 1; j <= block->timeConstraint; j++) {
		    cout << "\t"<< block->nodeVector.at(i)->forceData.predecessorForces.at(j);
	    }
        cout<<endl;
//#endif
    }
    return true;
}   
/**************************************************************************************************/
//Determines which node should be scheduled based on the minimum total force
bool Scheduler::scheduleNode(Block* block){
	
	Node * currentNode;
	Node * minimumForceNode = NULL;
	bool parentConflict = false;
	bool childConflict = false;

	if (!block->nodeVector.empty()) {
		//1. Determine the minimum total force for each node
		for (unsigned int i = 0; i < block->nodeVector.size(); i++) {
			currentNode = block->nodeVector.at(i);
			currentNode->forceData.updateTotalForces();
			currentNode->forceData.updateMinTotalForce(currentNode->alapTime, currentNode->alapTime);
		}
		//Find any unscheduled Node to begin
		for (unsigned int i = 0; i < block->nodeVector.size(); i++) {
			if (block->nodeVector.at(i)->scheduleTime == 0) {
				minimumForceNode = block->nodeVector.at(i);
				break;
			}
		}
		//Check if an unscheduled node was not found
		if (minimumForceNode != NULL) {

			//2. Find node with the the smallest total force
			for (unsigned int i = 0; i < block->nodeVector.size(); i++) {
				currentNode = block->nodeVector.at(i);
				//Check that current node isn't scheduled and that it has the smallest total force
				if (currentNode->scheduleTime == 0 &&
					currentNode->forceData.minTotalForce < minimumForceNode->forceData.minTotalForce) {
					minimumForceNode = currentNode;
				}
			}

			//Taget schedule time, time we want to schdule node without conflicts
			//Initially set as time with minimum force determined by FDS
			int targetTime = minimumForceNode->forceData.minTotalForceCycle;

			//3. Schedule the unscheduled node with minimum force
			//First Check for scheduling conficts with parents and children
			
				vector<Node*> parents;  //scheduled parents
				vector<Node*> children; //scheduled children
				Node* parentNode;
				Node* childNode;
				int upperDiff = 0, lowerDiff = 0, currentDiff = 0;

				//Determine scheduled Parents with conflicts
				for (unsigned int i = 0; i < minimumForceNode->parentNodes.size(); i++) {
					parentNode = minimumForceNode->parentNodes.at(i);
					if (parentNode->scheduleTime != 0) {
						parents.push_back(parentNode);
						int endTime = parentNode->scheduleTime - (parentNode->executionTime - 1);
						if (targetTime <= endTime) {
							parentConflict = true;
							currentDiff = abs(targetTime - endTime);
							if (upperDiff < currentDiff)
								upperDiff = currentDiff;
						}
					}
				}
				//Determine scheduled Children with conflicts
				for (unsigned int i = 0; i < minimumForceNode->childNodes.size(); i++) {
					childNode = minimumForceNode->childNodes.at(i);
					if (childNode->scheduleTime != 0) {
						children.push_back(childNode);
						int startTime = childNode->scheduleTime;
						if (targetTime >= startTime) {
							childConflict = true;
							currentDiff = abs(targetTime - startTime);
							if (lowerDiff < currentDiff)
								lowerDiff = currentDiff;
						}
					}
				}
				//Check for conflicts, attempt to adjust targetTime
				if (parentConflict || childConflict) {
					if (parentConflict)
						targetTime = targetTime + (upperDiff + 1);
					else if (childConflict)
						targetTime = targetTime - (lowerDiff + 1) - (minimumForceNode->executionTime - 1);
				}

				//target time is either the same as fds schedule time
				//or was adjusted to avoid conflicts

				minimumForceNode->scheduleTime = targetTime;
				cout << "\n----------------------------------------------------------------------" << endl;
				cout << "Scheduled Node: " << minimumForceNode->id << " Scheduled Time: " << minimumForceNode->scheduleTime << endl;
				cout << "----------------------------------------------------------------------" << endl;
		}
	
        //check if all nodes are scheduled
        bool allDone=true;
        for(unsigned int i = 0 ; i<block->nodeVector.size();i++){
            allDone &= (block->nodeVector.at(i)->scheduleTime != 0);
        }
        fdsNotDone=!allDone;
        
        return true;
	}
	return false;
}
/**************************************************************************************************/
bool Scheduler::determineAlapSchedule(Block * block){

	if (block->timeConstraint > 0) {
		//Reset all traverse Parameters
		block->resetAll();
		block->findLastNodes();

		bool ready = false;
		Node* currentNode;
		Node* parentNode;
		Node* childNode;
		int earliestAlapTime = 0;
		int maxExecuteTime = 0;
		vector<Node*> predecessors;
		int remainingTime = block->timeConstraint;
		
		/*
		//For testing force certain nodes to be scheduled already w/asap time
		for (unsigned int i = 0; i < block->nodeVector.size(); i++) {
			currentNode = block->nodeVector.at(i);
			if (currentNode->asapTime == 2) {
				//currentNode->scheduled = true;
				//currentNode->marked = true;
				currentNode->scheduleTime = 2;
			}
		}
		*/
		//Check if all nodes that have been FDS scheduled already
		for (unsigned int i = 0; i < block->nodeVector.size(); i++) {
			currentNode = block->nodeVector.at(i);
			if (currentNode->scheduleTime != 0) {
				currentNode->alapTime = currentNode->scheduleTime;
				currentNode->scheduled = true;
			}
		}
		//Schedule the last nodes in graph first
		for (unsigned int i = 0; i < block->nodeVector.size(); i++) {
			currentNode = block->nodeVector.at(i);
			remainingTime = block->timeConstraint;
			if (currentNode->last) {
				if(!currentNode->scheduled)
					currentNode->alapTime = remainingTime - (currentNode->executionTime - 1);
				currentNode->marked = true;
				currentNode->scheduled = true;

				//Add all current nodes predecessors to queue
				for (unsigned int j = 0; j < currentNode->parentNodes.size(); j++) {
					parentNode = currentNode->parentNodes.at(j);
					
					//Check that parentNode is within current block
					if (std::find(block->nodeVector.begin(), block->nodeVector.end(),
						parentNode) != block->nodeVector.end()) {

						if (!parentNode->marked) {
							predecessors.push_back(parentNode);
							parentNode->marked = true;
						}
					}
				}
			}
		}
		//Schedule All the predecessors
		while (!predecessors.empty()) {
			for (unsigned int i = 0; i < predecessors.size(); i++) {
				ready = true;
				currentNode = predecessors.at(i);
				for (unsigned int i = 0; i < currentNode->childNodes.size(); i++) {
					childNode = currentNode->childNodes.at(i);
					//Ensure child is in current block
					if (std::find(block->nodeVector.begin(), block->nodeVector.end(),
						childNode) != block->nodeVector.end()) {
						if (!childNode->scheduled) {
							ready = false;
							break;
						}
					}
				}
				//Schedule current node if ready, all child nodes scheduled
				if (ready) {
					earliestAlapTime = block->timeConstraint;
					maxExecuteTime = 0;
					for (unsigned int k = 0; k < currentNode->childNodes.size(); k++) {
						childNode = currentNode->childNodes.at(k);
						if (std::find(block->nodeVector.begin(), block->nodeVector.end(),
							childNode) != block->nodeVector.end()) {
							if (childNode->executionTime >= maxExecuteTime) {
								maxExecuteTime = childNode->executionTime;
							}
							if ((childNode->scheduled)
								&& (childNode->alapTime <= earliestAlapTime)) {
								earliestAlapTime = childNode->alapTime;
							}
						}
					}
					remainingTime = (earliestAlapTime - currentNode->executionTime);
					//currentNode->alapTime = remainingTime - (currentNode->executionTime - 1);
					if(currentNode->scheduleTime == 0)
						currentNode->alapTime = remainingTime;
					currentNode->scheduled = true;
				}
				//Add all current nodes predecessors to queue
				for (unsigned int j = 0; j < currentNode->parentNodes.size(); j++) {

					parentNode = currentNode->parentNodes.at(j);
					//Check that parentNode is within current block
					if (std::find(block->nodeVector.begin(), block->nodeVector.end(),
						parentNode) != block->nodeVector.end()) {

						if (!parentNode->marked) {
							predecessors.push_back(parentNode);
							parentNode->marked = true;
						}
					}
				}
				//If currentNode is scheduled remove it from predecessor queue
				if (currentNode->scheduled) {
					predecessors.erase(predecessors.begin() + i);
				}
			}
		}
		//Check that all scheduled Alap times are valid
		for (unsigned int i = 0; i < block->nodeVector.size(); i++) {
			currentNode = block->nodeVector.at(i);
			if (currentNode->alapTime > block->timeConstraint || currentNode->alapTime < 0)
				return false;
		}
		block->scheduled = true;
		return true;
	}
	//Scheduling failed, constraint not met
	block->scheduled = false;
	return  true;
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

    //Test schedule time!
    //block->nodeVector.at(4)->scheduleTime = 0;

    int exec_cycle = 1;
    while(scheduleNotDone){
        vector<Node*> newScheduled;
        //executing phase
        for(unsigned int i = 0; i< block->nodeVector.size();i++){
            bool nodeAvailable = true;
            // if the node has been schedule, wait the schedule time
            nodeAvailable &= exec_cycle >= block->nodeVector.at(i)->scheduleTime;
            for(unsigned int j = 0; j< block->nodeVector.at(i)->inputs.size();j++){
                if(block->nodeVector.at(i)->inputs.at(j)){
                    nodeAvailable &= block->nodeVector.at(i)->inputs.at(j)->available;
                }
            }
            if(nodeAvailable&&
               //node available but not scheduled yet
               (block->nodeVector.at(i)->visited==false)){
                // mark node visited, push to the vector, and mark asapTime 
				block->nodeVector.at(i)->nVisited = true;
				newScheduled.push_back(block->nodeVector.at(i));
				block->nodeVector.at(i)->asapTime = exec_cycle;
				//Check for exceeded time constaint
				if (block->timeConstraint < exec_cycle) return false;

                if(block->nodeVector.at(i)->op=="MUL"){
                    block->nodeVector.at(i)->nAsapCount++;
                }
                else if(block->nodeVector.at(i)->op=="DIV"){
                    block->nodeVector.at(i)->nAsapCount++;
                }
                else if(block->nodeVector.at(i)->op=="MOD"){
                    block->nodeVector.at(i)->nAsapCount++;
                }
                else {
                    block->nodeVector.at(i)->nMarked=true;
                    block->nodeVector.at(i)->output->nAvailable=true;
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
            //one cycle end, if there are new scheduled nodes, push to array
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

