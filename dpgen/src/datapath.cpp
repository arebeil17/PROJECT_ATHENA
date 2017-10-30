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
	currentLine = 0;
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
	
	if ((pos = nowParsingText->find("\t")) != std::string::npos)//special case, ending has "\t"
		newNet.name = nowParsingText->substr(0, pos);
	else if ((pos = nowParsingText->find(" ")) != std::string::npos) //special case, ending has " " padding.
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
			if (netListVector.at(i).name.compare(found_t) == 0) {
				inputNets->push_back(&netListVector.at(i));
				found = true;  // Found one.
			}
		}
		nowParsingText->erase(0, keyWord.length() + found_t.length());
	}
	//If remaining string is not empty continue checking for additional nets
	if (nowParsingText->compare("") != 0) {
		found = false; //last trial
		found_t = *nowParsingText;
		for (unsigned i = 0; i < netListVector.size(); i++) {
			if (netListVector.at(i).name.compare(found_t) == 0) {
				inputNets->push_back(&netListVector.at(i));
				found = true;  // Found one.
			}
		}
	}
	return found;
}


/**************************************************************************************************/
bool Datapath::parseNetlistLines() {
	string  nowParsingText;
	string  keyWord;
	string  found_t;
	bool    signedBit;
	int bitWidth;
	size_t  pos;
	for (unsigned int i = 0; i < netlistLines->size(); i++) {
		currentLine = i; //for error checking
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
				createNetList(&nowParsingText, "output", bitWidth, signedBit);
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
			string moduleName;
			Net* output;
			vector<Net*> inputNets;
			bool found = false;
			if ((pos = nowParsingText.find(keyWord = " = ")) != std::string::npos) {
				found_t = nowParsingText.substr(0, pos);
			}
			for (unsigned i = 0; i < netListVector.size(); i++) {
				if (netListVector.at(i).name.compare(found_t) == 0) {
					found = true;
					output = &netListVector.at(i);
					nowParsingText.erase(0, keyWord.length() + found_t.length());
					if (output->type == "register"){
						op = "REG";
						moduleName = "register";
                    }
				}
			}
			if (found == false) {
				return false; // found no output
			}         // search operator
			if ((pos = nowParsingText.find(keyWord = " + 1")) != std::string::npos) {
				op = "INC";
				moduleName = "inc";
			}
			else if ((pos = nowParsingText.find(keyWord = " - 1")) != std::string::npos) {
				op = "DEC";
				moduleName = "dec";
			}
            else if ((pos = nowParsingText.find(keyWord = "+ ")) != std::string::npos) {
				op = "ADD";
				moduleName = "add";
			}
			else if ((pos = nowParsingText.find(keyWord = "- ")) != std::string::npos) {
				op = "SUB";
				moduleName = "sub";
			}
			else if ((pos = nowParsingText.find(keyWord = "* ")) != std::string::npos) {
				op = "MUL";
				moduleName = "mul";
			}
            else if ((pos = nowParsingText.find(keyWord = ">> ")) != std::string::npos) {
				op = "SHR";
				moduleName = "shr";
			}
			else if ((pos = nowParsingText.find(keyWord = "<< ")) != std::string::npos) {
				op = "SHL";
				moduleName = "shl";
			}

			else if ((pos = nowParsingText.find(keyWord = "== ")) != std::string::npos) {
				op = "COMP_EQ";
				moduleName = "comp";
			}
			else if ((pos = nowParsingText.find(keyWord = "< ")) != std::string::npos) {
				op = "COMP_LT";
				moduleName = "comp";
			}
			else if ((pos = nowParsingText.find(keyWord = "> ")) != std::string::npos) {
				op = "COMP_GT";
				moduleName = "comp";
			}
			else if ((pos = nowParsingText.find(keyWord = "? ")) != std::string::npos) {
				nowParsingText.erase(pos, keyWord.length());
				pos = nowParsingText.find(keyWord = ": ");
				op = "MUX2x1";
				moduleName = "mux2x1";
			}
			else if ((pos = nowParsingText.find(keyWord = "/ ")) != std::string::npos) {
				op = "DIV";
				moduleName = "div";
			}
			else if ((pos = nowParsingText.find(keyWord = "% ")) != std::string::npos) {
				op = "MOD";
				moduleName = "mod";
			}
			else if (op==""){
				keyWord = "";
				op = "WIRE";
				moduleName = "";
			}
			//Only need to perform this once
			if (!createNodeInputs(&nowParsingText, &inputNets)) return false;

			Node  newNode;
			newNode.output = output;
			newNode.op = op;
			newNode.moduleName = moduleName;
			if (newNode.output->signedBit == true)
				newNode.signedBit = true;
			for (unsigned i = 0; i < inputNets.size(); i++) {
				if (inputNets.at(i)->signedBit == true && newNode.signedBit == false)
					newNode.signedBit = true;
				newNode.inputs.push_back(inputNets.at(i));
			}
			newNode.id = nodeListVector.size() + 1;
			nodeListVector.push_back(newNode);
		}

	}//End of main for loop

	return true;
}
/**************************************************************************************************/
void Datapath::printNodeListVector() {
	cout << endl << "All Nodes: \n";
	cout << "--------------------------------------------------------------------------" << endl;
	for (unsigned int i = 0; i < this->nodeListVector.size(); i++) {
		cout << "Node id: " + to_string(this->nodeListVector.at(i).id) + " Type: " + this->nodeListVector.at(i).op << endl;
		cout << "	"<<this->nodeListVector.at(i).toString() << endl;
		cout << "--------------------------------------------------------------------------" << endl;
	}
}
/**************************************************************************************************/
void Datapath::updateAllNodeBitwidth() {
	for (unsigned int i = 0; i < this->nodeListVector.size(); i++) {
		//Check if node is not a comparator, bitwidth based of output net width
		if (this->nodeListVector.at(i).op.find("COMP") == std::string::npos) {
			this->nodeListVector.at(i).width = nodeListVector.at(i).output->width;
		//else comparator node so bitwidth based off input net width 
		}else{
			this->nodeListVector.at(i).width = nodeListVector.at(i).inputs.at(0)->width;
		}
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
	
	Node* finalNode = NULL;
	float pathDelay = 0.0;
	for (unsigned int i = 0; i < this->nodeListVector.size(); i++) {
		//Check if current node is not a Register
		if (nodeListVector.at(i).op.compare("REG") != 0) 
			pathDelay = nodeListVector.at(i).pathDelay + nodeListVector.at(i).delay;
		else 
			pathDelay = nodeListVector.at(i).pathDelay;

		if (criticalDelay < pathDelay) {
			criticalDelay = pathDelay;
			finalNode = &nodeListVector.at(i);
		}
	}

	if(finalNode != NULL) createCriticalPathList(finalNode);

	return criticalDelay;
}
/**************************************************************************************************/
//creates critical path list given the final node
void Datapath::createCriticalPathList(Node* finalNode) {
	Node* currentNode = finalNode;
	this->criticalPath.push_front(currentNode);
	while (currentNode->criticalNode != NULL && currentNode != NULL) {
		//Set current node to critical/next node
		currentNode = currentNode->criticalNode;
		this->criticalPath.push_front(currentNode);
	}
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
				if (currentNode->childNodes.at(i)->visited == false 
					/*&& currentNode->childNodes.at(i)->marked != true*/) {
					currentNode->childNodes.at(i)->marked = true;
					nodeQueue.push(currentNode->childNodes.at(i));
				}
			}
			currentNode->visited = true;
		}

	}
}
/**************************************************************************************************/
//Expand current node by updating path delay and setting it's children
bool Datapath::expandNode(Node* currentNode) {
	if (currentNode != NULL) {
		Node* listNode;
		bool root = (std::find(rootNodes.begin(), rootNodes.end(), currentNode) != rootNodes.end());
		for (unsigned int i = 0; i < this->nodeListVector.size(); i++) {
			//pointer for current list node being checked
			listNode = &this->nodeListVector.at(i);
			//check that current node and list node are not the same
			if (currentNode->id != listNode->id) {
				//set parents
				//if not a root node update parent nodes
				if (!root) {
					//check if current nodes inputs match another nodes outputs
					for (unsigned int k = 0; k < currentNode->inputs.size(); k++) {
						//compare input net name with output net name
						if (!currentNode->inputs.at(k)->name.compare(listNode->output->name)) {
							//if parent hasn't been added yet, add parent node
							if (std::find(currentNode->parentNodes.begin(),
										  currentNode->parentNodes.end(),
										  listNode)
										  == currentNode->parentNodes.end()) {
								currentNode->parentNodes.push_back(listNode);
							}
						}
					}
				}
				//set childs
				//check if current node's output matchs another node's inputs
				for (unsigned int k = 0; k < listNode->inputs.size(); k++) {
					//compare input net name with output net name
					if (!listNode->inputs.at(k)->name.compare(currentNode->output->name)) {
						//if child hasn't been added yet, add child node
						if (std::find(currentNode->childNodes.begin(),
									  currentNode->childNodes.end(),
									  listNode)
									  == currentNode->childNodes.end()) {
							listNode->marked = true;
							currentNode->childNodes.push_back(listNode);
						}
					}
				}
			}
		}
		//Update max path delay to node
		float max = 0.0;
		float pathDelay = 0.0;

		for (unsigned int i = 0; i < currentNode->parentNodes.size(); i++) {
			//If parent node is not a Register then include node delay as part of path delay
			if (currentNode->parentNodes.at(i)->op.compare("REG") != 0)
				pathDelay = currentNode->parentNodes.at(i)->pathDelay + currentNode->parentNodes.at(i)->delay;
			else
				pathDelay = 0.0;

			if (max <= pathDelay) {
				max = pathDelay;
				currentNode->criticalNode = currentNode->parentNodes.at(i);
				currentNode->depth = currentNode->parentNodes.at(i)->depth + 1;
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
void Datapath::printCriticalPathInfo(bool full) {
	if (full) {
		cout << endl << "Critical Path Nodes: \n";
		cout << "--------------------------------------------------------------------------" << endl;
		cout << "Critical Path Delay: " + to_string(this->criticalDelay) << " Nodes: " + to_string(criticalPath.size()) << endl;
		cout << "--------------------------------------------------------------------------" << endl;
		if (criticalPath.size() > 0) {
			for (std::list<Node*>::iterator it = criticalPath.begin(); it != criticalPath.end(); ++it) {
				cout << "Node id: " + to_string((*it)->id) + " Depth: " + to_string((*it)->depth) + " Type: " + (*it)->op << endl;
				cout << "	" << (*it)->toString() << endl;
				cout << "--------------------------------------------------------------------------" << endl;
			}
		}
	}
	else {
		cout << "Critical Path Delay: " + to_string(this->criticalDelay) << " ns" << endl;
	}
}
/**************************************************************************************************/
//Print all information
void Datapath::printAll(bool all) {
	if (all) {
		printNodeListVector();
		printRootNodes();
	}
	printCriticalPathInfo(all);
}
