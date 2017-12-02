/**************************************************************************************************/
/*
* File: main.cpp
* Author: Andres D. Rebeil, Nikitha Ramohalli, Kyle Kuan
* NetID: andres07
* Date: December 1st, 2015
*
* Description: 
*/
/**************************************************************************************************/
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include "input.h"
#include "datapath.h"
#include "output.h"
#include "synthesis.h"
#include "scheduler.h"
/**************************************************************************************************/

int main(int argc, char *argv[]) {
    
    /* Check for the correct number of command line arguments. If incorrect
    *  provide a simple usage message to assist user
    */
    if(argc == 3){
       
		Input input;

		if (input.readInputFile(argv[1])) {
			
			Datapath datapath = Datapath(input.netlistLines);

			if (datapath.parseNetlistLines()) {

				datapath.determineCriticalPath();

				//datapath.printAll(false);
				datapath.printAll(true);
                
                Synthesis synthesis(input.netlistLines, &(datapath.nodeListVector));
                synthesis.makeBlocks();
				synthesis.setAllBlockPointers();
				synthesis.setBlockConstraint(10);
				//synthesis.printBlocks();
                
                Scheduler scheduler = Scheduler();
                for(unsigned int i = 0; i<synthesis.blockVector.size(); i++){
                    if(synthesis.blockVector.at(i)->type=="component"){
                        scheduler.asapSchedule(synthesis.blockVector.at(i));
						synthesis.blockVector.at(i)->timeConstraint = stoi(argv[2]);
						scheduler.determineAlapSchedule(synthesis.blockVector.at(i));
						synthesis.blockVector.at(i)->printSchedulingInfo();
                    }
                }
                    
                //Output output(argv[2], &(datapath.netListVector), &(datapath.nodeListVector));
				//output.makeVerilog();
			}
			else {
				cout << "\nError found in netlist file at line " << to_string(datapath.currentLine + 1)<<". Aborted netlist conversion." << endl;
				return -1;
			}
		} //Empty input file provided
		else {
			return -1;
		}
	}//Invalid number of input arguments entered
	else {
		cout << "\nUsage: " << argv[0] << " cFile latency verilogFile" << endl;
		return -1;
	}

    return 0;
}
