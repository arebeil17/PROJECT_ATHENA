#ifndef FORCEDATA_H
#define FORCE_DATA_H
/*************/
/*
 * File: forceData.h
 * Author: Andres Rebeil, Kyle, Nikitha
 * NetID: andres07
 * Date: December 1st, 2017
 *
 * Description: 
 */
 /**************************************************************************************************/
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>
#include <cstdio>

/**************************************************************************************************/
using namespace std;

class ForceData { 
	
	public:
		int frameWidth;
		vector<float> probabilities;
		//Forces for each possible time slot
		vector<float> selfForces;
		vector<float> predecessorForces;
		vector<float> successorForces;
		vector<float> totalForces;
		float minTotalForce;
		int minTotalForceCycle;
        // populate from node class

		//Default Constructor
		ForceData();
		//Compute and Update total force based off current
		//self, predecessor, and successorForces
		void updateTotalForces();
		//Update current minimum total force
		void updateMinTotalForce(int alapTime, int asapTime);
		
};
 
#endif //FORCEDATA_H
