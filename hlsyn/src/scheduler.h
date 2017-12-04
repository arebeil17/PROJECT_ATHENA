#ifndef SCHEDULER_H
#define SCHEDULER_H
/*************/
/*
 * File: Scheduler.h
 * Author: Andres Rebeil
 * NetID: andres07
 * Date: November 21st, 2017
 *
 * Description: This class implements all the functionality for the scheduling algorithms.
 */
 /**************************************************************************************************/
#include <vector>
#include <queue>
#include <list>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>
#include <cstdio>
#include <algorithm>
#include "node.h"
#include "net.h"
#include "block.h"

/**************************************************************************************************/
using namespace std;

class Scheduler { 
    private: 	
	public:
		//Default Constructor
		Scheduler();

        vector<vector<Node*>> asap;
		vector<float> aluDistribution;
		vector<float> multDistribution;
		vector<float> divModDistribution;
        bool    fdsNotDone = true;



        //Perform all the steps of Force Directed Scheduling on current block's nodes
		bool forceDirectedScheduling(Block* block);
		bool determineAlapSchedule(Block * block);
		bool asapSchedule(Block * block);

        bool updateTimeFrame(Block* block);
        bool updateDistributions(Block* block);
        bool updateSelfForce(Block* block);
        bool updatePredecessorForces(Block* block);
        bool updateSucessorForces(Block* block);
        bool scheduleNode(Block* block);
        vector<Node*> generateSuccessorQueue(Block* block, unsigned int nodeIndex);
        vector<Node*> generatePredecessorQueue(Block* block, unsigned int nodeIndex);
};
 
#endif //SCHEDULER_H

