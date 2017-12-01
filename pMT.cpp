#include "pMT.h"
#include <iostream>
using namespace std;

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
	int count = 1;
	// Emergency memoery so that if out of memory, this memory can be deleted and the error can be displayed
	char* _emergencyMemory = new char[1000];
	try {
		bTREE::treeNode* tree2 = new bTREE::treeNode();
		bTREE::treeNode* temp = myMerkle.getTree();
		tree2->leaf = true;
		tree2->time = time;
		tree2->height = 1;
		tree2->data = vote;
		if (temp == NULL) {
			myMerkle.setTree(tree2);
		}
		else {
			myMerkle.setTree(insert2(temp, tree2, count));
		}
	}
	catch (std::bad_alloc& ba) {
		// Delete the reserved memory so we can print an error message before exiting
		delete[] _emergencyMemory;

		cerr << "bad_alloc caught: " << ba.what() << endl;
		return -1;
	}
	return count;
}

// Helper function that inserts data into the node
// Count is used to count the total number of operations of the insert
bTREE::treeNode* pMT::insert2(bTREE::treeNode* temp, bTREE::treeNode* newnode, int& count)
{
	count ++;
	if (temp->leftNode == NULL) {
		bTREE::treeNode* temp2 = new bTREE::treeNode();
		temp->leftNode = newnode;
		temp2->data = temp->data;
		temp2->time = temp->time;
		temp2->leaf = true; 
		temp2->height = 1;
		temp->rightNode = temp2;
		temp->data = hash(selectedHash, temp->leftNode->data + temp->rightNode->data);
		temp->height = 2;
		temp->time = 0;
		temp->leaf = false;
		temp->leftNode->parent = temp;
		temp->rightNode->parent = temp;
		count += 1;					// Increment one more time because I need to move the root node to a leaf

		bool heightIncrease = true;

		// This recomputes hashes in the parent nodes
		// The height is changed only when the left and right nodes have the same height, else it keeps the height of the lowest tree
		while (temp->parent != NULL) {
			if (heightIncrease == true) {
				if (temp->parent->rightNode->height == temp->parent->leftNode->height) {
					temp->parent->height = (temp->parent->height) + 1;
				}
				else {
					heightIncrease = false;
				}
				temp->parent->data = hash(selectedHash, temp->parent->leftNode->data + temp->parent->rightNode->data);
			}
			temp = temp->parent;
			count++;
		}
	}
	// If leftNode isn't empty, then need to insert into the shortest branch and keep trying
	else {
		int lheight = temp->leftNode->height;
		int rheight = temp->rightNode->height;

		// Insert into the shortest height branch of the tree so the tree is balanced
		if (lheight <= rheight) {
			insert2(temp->leftNode, newnode, count);
		}
		else {
			insert2(temp->rightNode, newnode, count);
		}
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

string pMT::getRoot() const
{
	return myMerkle.getRoot();
}

string pMT::hash(int hashSelect, string vote) const
{
	if (hashSelect == 1) {
		return padZeros(hash_1(vote));
	}
	else if (hashSelect == 2) {
		return padZeros(hash_2(vote));
	}
	else {
		return padZeros(hash_3(vote));
	}
}

string pMT::hash_1(string key) const
/**
 * @brief A function that takes in a key and returns a hash of that key using some custom function
 * @param key, a string
 * @return a hash of the key
 */
{
	unsigned long int b = 378551;
	unsigned int hash = 63689;
	unsigned int i = 0;
	char const* str = key.c_str();
	unsigned int length = key.length();

	for (i = 0; i < length; ++str, ++i)
	{
		hash = (*str * (i + 1))*b + (hash << 3);
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
	unsigned long int hash = 4007;
	unsigned int i = 0;
	char const* str = key.c_str();
	unsigned int length = key.length();

	for (i = 0; i < length; ++str, ++i)
	{
		hash = hash + ((hash * (*str)) << (length - i));
	}

	return to_string(hash);
}

// Hash function credit to http://www.partow.net/programming/hashfunctions/
string pMT::hash_3(string key) const
/**
* @brief A function that takes in a key and returns a hash of that key using some custom function
* @param key, a string
* @return a hash of the key
*/
{
	unsigned int long hash = 5381;
	unsigned int i = 0;
	char const* str = key.c_str();
	unsigned int length = key.length();

	for (i = 0; i < length; ++str, ++i)
	{
		hash = ((hash << 5) + hash) + (*str);
	}
	return to_string(hash);
}

string pMT::padZeros(string str) const
{
	int strLength = str.length();
	for (int i = 0; i < 32 - strLength; i++) {
		str = "0" + str;
	}
	return str;
}

bool operator==(const pMT & lhs, const pMT & rhs)
/**
 * @brief Comparison between two merkle trees
 * @param lhs, the left hand side of the equality statment
 * @param rhs, the right hand side of the equality statement
 * @return true if equal, false otherwise
 */
{
	return (lhs.myMerkle.getTree()->data == rhs.myMerkle.getTree()->data);
}

bool operator !=(const pMT& lhs, const pMT& rhs)
/**
 * @brief Comparison between two merkle trees
 * @param lhs, the left hand side of the equality statment
 * @param rhs, the right hand side of the equality statement
 * @return true if not equal, false otherwise
 */
{
	return (lhs.myMerkle.getTree()->data != rhs.myMerkle.getTree()->data);
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

// DOES NOT WORK
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
	return temp;
}

// DOES NOT WORK
bTREE::treeNode* pMT::checkDifferent(bTREE::treeNode* lhs, bTREE::treeNode* rhs, bTREE::treeNode* temp)
{
	if(lhs == NULL || rhs == NULL) {
		return temp;
	}
	if (lhs->data == rhs->data) {
		temp = NULL;
	}
	else {
		checkDifferent(lhs->leftNode, rhs->leftNode, temp->leftNode);
		checkDifferent(lhs->rightNode, rhs->rightNode, temp->rightNode);
		return temp;
	}
	return temp;
}