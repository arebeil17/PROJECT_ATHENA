//
//  nodeList.cpp
//  Kyle Kuan
//
//
//

#include "nodeList.h"
#include <string>
#include <vector>
using namespace std;
// Class construtor functions
nodeList::nodeList(vector<string>* netlistLines) {
    this->netlistLines = netlistLines;
}
net::net() {
   // do nothing 
}
node::node() {
   // do nothing 
}

// Functions

int nodeList::createNetList(string* nowParsingText, string type, int width, bool signedBit){
    string keyWord=", ";
    size_t pos;
    while((pos =nowParsingText->find(keyWord)) != std::string::npos){
        net newNet;
        newNet.type=type;
        newNet.width=width;
        newNet.signedBit=signedBit;
        newNet.name=nowParsingText->substr(0, pos);
        nowParsingText->erase(0, pos + keyWord.length());
        netListVector.push_back(newNet);
    }
    net newNet;
    newNet.type=type;
    newNet.width=width;
    newNet.signedBit=signedBit;
    if((pos =nowParsingText->find(" ")) != std::string::npos) //special case, ending has " " padding.
        newNet.name=nowParsingText->substr(0, pos);
    else if((pos =nowParsingText->find("\t")) != std::string::npos)//special case, ending has "\t"
        newNet.name=nowParsingText->substr(0, pos);
    else
        newNet.name=*nowParsingText;
    netListVector.push_back(newNet);
return 1;
}

bool nodeList::createNodeInputs(string* nowParsingText, vector<net*>* inputNets){
// The int num is the input number that the operator should have
    string  keyWord=" ";
    string  found_t="";
    size_t  pos;
    bool    found=false;
    
    while ((pos=nowParsingText->find(keyWord))!=std::string::npos){
        found_t = nowParsingText->substr(0,pos);
        for (unsigned i=0; i<netListVector.size();i++){ 
            if(netListVector.at(i).name==found_t) {
                inputNets->push_back(&netListVector.at(i)); 
                found=true;  // Found one.
            }
        }
        nowParsingText->erase(0,keyWord.length()+found_t.length());
    }
    found=false; //last trial
    found_t=*nowParsingText;
    for (unsigned i=0; i<netListVector.size();i++){ 
        if(netListVector.at(i).name==found_t) {
            inputNets->push_back(&netListVector.at(i)); 
            found=true;  // Found one.
        }
    }
    return found;
}

int nodeList::parseNetlistLines(){
    string  nowParsingText; 
    string  keyWord;
    string  found_t;
    bool    signedBit;
    size_t  pos;
    for(unsigned int i=0;i<netlistLines->size();i++){
        nowParsingText = netlistLines->at(i);
        signedBit=true;
        if(nowParsingText.substr(0,6)=="input "){
            //do input
            nowParsingText.erase(0,6);
            if(nowParsingText.at(0) == 'U') {
                signedBit=false;
                nowParsingText.erase(0,1);
            }
            if (nowParsingText.find(keyWord="Int1 ")!=std::string::npos){
                nowParsingText.erase(0, keyWord.length());
                createNetList(&nowParsingText,"input",1,signedBit);
            }
            if (nowParsingText.find(keyWord="Int8 ")!=std::string::npos){
                nowParsingText.erase(0, keyWord.length());
                createNetList(&nowParsingText,"input",8,signedBit);
            }
            if (nowParsingText.find(keyWord="Int16 ")!=std::string::npos){
                nowParsingText.erase(0, keyWord.length());
                createNetList(&nowParsingText,"input",16,signedBit);
            }
            if (nowParsingText.find(keyWord="Int32 ")!=std::string::npos){
                nowParsingText.erase(0, keyWord.length());
                createNetList(&nowParsingText,"input",32,signedBit);
            }
            if (nowParsingText.find(keyWord="Int64 ")!=std::string::npos){
                nowParsingText.erase(0, keyWord.length());
                createNetList(&nowParsingText,"input",64,signedBit);
            }

        }
        else if(nowParsingText.substr(0,7)=="output "){
            //do output
            nowParsingText.erase(0, 7);
            if(nowParsingText.at(0) == 'U') {
                signedBit=false;
                nowParsingText.erase(0,1);
            }
            if (nowParsingText.find(keyWord="Int1 ")!=std::string::npos){
                nowParsingText.erase(0, keyWord.length());
                createNetList(&nowParsingText,"output",1,signedBit);
            }
            if (nowParsingText.find(keyWord="Int8 ")!=std::string::npos){
                nowParsingText.erase(0, keyWord.length());
                createNetList(&nowParsingText,"output",8,signedBit);
            }
            if (nowParsingText.find(keyWord="Int16 ")!=std::string::npos){
                nowParsingText.erase(0, keyWord.length());
                createNetList(&nowParsingText,"output",16,signedBit);
            }
            if (nowParsingText.find(keyWord="Int32 ")!=std::string::npos){
                nowParsingText.erase(0, keyWord.length());
                createNetList(&nowParsingText,"output",32,signedBit);
            }
            if (nowParsingText.find(keyWord="Int64 ")!=std::string::npos){
                nowParsingText.erase(0, keyWord.length());
                createNetList(&nowParsingText,"output",64,signedBit);
            }

        }
        else if(nowParsingText.substr(0,5)=="wire "){
        //do wire
            nowParsingText.erase(0, 5);
            if(nowParsingText.at(0) == 'U') {
                signedBit=false;
                nowParsingText.erase(0,1);
            }
            if (nowParsingText.find(keyWord="Int1 ")!=std::string::npos){
                nowParsingText.erase(0, keyWord.length());
                createNetList(&nowParsingText,"wire",1,signedBit);
            }
            if (nowParsingText.find(keyWord="Int8 ")!=std::string::npos){
                nowParsingText.erase(0, keyWord.length());
                createNetList(&nowParsingText,"wire",8,signedBit);
            }
            if (nowParsingText.find(keyWord="Int16 ")!=std::string::npos){
                nowParsingText.erase(0, keyWord.length());
                createNetList(&nowParsingText,"wire",16,signedBit);
            }
            if (nowParsingText.find(keyWord="Int32 ")!=std::string::npos){
                nowParsingText.erase(0, keyWord.length());
                createNetList(&nowParsingText,"wire",32,signedBit);
            }
            if (nowParsingText.find(keyWord="Int64 ")!=std::string::npos){
                nowParsingText.erase(0, keyWord.length());
                createNetList(&nowParsingText,"wire",64,signedBit);
            }
        }
        else if(nowParsingText.substr(0,9)=="register "){
        //do register
            nowParsingText.erase(0, 9);
            if(nowParsingText.at(0) == 'U') {
                signedBit=false;
                nowParsingText.erase(0,1);
            }
            if (nowParsingText.find(keyWord="Int1 ")!=std::string::npos){
                nowParsingText.erase(0, keyWord.length());
                createNetList(&nowParsingText,"register",1,signedBit);
            }
            if (nowParsingText.find(keyWord="Int8 ")!=std::string::npos){
                nowParsingText.erase(0, keyWord.length());
                createNetList(&nowParsingText,"register",8,signedBit);
            }
            if (nowParsingText.find(keyWord="Int16 ")!=std::string::npos){
                nowParsingText.erase(0, keyWord.length());
                createNetList(&nowParsingText,"register",16,signedBit);
            }
            if (nowParsingText.find(keyWord="Int32 ")!=std::string::npos){
                nowParsingText.erase(0, keyWord.length());
                createNetList(&nowParsingText,"register",32,signedBit);
            }
            if (nowParsingText.find(keyWord="Int64 ")!=std::string::npos){
                nowParsingText.erase(0, keyWord.length());
                createNetList(&nowParsingText,"register",64,signedBit);
            }
        }

        else{
        
        // do component
        // search output
        string op;
        net* output;
        vector<net*> inputNets;
        bool found=false;
        if ((pos=nowParsingText.find(keyWord=" = "))!=std::string::npos){
            found_t = nowParsingText.substr(0,pos);
        }
        for (unsigned i=0; i<netListVector.size();i++){ 
            if(netListVector.at(i).name==found_t) {
                found=true;
                output = &netListVector.at(i); 
                nowParsingText.erase(0,keyWord.length()+found_t.length());
                if(output->type=="register") 
                    op="REG";
            }
        }
        if (found==false) {
            return -1; // found no output
        }         // search operator
        if ((pos=nowParsingText.find(keyWord="+ "))!=std::string::npos){
            nowParsingText.erase(pos,keyWord.length());
            op="ADD";
            createNodeInputs(&nowParsingText, &inputNets);
        }
        else if ((pos=nowParsingText.find(keyWord="- "))!=std::string::npos){
            nowParsingText.erase(pos,keyWord.length());
            op="SUB";
            createNodeInputs(&nowParsingText, &inputNets);
        } 
        else if ((pos=nowParsingText.find(keyWord="* "))!=std::string::npos){
            nowParsingText.erase(pos,keyWord.length());
            op="MUL";
            createNodeInputs(&nowParsingText, &inputNets);
        }
        else if ((pos=nowParsingText.find(keyWord="== "))!=std::string::npos){
            nowParsingText.erase(pos,keyWord.length());
            op="COMP_EQ";
            createNodeInputs(&nowParsingText, &inputNets);
        }
        else if ((pos=nowParsingText.find(keyWord="< "))!=std::string::npos){
            nowParsingText.erase(pos,keyWord.length());
            op="COMP_LT";
            createNodeInputs(&nowParsingText, &inputNets);
        }
        else if ((pos=nowParsingText.find(keyWord="> "))!=std::string::npos){
            nowParsingText.erase(pos,keyWord.length());
            op="COMP_GT";
            createNodeInputs(&nowParsingText, &inputNets);
        }
        else if ((pos=nowParsingText.find(keyWord="? "))!=std::string::npos){
            nowParsingText.erase(pos,keyWord.length());
                if ((pos=nowParsingText.find(keyWord=": "))!=std::string::npos) nowParsingText.erase(pos,keyWord.length());
            op="MUX2x1";
            createNodeInputs(&nowParsingText, &inputNets);
        }
        else if ((pos=nowParsingText.find(keyWord=">> "))!=std::string::npos){
            nowParsingText.erase(pos,keyWord.length());
            op="SHR";
            createNodeInputs(&nowParsingText, &inputNets);
        }
        else if ((pos=nowParsingText.find(keyWord="<< "))!=std::string::npos){
            nowParsingText.erase(pos,keyWord.length());
            op="SHL";
            createNodeInputs(&nowParsingText, &inputNets);
        }
        else if ((pos=nowParsingText.find(keyWord="/ "))!=std::string::npos){
            nowParsingText.erase(pos,keyWord.length());
            op="DIV";
            createNodeInputs(&nowParsingText, &inputNets);
        }
        else if ((pos=nowParsingText.find(keyWord="% "))!=std::string::npos){
            nowParsingText.erase(pos,keyWord.length());
            op="MOD";
            createNodeInputs(&nowParsingText, &inputNets);
        }
        else if ((pos=nowParsingText.find(keyWord=" + 1"))!=std::string::npos){
            nowParsingText.erase(pos,keyWord.length());
            op="INC";
            createNodeInputs(&nowParsingText, &inputNets);
        }
        else if ((pos=nowParsingText.find(keyWord=" - 1"))!=std::string::npos){
            nowParsingText.erase(pos,keyWord.length());
            op="DEC";
            createNodeInputs(&nowParsingText, &inputNets);
        }
        else {
            op="WIRE";
            createNodeInputs(&nowParsingText, &inputNets);
        }

        node  newNode;
        newNode.output=output;
        newNode.op=op;
        for(unsigned i=0;i<inputNets.size();i++){
            newNode.inputs.push_back(inputNets.at(i));
        }
        nodeListVector.push_back(newNode);
        }
    }
return 1;
}
//nodeList::nodeList(std::string name) {
//    this->name = name;
//    vector<string> tempFollowers {};
//    this->followers = tempFollowers;
//    vector<string> tempFollowing {};
//    this->following = tempFollowing;
//}
//
//std::string nodeList::getName() {
//    return name;
//}
//
//void nodeList::getName(std::string name) {
//    this->name = name;
//    return;
//}
//
//std::vector<string> nodeList::getFollowers() {
//    return followers;
//}
//
//void nodeList::setFollowers(std::vector<string> followers) {
//    this->followers = followers;
//    return;
//}
//
//std::vector<string> nodeList::getFollowing() {
//    return following;
//}
//
//void nodeList::setFollowing(std::vector<string> following) {
//    this->following = following;
//    return;
//}
//
//void nodeList::newFollower(string follower) {
//    followers.push_back(follower);
//    return;
//}
//
//void nodeList::newFollowing(string newFollowing) {
//    following.push_back(newFollowing);
//    return;
//}
