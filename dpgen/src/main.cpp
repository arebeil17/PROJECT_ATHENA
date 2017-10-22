/**************************************************************************************************/
/*
* File: main.cpp
* Author: Andres D. Rebeil
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
/**************************************************************************************************/

int main(int argc, char *argv[]) {
    
    /* Check for the correct number of command line arguments. If incorrect
    *  provide a simple usage message to assist user
    */
    if(argc != 2){
        cout << "\nUsage: " << argv[0] << " netlistFile verilogFile" << endl;
        return -1;
	}
	else {
		Input input;
		
		if(input.readInputFile(argv[1])) {
			//for debugging prints out file read 
			for (unsigned int i = 0; i < input.netlistLines.size(); i++) {
				cout << input.netlistLines.at(i) << endl;
			}
			Datapath datapath = Datapath(&(input.netlistLines));
			
			datapath.parseNetlistLines();
			
			datapath.determineCriticalPath();

			datapath.printNodeListVector();
			datapath.printRootNodes();
			datapath.printCriticalPathInfo();
		}
		else {
			return -1;
		}
	}
    return 0;
}
