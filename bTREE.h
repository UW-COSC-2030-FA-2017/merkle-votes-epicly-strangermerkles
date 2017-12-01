#pragma once
#include <string>
using namespace std;

class bTREE
{
public:
	struct treeNode {
		string data;
		int time;
		bool leaf;
		int height;
		treeNode* leftNode;
		treeNode* rightNode;
		treeNode* parent;
	};
private:
	treeNode* tree;
    
	treeNode* insert2(treeNode*, treeNode*, int&); //****

	int find(string, int, treeNode*, bool&) const;//****
	string locate(string, treeNode*, string) const; //***

	void clearNode(treeNode*);//****
	int dataInserted(treeNode*) const;//****
	int numberOfNodes(treeNode*) const;//****

	ostream& display(std::ostream&, treeNode*) const; //***
	void displayLeft(ostream&, treeNode*, string) const; //***
	void displayRight(ostream&, treeNode*, string) const; //***

	bool checkEquality(treeNode*, treeNode*) const; //***
public:
    bTREE();//****
    ~bTREE();//****

	void setTree(treeNode* temp) {
		tree = temp;
	}

    int dataInserted() const;//****
    int numberOfNodes() const;//****
    
    int insert(string, int);//****
    
	int find(string data, int time = -1) const;//****

	treeNode* getTree() const;//****

    string locate(string) const; //***

	string getRoot() const;
    
    friend bool operator==(const bTREE&, const bTREE&); //***
    friend bool operator!=(const bTREE&, const bTREE&); //***
	friend ostream& operator<<(ostream&, const bTREE&); //***
};

