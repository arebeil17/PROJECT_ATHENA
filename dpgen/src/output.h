#ifndef OUTPUT_H
#define OUTPUT_H
/*************/
/*
 * File: Input.h
 * Author: Andres Rebeil
 * NetID: andres07
 * Date: December 1st, 2015
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
#include "net.h"
#include "datapath.h"

/**************************************************************************************************/
using namespace std;

class Output { 
	
	public:
		//Default Constructor
		Output();
		//Custom Constructor
		Output(char *outputFile, vector<Net>*  netListVector, vector<Node>* nodeListVector);

        //Variables
        char *outputFile;
        vector<Net>*    netListVector;
        vector<Node>*   nodeListVector;
        string          verilogText;
        bool            weHaveRegister;


        //Function Headers
        bool preMakeProcess();
        bool dumpVerilogText();
        bool makeHead();
        bool makeNets();
        bool makeNodes();
        bool makeEnd();
        bool makeVerilog();
        string getNetMatched(unsigned int i, string io, int numOfNets);
};
 
#endif //OUTPUT_H

