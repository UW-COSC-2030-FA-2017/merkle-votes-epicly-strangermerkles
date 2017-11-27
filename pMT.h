#pragma once

#include "bTREE.h"

#include <string>
using namespace std;
class pMT
{
private:
    int selectedHash;
    bTREE myMerkle;
    
	string hash(int, string) const; //***
    string hash_1(string) const;//***
    string hash_2(string) const;//***
    string hash_3(string) const;//***

	bTREE::treeNode* insert2(bTREE::treeNode*, bTREE::treeNode*);
	bTREE::treeNode* checkDifferent(bTREE::treeNode*, bTREE::treeNode*, bTREE::treeNode*);
public:
    pMT(int = 1);//***
    ~pMT();//***

    int insert(string, int);
    
    int find(string, int) const; //***
    int findHash(string) const; //***
    
	string locateData(string) const; //***
	string locateHash(string) const; //***

    friend bool operator==(const pMT&, const pMT&); //***
    friend bool operator!=(const pMT&, const pMT&); //***
    friend pMT operator^(const pMT&, const pMT&); //***
    friend ostream& operator<<(ostream&, const pMT&); //***
};

