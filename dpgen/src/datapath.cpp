/*
* File: datapath.cpp
* Author: Andres Rebeil
* NetID: andres07
* Date: December 1st, 2015
*
* Description: This file .cpp file contains the implementation of the input class
*/
/**************************************************************************************************/
#include "datapath.h"
/**************************************************************************************************/

//Default Constructor
Datapath::Datapath()
{
	maxBitwidth = 0;
}
/**************************************************************************************************/
//Customer constructor
Datapath::Datapath(vector<string>* netlistLines) {
	this->netlistLines = netlistLines;
}
/**************************************************************************************************/
int Datapath::createNetList(string* nowParsingText, string type, int width, bool signedBit) {
	string keyWord = ", ";
	size_t pos;
	while ((pos = nowParsingText->find(keyWord)) != std::string::npos) {
		Net newNet;
		newNet.type = type;
		newNet.width = width;
		newNet.signedBit = signedBit;
		newNet.name = nowParsingText->substr(0, pos);
		nowParsingText->erase(0, pos + keyWord.length());
		netListVector.push_back(newNet);
	}
	Net newNet;
	newNet.type = type;
	newNet.width = width;
	newNet.signedBit = signedBit;
	if ((pos = nowParsingText->find(" ")) != std::string::npos) //special case, ending has " " padding.
		newNet.name = nowParsingText->substr(0, pos);
	else if ((pos = nowParsingText->find("\t")) != std::string::npos)//special case, ending has "\t"
		newNet.name = nowParsingText->substr(0, pos);
	else
		newNet.name = *nowParsingText;
	netListVector.push_back(newNet);
	return 1;
}
/**************************************************************************************************/
bool Datapath::createNodeInputs(string* nowParsingText, vector<Net*>* inputNets) {
	// The int num is the input number that the operator should have
	string  keyWord = " ";
	string  found_t = "";
	size_t  pos;
	bool    found = false;

	while ((pos = nowParsingText->find(keyWord)) != std::string::npos) {
		found_t = nowParsingText->substr(0, pos);
		for (unsigned i = 0; i<netListVector.size(); i++) {
			if (netListVector.at(i).name == found_t) {
				inputNets->push_back(&netListVector.at(i));
				found = true;  // Found one.
			}
		}
		nowParsingText->erase(0, keyWord.length() + found_t.length());
	}
	found = false; //last trial
	found_t = *nowParsingText;
	for (unsigned i = 0; i<netListVector.size(); i++) {
		if (netListVector.at(i).name == found_t) {
			inputNets->push_back(&netListVector.at(i));
			found = true;  // Found one.
		}
	}
	return found;
}


/**************************************************************************************************/
int Datapath::parseNetlistLines() {
	string  nowParsingText;
	string  keyWord;
	string  found_t;
	bool    signedBit;
	int bitWidth;
	size_t  pos;
	for (unsigned int i = 0; i < netlistLines->size(); i++) {
		nowParsingText = netlistLines->at(i);
		signedBit = true;
		//Check if Input
		if (nowParsingText.substr(0, 6) == "input ") {
			nowParsingText.erase(0, 6);
			if (nowParsingText.at(0) == 'U') {
				signedBit = false;
				nowParsingText.erase(0, 1);
			}
			//Determine bitwidth and create netlist
			if (nowParsingText.find(keyWord = "Int") != std::string::npos) {
				nowParsingText.erase(0, keyWord.length());
				pos = nowParsingText.find(" ");
				bitWidth = stoi(nowParsingText.substr(0, pos));
				nowParsingText.erase(0, pos + 1);
				createNetList(&nowParsingText, "input", bitWidth, signedBit);
			}
		}//Check if Output
		else if (nowParsingText.substr(0, 7) == "output ") {
			nowParsingText.erase(0, 7);
			if (nowParsingText.at(0) == 'U') {
				signedBit = false;
				nowParsingText.erase(0, 1);
			}
			if (nowParsingText.find(keyWord = "Int") != std::string::npos) {
				nowParsingText.erase(0, keyWord.length());
				pos = nowParsingText.find(" ");
				bitWidth = stoi(nowParsingText.substr(0, pos));
				nowParsingText.erase(0, pos + 1);
				createNetList(&nowParsingText, "onput", bitWidth, signedBit);
			}
		}//Check if Wire
		else if (nowParsingText.substr(0, 5) == "wire ") {
			//do wire
			nowParsingText.erase(0, 5);
			if (nowParsingText.at(0) == 'U') {
				signedBit = false;
				nowParsingText.erase(0, 1);
			}
			if (nowParsingText.find(keyWord = "Int") != std::string::npos) {
				nowParsingText.erase(0, keyWord.length());
				pos = nowParsingText.find(" ");
				bitWidth = stoi(nowParsingText.substr(0, pos));
				nowParsingText.erase(0, pos + 1);
				createNetList(&nowParsingText, "wire", bitWidth, signedBit);
			}
		}//Check if Register
		else if (nowParsingText.substr(0, 9) == "register ") {
			nowParsingText.erase(0, 9);
			if (nowParsingText.at(0) == 'U') {
				signedBit = false;
				nowParsingText.erase(0, 1);
			}
			if (nowParsingText.find(keyWord = "Int") != std::string::npos) {
				nowParsingText.erase(0, keyWord.length());
				pos = nowParsingText.find(" ");
				bitWidth = stoi(nowParsingText.substr(0, pos));
				nowParsingText.erase(0, pos + 1);
				createNetList(&nowParsingText, "register", bitWidth, signedBit);
			}
		}
		else {
			// do component
			// search output
			string op;
			Net* output;
			vector<Net*> inputNets;
			bool found = false;
			if ((pos = nowParsingText.find(keyWord = " = ")) != std::string::npos) {
				found_t = nowParsingText.substr(0, pos);
			}
			for (unsigned i = 0; i < netListVector.size(); i++) {
				if (netListVector.at(i).name == found_t) {
					found = true;
					output = &netListVector.at(i);
					nowParsingText.erase(0, keyWord.length() + found_t.length());
					if (output->type == "register")
						op = "REG";
				}
			}
			if (found == false) {
				return -1; // found no output
			}         // search operator
			if ((pos = nowParsingText.find(keyWord = "+ ")) != std::string::npos) {
				op = "ADD";
			}
			else if ((pos = nowParsingText.find(keyWord = "- ")) != std::string::npos) {
				op = "SUB";
			}
			else if ((pos = nowParsingText.find(keyWord = "* ")) != std::string::npos) {
				op = "MUL";
			}
            else if ((pos = nowParsingText.find(keyWord = ">> ")) != std::string::npos) {
				op = "SHR";
			}
			else if ((pos = nowParsingText.find(keyWord = "<< ")) != std::string::npos) {
				op = "SHL";
			}

			else if ((pos = nowParsingText.find(keyWord = "== ")) != std::string::npos) {
				op = "COMP_EQ";
			}
			else if ((pos = nowParsingText.find(keyWord = "< ")) != std::string::npos) {
				op = "COMP_LT";
			}
			else if ((pos = nowParsingText.find(keyWord = "> ")) != std::string::npos) {
				op = "COMP_GT";
			}
			else if ((pos = nowParsingText.find(keyWord = "? ")) != std::string::npos) {
				nowParsingText.erase(pos, keyWord.length());
				pos = nowParsingText.find(keyWord = ": ");
				op = "MUX2x1";
			}
			else if ((pos = nowParsingText.find(keyWord = "/ ")) != std::string::npos) {
				op = "DIV";
			}
			else if ((pos = nowParsingText.find(keyWord = "% ")) != std::string::npos) {
				op = "MOD";
			}
			else if ((pos = nowParsingText.find(keyWord = " + 1")) != std::string::npos) {
				op = "INC";
			}
			else if ((pos = nowParsingText.find(keyWord = " - 1")) != std::string::npos) {
				op = "DEC";
			}
			else if (op==""){
				keyWord = "";
				op = "WIRE";
			}
			//Only need to perform this once
			createNodeInputs(&nowParsingText, &inputNets);

			Node  newNode;
			newNode.output = output;
			newNode.op = op;
			for (unsigned i = 0; i < inputNets.size(); i++) {
				newNode.inputs.push_back(inputNets.at(i));
			}
			nodeListVector.push_back(newNode);
		}
	}
	return 1;
}
/**************************************************************************************************/
void Datapath::printNodeListVector() {
	cout << endl;
	for (int i = 0; i < this->nodeListVector.size(); i++) {
		cout << "Node " + to_string(i) + ": Type: " + this->nodeListVector.at(i).op << endl; 
		cout << "	"<<this->nodeListVector.at(i).toString() << endl;
		cout << "--------------------------------------------------------------------------" << endl;
	}
}
/**************************************************************************************************/
void Datapath::updateNodeDelays() {
	for (int i = 0; i < this->nodeListVector.size(); i++) {
		nodeListVector.at(i).width = nodeListVector.at(i).output->width;
	}
}
