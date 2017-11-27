#include "pMT.h"
#include <iostream>

pMT::pMT(int hashSelect)
/**
 * @brief 
 * @param hashSelect a number corresponding to the hashfunction to use for this pMT
 * @return 
 */
{
	selectedHash = hashSelect;
}

pMT::~pMT()
/**
 * @brief destructor
 * @return nada
 */
{
}

int pMT::insert(string vote, int time)
/**
 * @brief insert a vote and time into a leaf node of tree
 * @param vote - a string
 * @param time - an int representing the time 
 * @return the number of operations needed to do the insert, -1 if out of memory
 */

{
	bTREE::treeNode* tree2 = new bTREE::treeNode();
	bTREE::treeNode* temp = myMerkle.getTree();
	tree2->leaf = true;
	tree2->time = time;
	tree2->data = vote;
	myMerkle.setTree(insert2(temp, tree2));
	return 1;
}

bTREE::treeNode* pMT::insert2(bTREE::treeNode* temp, bTREE::treeNode* newnode)
{
	if (temp == NULL) {
		temp = newnode;
	}
	else {
		int lheight = myMerkle.height(temp->leftNode);
		int rheight = myMerkle.height(temp->rightNode);

		if (lheight <= rheight) {
			insert2(temp->leftNode, newnode);
			if (temp->leftNode == NULL) {
				bTREE::treeNode* temp2 = new bTREE::treeNode();
				temp->leftNode = newnode;
				temp2->data = temp->data;
				temp2->time = temp->time;
				temp2->leaf = true;
				temp->rightNode = temp2;
				temp->data = hash(selectedHash, temp->leftNode->data + temp->rightNode->data);
				temp->time = 0;
				temp->leaf = false;
				temp->leftNode->parent = temp;
				temp->rightNode->parent = temp;
			}
		}
		else {
			insert2(temp->rightNode, newnode);
			if (temp->rightNode == NULL) {
				bTREE::treeNode* temp2 = new bTREE::treeNode();
				temp->leftNode = newnode;
				temp2->data = temp->data;
				temp2->time = temp->time;
				temp2->leaf = true;
				temp->rightNode = temp2;
				temp->data = hash(selectedHash, temp->leftNode->data + temp->rightNode->data);
				temp->time = 0;
				temp->leaf = false;
				temp->leftNode->parent = temp;
				temp->rightNode->parent = temp;
			}
		}
	}
	while (temp->parent != NULL) {
		temp->parent->data = hash(selectedHash, temp->parent->leftNode->data + temp->parent->rightNode->data);
		temp = temp->parent;
	}
	return temp;
}


int pMT::find(string vote, int time) const
/**
 * @brief given a vote and a timestamp does this vote exist in the tree?
 * @param vote, a string
 * @param time, an int
 * @return 0 if not found, else number of opperations required to find the matching vote
 */
{
	return myMerkle.find(vote, time);
}

int pMT::findHash(string mhash) const
/**
 * @brief does this hash exist in the tree?
 * @param mhash, a string to search for in the tree
 * @return 0 if not found, else number of opperations required to find the matching hash
 */
{
	return myMerkle.find(mhash);
}

string pMT::locateData(string vote) const
/**
 * @brief Function takes a string and returns the sequence of (L)eft and (R)ight moves to get to that node starting from root. 
 * @param vote, the data to search for 
 * @return sequence of L's and R's comprising the movement to the leaf node; else return a dot '.'
 */
{
	return myMerkle.locate(vote);
}

string pMT::locateHash(string hash) const
/**
* @brief Function takes a string and returns the sequence of (L)eft and (R)ight moves to get to that node starting from root.
* @param vote, the data to search for
* @return sequence of L's and R's comprising the movement to the leaf node; else return a dot '.'
*/
{
	return myMerkle.locate(hash);
}

// http://blog.refu.co/?p=804

string pMT::hash(int hashSelect, string vote) const
{
	if (hashSelect == 1) {
		return hash_1(vote);
	}
	else if (hashSelect == 2) {
		return hash_2(vote);
	}
	else {
		return hash_3(vote);
	}
}

string pMT::hash_1(string key) const
/**
 * @brief A function that takes in a key and returns a hash of that key using some custom function
 * @param key, a string
 * @return a hash of the key
 */
{
	unsigned int hash = 5381;
	unsigned int i = 0;
	char const* str = key.c_str();
	unsigned int length = key.length();

	for (i = 0; i < length; ++str, ++i)
	{
		hash = ((hash << 5) + hash) + (*str);
	}
	return to_string(hash);
}

string pMT::hash_2(string key) const
/**
 * @brief A function that takes in a key and returns a hash of that key using some custom function
 * @param key, a string
 * @return a hash of the key
 */
{
	unsigned int b = 378551;
	unsigned int a = 63689;
	unsigned int hash = 0;
	unsigned int i = 0;
	char const* str = key.c_str();
	unsigned int length = key.length();

	for (i = 0; i < length; ++str, ++i)
	{
		hash = hash * a + (*str);
		a = a * b;
	}
	return to_string(hash);
}

string pMT::hash_3(string key) const
/**
 * @brief A function that takes in a key and returns a hash of that key using some custom function
 * @param key, a string
 * @return a hash of the key
 */
{
	unsigned int hash = 10639;
	unsigned int i = 0;
	char const* str = key.c_str();
	unsigned int length = key.length();

	for (i = 0; i < length; ++str, ++i)
	{
		hash = ((hash << 5) ^ (hash >> 27)) ^ (*str);
	}

	return to_string(hash);
}

bool operator==(const pMT & lhs, const pMT & rhs)
/**
 * @brief Comparison between two merkle trees
 * @param lhs, the left hand side of the equality statment
 * @param rhs, the right hand side of the equality statement
 * @return true if equal, false otherwise
 */
{
	return lhs.myMerkle == rhs.myMerkle;
}

bool operator !=(const pMT& lhs, const pMT& rhs)
/**
 * @brief Comparison between two merkle trees
 * @param lhs, the left hand side of the equality statment
 * @param rhs, the right hand side of the equality statement
 * @return true if not equal, false otherwise
 */
{
	return lhs.myMerkle != rhs.myMerkle;
}

ostream& operator <<(ostream& out, const pMT& p)
/**
 * @brief Print out a tree
 * @param out
 * @param p
 * @return a tree to the screen
 */
{
	return out << p.myMerkle;
}

pMT operator ^(const pMT& lhs, const pMT& rhs)
/**
 * @brief Where do two trees differ
 * @param lhs
 * @param rhs
 * @return a tree comprised of the right hand side tree nodes that are different from the left
 */
{
	pMT temp = pMT();
	bTREE tempTree = bTREE();
	bTREE::treeNode* btemp = new bTREE::treeNode();
	memcpy(btemp, rhs.myMerkle.getTree(), sizeof(bTREE::treeNode) * rhs.myMerkle.numberOfNodes());
	tempTree.setTree(temp.checkDifferent(lhs.myMerkle.getTree(), rhs.myMerkle.getTree(), btemp));
	temp.myMerkle = tempTree;
	cout << tempTree;
	return temp;
}

bTREE::treeNode* pMT::checkDifferent(bTREE::treeNode* lhs, bTREE::treeNode* rhs, bTREE::treeNode* temp)
{
	if(lhs == NULL || lhs->data == rhs->data) {
		temp = NULL;
	}
	else {
		checkDifferent(lhs->leftNode, rhs->leftNode, temp->leftNode);
		checkDifferent(lhs->rightNode, rhs->rightNode, temp->rightNode);
		return temp;
	}
	return temp;
}