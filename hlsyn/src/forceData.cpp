/*
* File: ForceData.cpp
* Author: Andres Rebeil
* NetID: andres07
* Date: December 1st, 2015
*
* Description: This file .cpp file contains the implementation of the ForceData class
*/
/**************************************************************************************************/
#include "forceData.h"
/**************************************************************************************************/

//Default Constructor
ForceData::ForceData(){
    frameWidth = 0; //Means it wasn't set
	minTotalForceCycle = 0;
	minTotalForce = 10000;
}

/**************************************************************************************************/
//Compute and Update total forces based off current
//self, predecessor, and successorForces
void ForceData::updateTotalForces(){
	
	float totalSum = 0.0;
	
	//Erase old values before populating with new values
	totalForces.erase(totalForces.begin(), totalForces.end());
		
	for(unsigned int i = 0; i < selfForces.size(); i++){
			totalSum = 0.0;
			if(selfForces.size() > i) totalSum += selfForces.at(i);
			if(predecessorForces.size() > i) totalSum += predecessorForces.at(i);
			if(successorForces.size() > i) totalSum += successorForces.at(i);
			//Store totalForce for current time slot position of node
			totalForces.push_back(totalSum); 
	}
}
/**************************************************************************************************/
void ForceData::updateMinTotalForce(int alapTime, int asapTime){

	minTotalForce = 10000;
	for (unsigned int i = 1; i < totalForces.size(); i++) {
		int currentTime = i;
		//Check that currentTime is within specified time frame
		if ((currentTime >= asapTime) && (currentTime <= alapTime)) {
			//Check for the smallest total force
			if (totalForces.at(i) <= minTotalForce) {
				minTotalForce = totalForces.at(i);
				minTotalForceCycle = i;
			}
		}
	}
}
/**************************************************************************************************/
