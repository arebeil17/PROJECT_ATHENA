/*
* File: Synthesis.cpp
* Author: Andres Rebeil
* NetID: andres07
* Date: November 21st, 2017
*
* Description: This file .cpp file contains the implementation of the Synthesis class
*/
/**************************************************************************************************/
#include "synthesis.h"
/**************************************************************************************************/

//Default Constructor
Synthesis::Synthesis()
{
    currentLine = 0;
    blockId = 0;
}
Synthesis::Synthesis(vector<string> netlistLines, vector<Node>* nodeListVector){
    this->netlistLines = netlistLines;
    this->nodeListVector = nodeListVector;
    currentLine = 0;
    blockId = 0;
}
//static variable initiallization, Keep in case future debug
//unsigned int Synthesis::blockId = 0;
//unsigned int Synthesis::currentLine = 0;
//vector<Block*>   Synthesis::blockVector;
//Block Synthesis::nextLevelBlock[100];        

/**************************************************************************************************/
bool Synthesis::parseBlocks_prefix(){
    unsigned int i=0;
    size_t pos,lpos;
    string nowParsingText = "";
    string lastParsingText = "";
    while(i < netlistLines.size()) {
        nowParsingText = netlistLines.at(i);
        // erase head padding " "
        size_t firstNotSpace = nowParsingText.find_first_not_of(" \t\f\v\n\r");
        netlistLines.at(i) = nowParsingText.erase(0,firstNotSpace); 
        
        if((nowParsingText.substr(0, 6) == "input ")||
           (nowParsingText.substr(0, 7) == "output ")||
           (nowParsingText.substr(0, 9) == "variable ")){
            netlistLines.erase(netlistLines.begin()+i);
            continue;
        }
        i++;
    }
    for(i=0;i<netlistLines.size();i++){
        nowParsingText = netlistLines.at(i);
        if( (pos = nowParsingText.find("{") != string::npos)&&
            (lpos = lastParsingText.find("}")== string::npos)&&
            (lpos = lastParsingText.find("{")== string::npos)){
            // nowParsing is a if condition, and last line doesn't contain { or }
            netlistLines.insert(netlistLines.begin()+i ,"}");
            i++;
        }
        else if((pos = nowParsingText.find("{") == string::npos)&&
            (lpos = lastParsingText.find("{")!=string::npos)){
            // nowParsing is a component, and last line is if or else condition
            netlistLines.insert(netlistLines.begin()+i ,"{");
            i++;
        }
 
        else if((pos = nowParsingText.find("}") == string::npos)&&
                (pos = nowParsingText.find("{") == string::npos)&&
            (lpos = lastParsingText.find("}")!=string::npos)){
            // nowParsing is a component, and last line is a ending
            netlistLines.insert(netlistLines.begin()+i ,"{");
            i++;
        }
        else if((lpos = lastParsingText.find("}") == string::npos)&&
            (pos = nowParsingText.find("}")!=string::npos)){
            // nowParsing is a ending, and last line is a component
            netlistLines.insert(netlistLines.begin()+i ,"}");
            i++;
        }

        lastParsingText = nowParsingText;
    }
    netlistLines.insert(netlistLines.begin() ,"{");
    if(netlistLines.back()!="}"){
        //means last components hasn't been completely contained by the last block
        netlistLines.push_back("}");
    };
return true;
}
/**************************************************************************************************/
bool Synthesis::parseBlocksNodes(Block* currentBlock, unsigned int currentLevel){
    string nowParsingText;
    unsigned int level = currentLevel+1;
    while (currentLine < netlistLines.size()) { 
        nowParsingText = netlistLines.at(currentLine);
        // Start parsing
        if(nowParsingText=="{"){
        currentLine++;
            buildNextBlock(currentBlock, "component", level, "no if else here"); 
            parseBlocksNodes(blockVector.back(),level);
        }
        else if(nowParsingText.substr(0, 4)=="if ("){
            currentLine++;
            // go to next recursion level
            buildNextBlock(currentBlock, "if", level, nowParsingText); 
            parseBlocksNodes(blockVector.back(),level);
        }
        else if(nowParsingText.substr(0, 6)=="else {"){
            currentLine++;
            buildNextBlock(currentBlock, "else", level, nowParsingText); 
            parseBlocksNodes(blockVector.back(),level);
        }
        else if((nowParsingText.substr(0, 1)=="}")){
            currentLine++;
            // recursion return
            return true;
        }
        else{
        currentLine++;
        // component parsing
        //do component parsing and filling block here
        //Text parsing
        size_t  pos = nowParsingText.find(" ");
        string output = nowParsingText.substr(0,pos);
        size_t  pos2 = nowParsingText.find(" ",pos+3);
        string input1 = nowParsingText.substr(pos+3,(pos2-pos-3));
        string  op = nowParsingText.substr(pos2+1);
        size_t  pos3 = nowParsingText.find_last_of(" ");
        string input2 = nowParsingText.substr(pos3+1); 
            for(unsigned int i = 0; i<nodeListVector->size(); i++){
                bool match = true;
                string key = nodeListVector->at(i).inputs.front()->name;
                match&=(key==input1);
                key = nodeListVector->at(i).inputs.back()->name;
                match&=(key==input2);
                key = nodeListVector->at(i).output->name;
                match&=(key==output);

                if(op.substr(0,1)=="+"&&op!="+ one") match&=(nodeListVector->at(i).op=="ADD");
                if(op.substr(0,1)=="*") match&=(nodeListVector->at(i).op=="MUL");

                if(match){
                    nodeListVector->at(i).statement = nowParsingText;
                    blockVector.back()->addNode(&nodeListVector->at(i));
                } 
            }
        }
    }
return true;
}

bool Synthesis::buildNextBlock(Block* currentBlock, string type, unsigned int level, string nowParsingText){
    // Blocks were stored in Block array, 
    // the pointer was pushed to vector for concise orginzing
    nextLevelBlock[blockId].parent = currentBlock;
    nextLevelBlock[blockId].type = type;
    nextLevelBlock[blockId].condText = nowParsingText;
    nextLevelBlock[blockId].level = level;
    nextLevelBlock[blockId].blockId = blockId;
    for(unsigned int i = 0; i<blockVector.size(); i++){
        // find the latest one in the same level 
        // that has just been pushed to vector
        if(blockVector.at(i)->level== level){
            if(type=="else"){
                nextLevelBlock[blockId].adjacent = blockVector.at(i);
            }
            else {
                nextLevelBlock[blockId].prev = blockVector.at(i);
            }
        }
    }
    blockVector.push_back(&nextLevelBlock[blockId]);

    blockId ++;
return true;
}
/**************************************************************************************************/
void Synthesis::setAllBlockPointers(){
	
	for (unsigned int i = 1; i < blockVector.size(); i++) {
		
		for (unsigned int j = i + 1; j < blockVector.size(); j++) {
				if (blockVector.at(i)->parent->blockId == blockVector.at(j)->parent->blockId) {
					blockVector.at(i)->next = blockVector.at(j);
					break;
				}
		}
		for (unsigned int j = 1; j < blockVector.size(); j++) {
			if ((blockVector.at(i)->blockId == blockVector.at(j)->parent->blockId) && (i!=j) ) {
				blockVector.at(i)->children.push_back(blockVector.at(j));
			}
		}
	}

}
/**************************************************************************************************/
bool Synthesis::makeBlocks(){
    parseBlocks_prefix();
    buildNextBlock(NULL, "top", 0,"");         // build top block 
    parseBlocksNodes(blockVector.back(),0); //assign null pointer to top block's parent
return true;
}
/**************************************************************************************************/
void Synthesis::printBlocks(){

	for (int i = 0; i < blockVector.size(); i++) {
		cout << "--------------------------------------------------------------------------" << endl;
		if (blockVector.at(i)->parent != NULL) {
			if (blockVector.at(i)->next != NULL) {
				cout << "Block: " << blockVector.at(i)->blockId << " Parent Block: " << blockVector.at(i)->parent->blockId << " Next Block: " << blockVector.at(i)->next->blockId;
			}else {
				cout << "Block: " << blockVector.at(i)->blockId << " Parent Block: " << blockVector.at(i)->parent->blockId << " Next Block: " << "NULL";
			}
			cout << " Children: ";
			for (unsigned int j = 0; j < blockVector.at(i)->children.size(); j++) {
				cout << " " << blockVector.at(i)->children.at(j)->blockId;
			}
			cout << endl;
		}
		else {
			cout << "Block: " << blockVector.at(i)->blockId << " Parent Block: " << "NULL" << " Next Block: " << "NULL" << endl;
		}
		cout << "--------------------------------------------------------------------------" << endl;
		for (int j = 0; j < blockVector.at(i)->nodeVector.size(); j++) {
			cout << "  " << blockVector.at(i)->nodeVector.at(j)->toString() << endl;
		}
	}

}
/**************************************************************************************************/