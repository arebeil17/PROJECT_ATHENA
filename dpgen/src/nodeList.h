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
    float delay=0.0;
    int width=0;
    vector<node*>   parentNodes;
    vector<node*>   childNodes;
    vector<net*>    inputs;
    net*            output;
    //Functions
};

class nodeList {
private:

public:
    // Function constructors
    //constructs new user with name, followers, and following vectors
    //nodeList(vector<string>* netlistLines, vector<string> following);
    //constructs new user with name and empty followers and following vectors
    nodeList(vector<string>* netlistLines);
    
    // Variables
    vector<string>*     netlistLines;
    vector<net>         netListVector;
    vector<node>        nodeListVector;


    //Functions
    int parseNetlistLines();
    int createNetList(string* nowParsingText, string type, int width, bool signedBit);      
    bool createNodeInputs(string* nowParsingText, vector<net*>* inputNets);
//  std::string getName();
//  void getName(std::string name);
//  std::vector<std::string> getFollowers();
//  void setFollowers(std::vector<std::string> followers);
//  std::vector<std::string> getFollowing();
//  void setFollowing(std::vector<std::string> following);
//  void newFollower(std::string follower);
//  void newFollowing(std::string newFollowing);
};


#endif /* nodeList_h */
