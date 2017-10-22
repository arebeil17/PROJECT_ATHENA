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
	criticalDelay = 0.0;
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
			newNode.id = nodeListVector.size() + 1;
			nodeListVector.push_back(newNode);
		}
	}
	return 1;
}
/**************************************************************************************************/
void Datapath::printNodeListVector() {
	cout << endl;
	for (unsigned int i = 0; i < this->nodeListVector.size(); i++) {
		cout << "Node id: " + to_string(this->nodeListVector.at(i).id) + " Type: " + this->nodeListVector.at(i).op << endl;
		cout << "	"<<this->nodeListVector.at(i).toString() << endl;
		cout << "--------------------------------------------------------------------------" << endl;
	}
}
/**************************************************************************************************/
void Datapath::updateAllNodeBitwidth() {
	for (unsigned int i = 0; i < this->nodeListVector.size(); i++) {
		nodeListVector.at(i).width = nodeListVector.at(i).output->width;
	}
}
/**************************************************************************************************/
//Update all node delays based off bitwidth
void Datapath::updateAllNodeDelay(){
	for (unsigned int i = 0; i < this->nodeListVector.size(); i++) {
		nodeListVector.at(i).updateDelay();
	}
}
/**************************************************************************************************/
//Find Root Nodes
bool Datapath::findRootNodes() {
	unsigned int nodeInputCount = 0;

	for (unsigned int i = 0; i < this->nodeListVector.size(); i++) {
		//Check all node inputs are of type input net
		for(unsigned int j = 0; j < this->nodeListVector.at(i).inputs.size(); j++) {
			if (!this->nodeListVector.at(i).inputs.at(j)->type.compare("input"))
				nodeInputCount++;
		}
		//Check if current Nodes nets are all inputs
		if (nodeInputCount == this->nodeListVector.at(i).inputs.size()) {
			//Add to root node vector
			rootNodes.push_back(&(this->nodeListVector.at(i)));
		}
		nodeInputCount = 0;
	}
	if (this->rootNodes.size() > 0) return true;
	else return false;
}
/**************************************************************************************************/
//Determine critical path of circuit by perform BFS on node graph
float Datapath::determineCriticalPath(){

	updateAllNodeBitwidth();
	updateAllNodeDelay();
	findRootNodes();

	
	//Determine path delay for each root/source node
	for (unsigned int i = 0; i < this->rootNodes.size(); i++) {
		//Perform BFS on source node
		breadthFirstSearch(this->rootNodes.at(i));
	}
	
	Node* finalNode;
	for (unsigned int i = 0; i < this->nodeListVector.size(); i++) {
		float pathDelay = nodeListVector.at(i).pathDelay + nodeListVector.at(i).delay;
		if (criticalDelay < pathDelay) {
			criticalDelay = pathDelay;
			finalNode = &nodeListVector.at(i);
		}
	}
	Node* currentNode = finalNode;
	this->criticalPath.push_front(currentNode);
	while (currentNode->criticalNode != NULL) {
		this->criticalPath.push_front(currentNode->criticalNode);
		//Set current to critical/next node
		currentNode = currentNode->criticalNode;
	}
	return criticalDelay;
}
/**************************************************************************************************/
//Perform BFS given source node and return maximum path delay
void Datapath::breadthFirstSearch(Node* source) {
	
	queue<Node*> nodeQueue;
	Node* currentNode;

	if (source != NULL) {
		//Insert source node to queue
		nodeQueue.push(source);
	
		//set source node as visited
		source->visited = true;
		//All marked childs nodes to queue
			
		while (nodeQueue.size() > 0) {
			currentNode = nodeQueue.front();
			nodeQueue.pop(); //dequeue current node
			
			expandNode(currentNode);

			for (unsigned int i = 0; i < currentNode->childNodes.size(); i++) {
				if (currentNode->childNodes.at(i)->visited == false)
					nodeQueue.push(currentNode->childNodes.at(i));
			}
			currentNode->visited = true;
		}

	}
}
/**************************************************************************************************/
//Expand current node by updating path delay and setting it's children
bool Datapath::expandNode(Node* currentNode) {
	if (currentNode != NULL) {
		bool root = (find(rootNodes.begin(), rootNodes.end(), currentNode) != rootNodes.end());
		for (unsigned int i = 0; i < this->nodeListVector.size(); i++) {
			
			if (currentNode->id != this->nodeListVector.at(i).id) {
				//set parents
				//if not a root node update parent nodes
				if (!root) {
					//check if current nodes inputs match another nodes outputs
					for (unsigned int k = 0; k < currentNode->inputs.size(); k++) {
						//compare input net name with output net name
						if (!currentNode->inputs.at(k)->name.compare(this->nodeListVector.at(i).output->name)) {
							//if parent hasn't been added yet, add parent node
							
							if (std::find(currentNode->parentNodes.begin(),
										  currentNode->parentNodes.end(),
										  &this->nodeListVector.at(i))
										  == currentNode->parentNodes.end()) {
								currentNode->parentNodes.push_back(&this->nodeListVector.at(i));
							}
						}
					}
				}
				//set childs
				//check if current node's output matchs another node's inputs
				for (unsigned int k = 0; k < this->nodeListVector.at(i).inputs.size(); k++) {
					//compare input net name with output net name
					if (!this->nodeListVector.at(i).inputs.at(k)->name.compare(currentNode->output->name)) {
						//if parent hasn't been added yet, add parent node
						if (find(currentNode->childNodes.begin(),
									  currentNode->childNodes.end(),
									  &this->nodeListVector.at(i))
									  == currentNode->childNodes.end()) {
							this->nodeListVector.at(i).marked = true;
							currentNode->childNodes.push_back(&this->nodeListVector.at(i));
						}
					}
				}
			}
		}
		//Update max path delay to node
		float max = 0.0;
		for (unsigned int i = 0; i < currentNode->parentNodes.size(); i++) {
			float pathDelay = currentNode->parentNodes.at(i)->pathDelay + currentNode->parentNodes.at(i)->delay;
			if (max < pathDelay) {
				max = pathDelay;
				currentNode->criticalNode = currentNode->parentNodes.at(i);
			}
		}
		currentNode->pathDelay = max;

		return true;
	}
	return false;
}
/**************************************************************************************************/
//Print Root Nodes
void Datapath::printRootNodes() {
	cout << endl << "Root Nodes: \n";
	cout << "--------------------------------------------------------------------------" << endl;
	for (unsigned int i = 0; i < this->rootNodes.size(); i++) {
		cout << "Node id: " + to_string(this->rootNodes.at(i)->id) + " Type: " + this->rootNodes.at(i)->op << endl;
		cout << "	" << this->rootNodes.at(i)->toString() << endl;
		cout << "--------------------------------------------------------------------------" << endl;
	}
}
/**************************************************************************************************/
//Print critical path info
void Datapath::printCriticalPathInfo() {
	cout << endl << "Critical Path Delay: " + to_string(this->criticalDelay) << " Nodes: " + to_string(criticalPath.size()) <<endl;
	cout << "--------------------------------------------------------------------------" << endl;
	for (std::list<Node*>::iterator it = criticalPath.begin(); it != criticalPath.end(); ++it) {
		cout << "Node id: " + to_string((*it)->id) + " Type: " + (*it)->op << endl;
		cout << "	" << (*it)->toString() << endl;
		cout << "--------------------------------------------------------------------------" << endl;
	}
}
