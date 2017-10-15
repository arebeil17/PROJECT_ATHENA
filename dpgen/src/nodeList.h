#ifndef nodeList_h
#define nodeList_h

#include <stdio.h>
#include <string>
#include <vector>
using namespace std;

class net {
	private:
	public:
		net();
		// Variables
		string name;
		int width;
		string type;
		bool signedBit;
		//Functions
};

class node {
	private:
	public:
		node();
		// Variables
		string op;
		float delay= 0.0;
		int width = 0;
		vector<node*> parentNodes;
		vector<node*> childNodes;
		vector<net*> inputs;
		net* output;
		//Functions
};

class nodeList {
	private:

	public:
		// Function constructors
		nodeList(vector<string>* netlistLines);
    
		// Variables
		vector<string>* netlistLines;
		vector<net>  netListVector;
		vector<node> nodeListVector;
		//Functions
		int parseNetlistLines();
		int createNetList(string* nowParsingText, string type, int width, bool signedBit);      
		bool createNodeInputs(string* nowParsingText, vector<net*>* inputNets);
};


#endif /* nodeList_h */
