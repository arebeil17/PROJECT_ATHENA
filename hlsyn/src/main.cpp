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

				Output output(argv[2], &(datapath.netListVector), &(datapath.nodeListVector));
				output.makeVerilog();
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
		cout << "\nUsage: " << argv[0] << " netlistFile verilogFile" << endl;
		return -1;
	}

    return 0;
}
